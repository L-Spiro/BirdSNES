/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A file-mapping.
 */


#pragma once

#include "LSNFileBase.h"

#include <string>
#include <vector>

#ifdef NN9_USE_WINDOWS
#include <Helpers/LSWHelpers.h>
#endif	// #ifdef NN9_USE_WINDOWS

namespace lsn {

	/**
	 * Class FileMap
	 * \brief A file-mapping.
	 *
	 * Description: A file-mapping.
	 */
	class FileMap : public FileBase {
	public :
		FileMap();
		virtual ~FileMap();


		// == Types.
#ifdef _WIN32
		typedef HANDLE										Handle;
#define FileMap_Null										INVALID_HANDLE_VALUE
#else
#endif	// #ifdef _WIN32


		// == Functions.
		/**
		 * Opens a file.
		 *
		 * \param _pFile Path to the file to open.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									Open( const std::filesystem::path &_pFile );

		/**
		 * Creates a file.
		 *
		 * \param _pFile Path to the file to create.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									Create( const std::filesystem::path &_pFile );

		/**
		 * Closes the opened file.
		 */
		virtual void										Close();

		/**
		 * Gets the size of the file.
		 * 
		 * \return Returns the size of the file.
		 **/
		virtual uint64_t									Size() const;


	protected :
		// == Members.
#ifdef _WIN32
		Handle												m_hFile = FileMap_Null;						/**< The file handle. */
		Handle												m_hMap = FileMap_Null;						/**< The file-mapping handle. */
		mutable PBYTE										m_pbMapBuffer = nullptr;					/**< Mapped bytes. */
		bool												m_bIsEmpty = true;							/**< Is the file 0-sized? */
		bool												m_bWritable = false;						/**< Read-only or read-write? */
		mutable uint64_t									m_ui64Size = 0;								/**< Size of the file. */
		mutable uint64_t									m_ui64MapStart = MAXUINT64;					/**< Map start. */
		mutable DWORD										m_dwMapSize = 0;							/**< Mapped size. */
#else
#endif	// #ifdef _WIN32


		// == Functions.
		/**
		 * Creates the file map.
		 * 
		 * \return Returns true if the file mapping was successfully created.
		 **/
		NN9_ERRORS											CreateFileMap();

	};

}	// namespace lsn
