/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for working with files.
 */


#pragma once

#include "../Errors/LSNErrors.h"
#include "../OS/LSNOs.h"

#include <filesystem>
#include <string>
#include <vector>

namespace lsn {

	/**
	 * Class FileBase
	 * \brief The base class for working with files.
	 *
	 * Description: The base class for working with files.
	 */
	class FileBase {
	public :
		virtual ~FileBase();


		// == Functions.
		/**
		 * Opens a file.
		 *
		 * \param _pFile Path to the file to open.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									Open( const std::filesystem::path &/*_pFile*/ ) { return LSN_E_NOT_IMPLEMENTED; }

		/**
		 * Creates a file.
		 *
		 * \param _pFile Path to the file to create.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									Create( const std::filesystem::path &/*_pFile*/ ) { return LSN_E_NOT_IMPLEMENTED; }

		/**
		 * Opens a file for appending.  If it does not exist it is created.
		 *
		 * \param _pFile Path to the file to open for appending.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									Append( const std::filesystem::path &/*_pFile*/ ) { return LSN_E_NOT_IMPLEMENTED; }

		/**
		 * Closes the opened file.
		 */
		virtual void										Close();

		/**
		 * If true, the file is an archive containing more files.
		 *
		 * \return Returns true if the file is an archive, false otherwise.
		 */
		virtual bool										IsArchive() const;

		/**
		 * Loads the opened file to memory, storing the result in _vResult.
		 *
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									LoadToMemory( std::vector<uint8_t> &_vResult ) const;

		/**
		 * Gathers the file names in the archive into an array.
		 *
		 * \param _vResult The location where to store the file names.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									GatherArchiveFiles( std::vector<std::u16string> &_vResult ) const;

		/**
		 * Extracts the given file from the archive.
		 *
		 * \param _s16File The name of the file to extract.
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									ExtractToMemory( const std::u16string &_s16File, std::vector<uint8_t> &_vResult ) const;

		/**
		 * Decompresses the whole archive into a single result.
		 *
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									ExtractToMemory( std::vector<uint8_t> &_vResult ) const;

		/**
		 * Gets the size of the file.
		 * 
		 * \return Returns the size of the file.
		 **/
		virtual uint64_t									Size() const { return 0; }

		/**
		 * Moves the file pointer from the current position and returns the new position.
		 * 
		 * \param _i64Offset Amount by which to move the file pointer.
		 * \return Returns the new line position.
		 **/
		virtual uint64_t									MovePointerBy( int64_t /*_i64Offset*/ ) const { return 0; }

		/**
		 * Moves the file pointer to the given file position.
		 * 
		 * \param _ui64Pos The new file position to set.
		 * \param _bFromEnd Whether _ui64Pos is from the end of the file or not. 
		 * \return Returns the new file position.
		 **/
		virtual uint64_t									MovePointerTo( uint64_t /*_ui64Pos*/, bool /*_bFromEnd*/ = false ) const { return 0; }

		/**
		 * Finds files/folders in a given directory.
		 * 
		 * \param _pcFolderPath The path to the directory to search.
		 * \param _pcSearchString A wildcard search string to find only certain files/folders.
		 * \param _bIncludeFolders If true, folders are included in the return.
		 * \param _vResult The return array.  Found files and folders are appended to the array.
		 * \return Returns _vResult.
		 **/
		static std::vector<std::u16string> &				FindFiles( const char16_t * _pcFolderPath, const char16_t * _pcSearchString, bool _bIncludeFolders, std::vector<std::u16string> &_vResult );
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Functions.

}	// namespace lsn
