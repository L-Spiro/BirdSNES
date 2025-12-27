/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A file-mapping.
 */

#include "LSNFileMap.h"


namespace lsn {

	FileMap::FileMap() {
	}
	FileMap::~FileMap() {
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
	NN9_ERRORS FileMap::Open( const std::filesystem::path &_pFile ) {
		Close();
		try {
			m_hFile = ::CreateFileW( _pFile.native().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL );

			if ( m_hFile == INVALID_HANDLE_VALUE ) {
				auto aCode = Errors::GetLastError_To_Native();
				Close();
				return aCode;
			}
			m_bWritable = true;
		}
		catch ( ... ) { return NN9_E_OUT_OF_MEMORY; }		// _pFile.native() fails if out of memory.
		return CreateFileMap();
	}

	/**
	 * Creates a file.  The path is given in UTF-16.
	 *
	 * \param _pFile Path to the file to create.
	 * \return Returns an error code indicating the result of the operation.
	 */
	NN9_ERRORS FileMap::Create( const std::filesystem::path &_pFile ) {
		Close();
		try {
			m_hFile = ::CreateFileW( _pFile.native().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL );

			if ( m_hFile == INVALID_HANDLE_VALUE ) {
				auto aCode = Errors::GetLastError_To_Native();
				Close();
				return aCode;
			}
			m_bWritable = true;
		}
		catch ( ... ) { return NN9_E_OUT_OF_MEMORY; }		// _pFile.native() fails if out of memory.


		LARGE_INTEGER largeSize;
		largeSize.QuadPart = 4 * 1024;
		if ( !::SetFilePointerEx( m_hFile, largeSize, NULL, FILE_BEGIN ) ||
			!::SetEndOfFile( m_hFile ) ) {
			auto aCode = Errors::GetLastError_To_Native();
			Close();
			return aCode;
		}

		return CreateFileMap();
	}

	/**
	 * Closes the opened file.
	 */
	void FileMap::Close() {
		if ( m_pbMapBuffer ) {
			::UnmapViewOfFile( m_pbMapBuffer );
			m_pbMapBuffer = nullptr;
		}
		if ( m_hFile != INVALID_HANDLE_VALUE ) {
			::CloseHandle( m_hMap );
			m_hMap = FileMap_Null;
		}
		if ( m_hFile != INVALID_HANDLE_VALUE ) {
			::CloseHandle( m_hFile );
			m_hFile = FileMap_Null;
		}
		m_bIsEmpty = TRUE;
		m_ui64Size = 0;
		m_ui64MapStart = MAXUINT64;
		m_dwMapSize = 0;
	}

	/**
	 * Gets the size of the file.
	 * 
	 * \return Returns the size of the file.
	 **/
	uint64_t FileMap::Size() const {
		if ( !m_ui64Size ) {
			LARGE_INTEGER liInt;
			if ( ::GetFileSizeEx( m_hFile, &liInt ) ) { m_ui64Size = liInt.QuadPart; }
		}
		return m_ui64Size;
	}

	/**
	 * Creates the file map.
	 * 
	 * \return Returns true if the file mapping was successfully created.
	 **/
	NN9_ERRORS FileMap::CreateFileMap() {
		if ( m_hFile == INVALID_HANDLE_VALUE ) {
			return NN9_E_INVALID_HANDLE;
		}
		// Can't open 0-sized files.
		m_bIsEmpty = Size() == 0;
		if ( m_bIsEmpty ) { return NN9_E_FILE_TOO_SMALL; }
		m_hMap = ::CreateFileMappingW( m_hFile,
			NULL,
			m_bWritable ? PAGE_READWRITE : PAGE_READONLY,
			0,
			0,
			NULL );

		if ( m_hFile == INVALID_HANDLE_VALUE ) {
			auto aCode = Errors::GetLastError_To_Native();
			Close();
			return aCode;
		}
		m_ui64MapStart = MAXUINT64;
		m_dwMapSize = 0;
		return NN9_E_SUCCESS;
	}
#else
	/**
	 * Opens a file.
	 *
	 * \param _pcFile Path to the file to open.
	 * \return Returns an error code indicating the result of the operation.
	 */
	NN9_ERRORS FileMap::Open( const std::filesystem::path &_pFile ) {
		return NN9_E_NOT_IMPLEMENTED;
	}

	/**
	 * Creates a file.
	 *
	 * \param _pcFile Path to the file to create.
	 * \return Returns an error code indicating the result of the operation.
	 */
	NN9_ERRORS FileMap::Create( const std::filesystem::path &_pFile ) {
		return NN9_E_NOT_IMPLEMENTED;
	}
#endif	// #ifdef _WIN32

}	// namespace lsn
