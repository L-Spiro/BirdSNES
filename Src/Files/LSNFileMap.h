/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A file-mapping.
 */


#pragma once

#include "LSNFileBase.h"

#include <filesystem>
#include <limits>


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
		typedef int											Handle;
#define FileMap_Null										(-1)
#endif	// #ifdef _WIN32


		// == Functions.
		/**
		 * Opens a file.
		 *
		 * \param _pFile Path to the file to open.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									Open( const std::filesystem::path &_pFile );

		/**
		 * Creates a file.
		 *
		 * \param _pFile Path to the file to create.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual LSN_ERRORS									Create( const std::filesystem::path &_pFile );

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
		mutable uint64_t									m_ui64Size = 0;												/**< Size of the file. */
		mutable uint64_t									m_ui64MapStart = std::numeric_limits<uint64_t>::max();		/**< Map start. */
		mutable uint8_t *									m_pbMapBuffer = nullptr;									/**< Mapped bytes. */
		Handle												m_hFile = FileMap_Null;										/**< The file handle. */
		Handle												m_hMap = FileMap_Null;										/**< The file-mapping handle. */
		mutable uint32_t									m_ui32MapSize = 0;											/**< Mapped size. */
		bool												m_bIsEmpty = true;											/**< Is the file 0-sized? */
		bool												m_bWritable = false;										/**< Read-only or read-write? */


		// == Functions.
		/**
		 * Creates the file map.
		 * 
		 * \return Returns true if the file mapping was successfully created.
		 **/
		LSN_ERRORS											CreateFileMap();

	};

}	// namespace lsn
