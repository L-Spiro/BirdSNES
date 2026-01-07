/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A class for opening files using the standard C library (FILE).
 */


#include "LSNStdFile.h"

namespace lsn {

	CStdFile::CStdFile() :
		m_pfFile( nullptr ),
		m_ui64Size( 0 ) {
	}
	CStdFile::~CStdFile() {
		Close();
	}

	// == Functions.
#ifdef _WIN32
	/**
	 * Opens a file.  The path is given in UTF-16.
	 *
	 * \param _pFile Path to the file to open.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::Open( const std::filesystem::path &_pFile ) {
		Close();
		try {
			FILE * pfFile = nullptr;
			errno_t enOpenResult = ::_wfopen_s( &pfFile, _pFile.generic_wstring().c_str(), L"rb" );
			if ( nullptr == pfFile || enOpenResult != 0 ) { return CErrors::ErrNo_T_To_Native( enOpenResult ); }

			::_fseeki64( pfFile, 0, SEEK_END );
			m_ui64Size = ::_ftelli64( pfFile );
			std::rewind( pfFile );

			m_pfFile = pfFile;
			PostLoad();
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }	// _pFile.generic_wstring() failed due to memory.
		return LSN_E_SUCCESS;
	}

	/**
	 * Creates a file.  The path is given in UTF-16.
	 *
	 * \param _pFile Path to the file to create.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::Create( const std::filesystem::path &_pFile ) {
		Close();
		try {
			FILE * pfFile = nullptr;
			errno_t enOpenResult = ::_wfopen_s( &pfFile, _pFile.generic_wstring().c_str(), L"wb" );
			if ( nullptr == pfFile || enOpenResult != 0 ) { return CErrors::ErrNo_T_To_Native( enOpenResult ); }

			m_ui64Size = 0;

			m_pfFile = pfFile;
			PostLoad();
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }	// _pFile.generic_wstring() failed due to memory.
		return LSN_E_SUCCESS;
	}

	/**
	 * Opens a file for appending.  If it does not exist it is created.  The path is given in UTF-16.
	 *
	 * \param _pFile Path to the file to open for appending.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::Append( const std::filesystem::path &_pFile ) {
		Close();
		try {
			FILE * pfFile = nullptr;
			errno_t enOpenResult = ::_wfopen_s( &pfFile, _pFile.generic_wstring().c_str(), L"ab" );
			if ( nullptr == pfFile || enOpenResult != 0 ) { return CErrors::ErrNo_T_To_Native( enOpenResult ); }

			m_ui64Size = 0;

			m_pfFile = pfFile;
			PostLoad();
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }	// _pFile.generic_wstring() failed due to memory.
		return LSN_E_SUCCESS;
	}
#else
	/**
	 * Opens a file.
	 *
	 * \param _pFile Path to the file to open.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::Open( const std::filesystem::path &_pFile ) {
		Close();
		try {
			FILE * pfFile = std::fopen( _pFile.generic_string().c_str(), "rb" );
			if ( nullptr == pfFile ) { return CErrors::ErrNo_T_To_Native( errno ); }

			std::fseek( pfFile, 0, SEEK_END );
			m_ui64Size = std::ftell( pfFile );
			std::rewind( pfFile );

			m_pfFile = pfFile;
			PostLoad();
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }	// _pFile.generic_string() failed due to memory.
		return LSN_E_SUCCESS;
	}

	/**
	 * Creates a file.
	 *
	 * \param _pFile Path to the file to create.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::Create( const std::filesystem::path &_pFile ) {
		Close();
		try {
			FILE * pfFile = std::fopen( _pFile.generic_string().c_str(), "wb" );
			if ( nullptr == pfFile ) { return CErrors::ErrNo_T_To_Native( errno ); }

			m_ui64Size = 0;

			m_pfFile = pfFile;
			PostLoad();
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }	// _pFile.generic_string() failed due to memory.
		return LSN_E_SUCCESS;
	}

	/**
	 * Opens a file for appending.  If it does not exist it is created.
	 *
	 * \param _pFile Path to the file to open for appending.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::Append( const std::filesystem::path &_pFile ) {
		Close();
		try {
			FILE * pfFile = std::fopen( _pFile.generic_string().c_str(), "ab" );
			if ( nullptr == pfFile ) { return CErrors::ErrNo_T_To_Native( errno ); }

			m_ui64Size = 0;

			m_pfFile = pfFile;
			PostLoad();
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }	// _pFile.generic_string() failed due to memory.
		return LSN_E_SUCCESS;
	}
#endif	// #ifdef _WIN32

	/**
	 * Closes the opened file.
	 */
	void CStdFile::Close() {
		if ( m_pfFile != nullptr ) {
			::fclose( m_pfFile );
			m_pfFile = nullptr;
			m_ui64Size = 0;
		}
	}

