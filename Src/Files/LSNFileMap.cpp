/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A file-mapping.
 */

#include "LSNFileMap.h"

#ifndef _WIN32
#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif	// #ifndef _WIN32


namespace lsn {

	FileMap::FileMap() {
	}
	FileMap::~FileMap() {
		Close();
	}

	// == Functions.
#ifdef _WIN32
	/**
	 * Opens a file.
	 *
	 * \param _pFile Path to the file to open.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS FileMap::Open( const std::filesystem::path &_pFile ) {
		Close();
		try {
			m_hFile = ::CreateFileW( _pFile.native().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL );

			if ( m_hFile == FileMap_Null ) {
				auto aCode = Errors::GetLastError_To_Native();
				Close();
				return aCode;
			}
			m_bWritable = true;
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }		// _pFile.native() fails if out of memory.
		return CreateFileMap();
	}

	/**
	 * Creates a file.
	 *
	 * \param _pFile Path to the file to create.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS FileMap::Create( const std::filesystem::path &_pFile ) {
		Close();
		try {
			m_hFile = ::CreateFileW( _pFile.native().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL );

			if ( m_hFile == FileMap_Null ) {
				auto aCode = Errors::GetLastError_To_Native();
				Close();
				return aCode;
			}
			m_bWritable = true;
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }		// _pFile.native() fails if out of memory.


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
		if ( m_hMap != FileMap_Null ) {
			::CloseHandle( m_hMap );
			m_hMap = FileMap_Null;
		}
		if ( m_hFile != FileMap_Null ) {
			::CloseHandle( m_hFile );
			m_hFile = FileMap_Null;
		}
		m_bIsEmpty = TRUE;
		m_ui64Size = 0;
		m_ui64MapStart = MAXUINT64;
		m_ui32MapSize = 0;
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
	LSN_ERRORS FileMap::CreateFileMap() {
		if ( m_hFile == FileMap_Null ) {
			return LSN_E_INVALID_HANDLE;
		}
		
		LARGE_INTEGER liInt;
		if ( !::GetFileSizeEx( m_hFile, &liInt ) ) {
			auto aCode = Errors::GetLastError_To_Native();
			Close();
			return (aCode == LSN_E_OTHER) ? LSN_E_STAT_FAILED : aCode;
		}
		m_ui64Size = static_cast<uint64_t>(liInt.QuadPart);
		
		// Can't open 0-sized files.
		m_bIsEmpty = Size() == 0;
		if ( m_bIsEmpty ) { return LSN_E_FILE_TOO_SMALL; }
		m_hMap = ::CreateFileMappingW( m_hFile,
			NULL,
			m_bWritable ? PAGE_READWRITE : PAGE_READONLY,
			0,
			0,
			NULL );

		if ( m_hMap == FileMap_Null ) {
			auto aCode = Errors::GetLastError_To_Native();
			Close();
			return aCode;
		}
		m_ui64MapStart = MAXUINT64;
		m_ui32MapSize = 0;
		return LSN_E_SUCCESS;
	}
#else

	/**
	 * Opens a file.
	 *
	 * \param _pFile Path to the file to open.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS FileMap::Open( const std::filesystem::path &_pFile ) {
		Close();
		try {
			auto sPath = _pFile.native();
			m_hFile = ::open( sPath.c_str(), O_RDONLY );
			if ( m_hFile == FileMap_Null ) {
				auto aCode = Errors::ErrNo_T_To_Native( errno );
				Close();
				return aCode;
			}
			m_bWritable = false;
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }		// _pFile.native() can fail if out of memory.

		return CreateFileMap();
	}

	/**
	 * Creates a file.
	 *
	 * \param _pFile Path to the file to create.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS FileMap::Create( const std::filesystem::path &_pFile ) {
		Close();
		try {
			auto sPath = _pFile.native();
			m_hFile = ::open( sPath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644 );
			if ( m_hFile == FileMap_Null ) {
				auto aCode = Errors::ErrNo_T_To_Native( errno );
				Close();
				return aCode;
			}
			m_bWritable = true;
		}
		catch ( ... ) { return LSN_E_OUT_OF_MEMORY; }		// _pFile.native() can fail if out of memory.

		if ( ::ftruncate( m_hFile, 4 * 1024 ) != 0 ) {
			auto aCode = Errors::ErrNo_T_To_Native( errno );
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
			if ( m_ui32MapSize ) { ::munmap( m_pbMapBuffer, static_cast<size_t>(m_ui32MapSize) ); }
			m_pbMapBuffer = nullptr;
		}
		if ( m_hMap != FileMap_Null ) {
			::close( m_hMap );
			m_hMap = FileMap_Null;
		}
		if ( m_hFile != FileMap_Null ) {
			::close( m_hFile );
			m_hFile = FileMap_Null;
		}
		m_bIsEmpty = true;
		m_ui64Size = 0;
		m_ui64MapStart = std::numeric_limits<uint64_t>::max();
		m_ui32MapSize = 0;
	}

	/**
	 * Gets the size of the file.
	 *
	 * \return Returns the size of the file.
	 **/
	uint64_t FileMap::Size() const {
		if ( !m_ui64Size ) {
			struct stat sStat;
			if ( ::fstat( m_hFile, &sStat ) == 0 ) { m_ui64Size = static_cast<uint64_t>(sStat.st_size); }
		}
		return m_ui64Size;
	}

	/**
	 * Creates the file map.
	 *
	 * \return Returns true if the file mapping was successfully created.
	 **/
	LSN_ERRORS FileMap::CreateFileMap() {
		if ( m_hFile == FileMap_Null ) {
			return LSN_E_INVALID_HANDLE;
		}
		// Can't open 0-sized files.
		m_bIsEmpty = Size() == 0;
		if ( m_bIsEmpty ) { return LSN_E_FILE_TOO_SMALL; }
		m_hMap = ::dup( m_hFile );
		if ( m_hMap == FileMap_Null ) {
			auto aCode = Errors::ErrNo_T_To_Native( errno );
			Close();
			return aCode;
		}
		m_ui64MapStart = std::numeric_limits<uint64_t>::max();
		m_ui32MapSize = 0;
		return LSN_E_SUCCESS;
	}

#endif	// #ifdef _WIN32

}	// namespace lsn
