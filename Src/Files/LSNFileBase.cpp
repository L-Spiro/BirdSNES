/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for working with files.
 */


#include "LSNFileBase.h"
#include "../OS/LSNOs.h"
#include "../Utilities/LSNUtilities.h"

#ifndef _WIN32
#include <filesystem>
#endif	// #ifndef _WIN32

namespace lsn {

	CFileBase::~CFileBase() {}

	// == Functions.
	/**
	 * Closes the opened file.
	 */
	void CFileBase::Close() {}

	/**
	 * If true, the file is an archive containing more files.
	 *
	 * \return Returns true if the file is an archive, false otherwise.
	 */
	bool CFileBase::IsArchive() const { return false; }

	/**
	 * Loads the opened file to memory, storing the result in _vResult.
	 *
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CFileBase::LoadToMemory( std::vector<uint8_t> &_vResult ) const { static_cast<void>(_vResult); return LSN_E_NOT_IMPLEMENTED; }

	/**
	 * Gathers the file names in the archive into an array.
	 *
	 * \param _vResult The location where to store the file names.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CFileBase::GatherArchiveFiles( std::vector<std::u16string> &_vResult ) const { static_cast<void>(_vResult); return LSN_E_NOT_IMPLEMENTED; }

	/**
	 * Extracts the given file from the archive.
	 *
	 * \param _s16File The name of the file to extract.
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CFileBase::ExtractToMemory( const std::u16string &_s16File, std::vector<uint8_t> &_vResult ) const { static_cast<void>(_s16File); static_cast<void>(_vResult); return LSN_E_NOT_IMPLEMENTED; }

	/**
	 * Decompresses the whole archive into a single result.
	 *
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS CFileBase::ExtractToMemory( std::vector<uint8_t> &_vResult ) const { static_cast<void>(_vResult); return LSN_E_NOT_IMPLEMENTED; }

	/**
	 * Finds files/folders in a given directory.
	 * 
	 * \param _pcFolderPath The path to the directory to search.
	 * \param _pcSearchString A wildcard search string to find only certain files/folders.
	 * \param _bIncludeFolders If true, folders are included in the return.
	 * \param _vResult The return array.  Found files and folders are appended to the array.
	 * \return Returns _vResult.
	 **/
	std::vector<std::u16string> & CFileBase::FindFiles( const char16_t * _pcFolderPath, const char16_t * _pcSearchString, bool _bIncludeFolders, std::vector<std::u16string> &_vResult ) {
#ifdef _WIN32
		std::filesystem::path sPath = std::filesystem::path( _pcFolderPath ).make_preferred();

		std::filesystem::path sSearch;
		if ( _pcSearchString ) { sSearch = std::filesystem::path( _pcSearchString ).make_preferred(); }
		else { sSearch = L"*"; }


		std::filesystem::path sSearchPath = (sPath / sSearch).make_preferred();
		// Add the "\\?\" prefix to the path to support long paths
		std::wstring wsSearchPath = sSearchPath.native();
		if ( wsSearchPath.compare( 0, 4, L"\\\\?\\" ) != 0 ) {
			wsSearchPath = L"\\\\?\\" + wsSearchPath;
		}

		WIN32_FIND_DATAW wfdData;
		HANDLE hDir = ::FindFirstFileW( wsSearchPath.c_str(), &wfdData );
		if ( INVALID_HANDLE_VALUE == hDir ) { return _vResult; }
		
		do {
			if ( wfdData.cFileName[0] == L'.' ) { continue; }
			bool bIsFolder = ((wfdData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
			if ( !_bIncludeFolders && bIsFolder ) { continue; }
			try {
				// Construct the full path to the file
				std::filesystem::path pFilePath = sPath / wfdData.cFileName;
				pFilePath = pFilePath.make_preferred();

				// Add the "\\?\" prefix if it's not already present
				std::u16string wsFilePath = pFilePath.u16string();
				if ( wsFilePath.compare( 0, 4, u"\\\\?\\" ) != 0 ) {
					wsFilePath = u"\\\\?\\" + wsFilePath;
				}

				_vResult.push_back( wsFilePath );
			}
			catch ( ... ) {
				::FindClose( hDir );
				return _vResult;
			}
		} while ( ::FindNextFileW( hDir, &wfdData ) );

		::FindClose( hDir );
		return _vResult;
#else
		// Convert char16_t * to std::u16string.
		std::u16string sPath = _pcFolderPath;
		while ( sPath.size() && sPath.back() == u'\\' ) {
			sPath.pop_back();
		}
		sPath.push_back( u'/' );  // Use forward slash for UNIX-like path.
		
		std::u16string sSearch = _pcSearchString ? _pcSearchString : u"*";
		
		for ( const auto & entry : std::filesystem::directory_iterator( std::filesystem::path( sPath.begin(), sPath.end() ) ) ) {
			const auto & path = entry.path();
			bool isDirectory = entry.is_directory();

			if ( !_bIncludeFolders && isDirectory ) {
				continue;
			}

			std::u16string sFilename = path.filename().u16string();
			if ( sFilename[0] == u'.' ) {
				continue;  // Skip hidden files and directories
			}

			_vResult.push_back(std::u16string( sPath.begin(), sPath.end()) + sFilename );
		}

		return _vResult;

#endif	// #ifdef _WIN32
	}

}	// namespace lsn
