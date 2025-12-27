/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A class for working with ZIP files.
 */


#include "NN9ZipFile.h"
#include "../Utilities/NN9Utilities.h"

namespace nn9 {

	ZipFile::ZipFile() {
		std::memset( &m_zaArchive, 0, sizeof( m_zaArchive ) );
	}
	ZipFile::~ZipFile() {
		Close();
	}


	// == Functions.
	/**
	 * Closes the opened file.
	 */
	void ZipFile::Close() {
		if ( m_pfFile != nullptr ) {
			::mz_zip_reader_end( &m_zaArchive );
			std::memset( &m_zaArchive, 0, sizeof( m_zaArchive ) );
		}
		StdFile::Close();
	}

	/**
	 * If true, the file is an archive containing more files.
	 *
	 * \return Returns true if the file is an archive, false otherwise.
	 */
	bool ZipFile::IsArchive() const { return m_zaArchive.m_zip_mode != MZ_ZIP_MODE_INVALID; }

	/**
	 * Gathers the file names in the archive into an array.  Call within try/catch block.
	 *
	 * \param _vResult The location where to store the file names.
	 * \return Returns an error code indicating the result of the operation.
	 */
	NN9_ERRORS ZipFile::GatherArchiveFiles( std::vector<std::u16string> &_vResult ) const {
		if ( m_pfFile != nullptr ) {
			if ( !IsArchive() ) { return Errors::ZipError_To_Native( ::mz_zip_get_last_error( const_cast<mz_zip_archive *>(&m_zaArchive) ) ); }
			mz_uint uiTotal = ::mz_zip_reader_get_num_files( const_cast<mz_zip_archive *>(&m_zaArchive) );
			for ( mz_uint I = 0; I  < uiTotal; ++I ) {
				::mz_zip_archive_file_stat zafsStat;
				if ( !::mz_zip_reader_file_stat( const_cast<mz_zip_archive *>(&m_zaArchive), I, &zafsStat ) ) {
					return Errors::ZipError_To_Native( ::mz_zip_get_last_error( const_cast<mz_zip_archive *>(&m_zaArchive) ) );
				}
				_vResult.push_back( Utilities::Utf8ToUtf16<char, std::u16string>( zafsStat.m_filename ) );
			}
			return NN9_E_SUCCESS;
		}
		return NN9_E_FILE_NOT_OPENED;
	}

	/**
	 * Extracts the given file from the archive.
	 *
	 * \param _s16File The name of the file to extract.
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 */
	NN9_ERRORS ZipFile::ExtractToMemory( const std::u16string &_s16File, std::vector<uint8_t> &_vResult ) const {
		if ( m_pfFile != nullptr ) {
			if ( !IsArchive() ) { return Errors::ZipError_To_Native( ::mz_zip_get_last_error( const_cast<mz_zip_archive *>(&m_zaArchive) ) ); }
			bool bError;
			std::u8string sUtf8 = Utilities::Utf16ToUtf8( _s16File, &bError );
			if ( bError ) { return NN9_E_INVALID_UNICODE; }
			size_t stSize;
			void * pvData = ::mz_zip_reader_extract_file_to_heap( const_cast<mz_zip_archive *>(&m_zaArchive), reinterpret_cast<const char *>(sUtf8.c_str()), &stSize, 0 );
			if ( pvData == nullptr ) { return NN9_E_OUT_OF_MEMORY; }
			try {
				_vResult = std::vector<uint8_t>( static_cast<uint8_t *>(pvData), static_cast<uint8_t *>(pvData) + stSize );
			}
			catch ( ... ) {
				::mz_free( pvData );
				return NN9_E_OUT_OF_MEMORY;
			}
			::mz_free( pvData );
			return NN9_E_SUCCESS;
		}
		return NN9_E_FILE_NOT_OPENED;
	}

	// == Functions.
	/**
	 * Performs post-loading operations after a successful loading of the file.  m_pfFile will be valid when this is called.  Override to perform additional loading operations on m_pfFile.
	 */
	void ZipFile::PostLoad() {
		::mz_zip_reader_init_cfile( &m_zaArchive, m_pfFile, m_ui64Size, 0 );
	}

}	// namespace nn9