	/**
	 * Loads the opened file to memory, storing the result in _vResult.
	 *
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CStdFile::LoadToMemory( std::vector<uint8_t> &_vResult ) const {
		if ( m_pfFile != nullptr ) {
#ifdef _WIN32
			__int64 i64Pos = ::_ftelli64( m_pfFile );
			::_fseeki64( m_pfFile, 0, SEEK_END );
			__int64 i64Len = ::_ftelli64( m_pfFile );
			std::rewind( m_pfFile );
			try {
				_vResult.resize( size_t( i64Len ) );
			}
			catch ( ... ) {
				::_fseeki64( m_pfFile, i64Pos, SEEK_SET );
				return LSN_E_OUT_OF_MEMORY;
			}
			if ( __int64( _vResult.size() ) != i64Len ) {
				::_fseeki64( m_pfFile, i64Pos, SEEK_SET );
				return LSN_E_FILE_ATTRIBUTE_TOO_LARGE;
			}
			if ( std::fread( _vResult.data(), _vResult.size(), 1, m_pfFile ) != 1 ) {
				::_fseeki64( m_pfFile, i64Pos, SEEK_SET );
				return LSN_E_OPERATION_NOT_PERMITTED;
			}
			::_fseeki64( m_pfFile, i64Pos, SEEK_SET );
#else
			off_t oPos = ::ftello( m_pfFile );
			if ( oPos < 0 ) { return LSN_E_OPERATION_NOT_PERMITTED; }

			if ( ::fseeko( m_pfFile, 0, SEEK_END ) != 0 ) {
				::fseeko( m_pfFile, oPos, SEEK_SET );
				return LSN_E_OPERATION_NOT_PERMITTED;
			}

			off_t oLen = ::ftello( m_pfFile );
			if ( oLen < 0 ) {
				::fseeko( m_pfFile, oPos, SEEK_SET );
				return LSN_E_OPERATION_NOT_PERMITTED;
			}

			if ( ::fseeko( m_pfFile, 0, SEEK_SET ) != 0 ) {
				::fseeko( m_pfFile, oPos, SEEK_SET );
				return LSN_E_OPERATION_NOT_PERMITTED;
			}

			if ( oLen == 0 ) {
				_vResult.clear();
				::fseeko( m_pfFile, oPos, SEEK_SET );
				return LSN_E_SUCCESS;
			}

			if ( static_cast<uint64_t>(oLen) > static_cast<uint64_t>(std::numeric_limits<size_t>::max())) {
				::fseeko( m_pfFile, oPos, SEEK_SET );
				return LSN_E_FILE_ATTRIBUTE_TOO_LARGE;
			}

			std::vector<uint8_t> vTmp;
			try {
				vTmp.resize( static_cast<size_t>(oLen) );
			}
			catch ( ... ) {
				::fseeko( m_pfFile, oPos, SEEK_SET );
				return LSN_E_OUT_OF_MEMORY;
			}

			size_t stRead = std::fread( vTmp.data(), 1, vTmp.size(), m_pfFile );
			::fseeko( m_pfFile, oPos, SEEK_SET );
			if ( stRead != vTmp.size() ) {
				return LSN_E_OPERATION_NOT_PERMITTED;
			}

			_vResult.swap( vTmp );
#endif	// #ifdef _WIN32
			return LSN_E_SUCCESS;
		}
		return LSN_E_FILE_NOT_OPENED;
	}

	/**
	 * Writes the given data to the created file.  File must have been cerated with Create().
	 *
	 * \param _vData The data to write to the file.
	 * \return Returns true if the data was successfully written to the file.
	 */
	LSN_ERRORS CStdFile::WriteToFile( const std::vector<uint8_t> &_vData ) {
		return WriteToFile( _vData.data(), _vData.size() );
	}

	/**
	 * Writes the given data to the created file.  File must have been cerated with Create().
	 *
	 * \param _pui8Data The data to write to the file.
	 * \param _tsSize The size of the buffer to which _pui8Data points.
	 * \return Returns true if the data was successfully written to the file.
	 */
	LSN_ERRORS CStdFile::WriteToFile( const uint8_t * _pui8Data, size_t _tsSize ) {
		if ( m_pfFile != nullptr ) {
			return (std::fwrite( _pui8Data, _tsSize, 1, m_pfFile ) == 1) ? LSN_E_SUCCESS : LSN_E_OPERATION_NOT_PERMITTED;
		}
		return LSN_E_SUCCESS;
	}

	/**
	 * Moves the file pointer from the current position and returns the new position.
	 * 
	 * \param _i64Offset Amount by which to move the file pointer.
	 * \return Returns the new line position.
	 **/
	uint64_t CStdFile::MovePointerBy( int64_t _i64Offset ) const {
#ifdef _WIN32
		::_fseeki64( m_pfFile, _i64Offset, SEEK_CUR );
		return ::_ftelli64( m_pfFile );
#else
		std::fseek( m_pfFile, static_cast<long>(_i64Offset), SEEK_CUR );
		return uint64_t( std::ftell( m_pfFile ) );
#endif	// #ifdef _WIN32
	}

	/**
	 * Moves the file pointer to the given file position.
	 * 
	 * \param _ui64Pos The new file position to set.
	 * \param _bFromEnd Whether _ui64Pos is from the end of the file or not. 
	 * \return Returns the new file position.
	 **/
	uint64_t CStdFile::MovePointerTo( uint64_t _ui64Pos, bool _bFromEnd ) const {
#ifdef _WIN32
		::_fseeki64( m_pfFile, static_cast<long long>(_ui64Pos), _bFromEnd ? SEEK_END : SEEK_SET );
		return ::_ftelli64( m_pfFile );
#else
		::fseeko( m_pfFile, static_cast<off_t>(_ui64Pos), _bFromEnd ? SEEK_END : SEEK_SET );
		return ::ftello( m_pfFile );
#endif	// #ifdef _WIN32
	}

	/**
	 * Performs post-loading operations after a successful loading of the file.  m_pfFile will be valid when this is called.  Override to perform additional loading operations on m_pfFile.
	 */
	void CStdFile::PostLoad() {}

}	// namespace lsn
