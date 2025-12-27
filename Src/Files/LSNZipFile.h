/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A class for working with ZIP files.
 */


#pragma once

#include "../Compression/MiniZ/miniz.h"
#include "NN9StdFile.h"

namespace nn9 {

	/**
	 * Class ZipFile
	 * \brief A class for working with ZIP files.
	 *
	 * Description: A class for working with ZIP files.
	 */
	class ZipFile : public StdFile {
	public :
		ZipFile();
		virtual ~ZipFile();


		// == Functions.
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
		 * Gathers the file names in the archive into an array.  Call within try/catch block.
		 *
		 * \param _vResult The location where to store the file names.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									GatherArchiveFiles( std::vector<std::u16string> &_vResult ) const;

		/**
		 * Extracts the given file from the archive.
		 *
		 * \param _s16File The name of the file to extract.
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									ExtractToMemory( const std::u16string &_s16File, std::vector<uint8_t> &_vResult ) const;


	protected :
		// == Members.
		::mz_zip_archive									m_zaArchive;							/**< The miniz archive object. */


		// == Functions.
		/**
		 * Performs post-loading operations after a successful loading of the file.  m_pfFile will be valid when this is called.  Override to perform additional loading operations on m_pfFile.
		 */
		virtual void										PostLoad();

	};

}	// namespace nn9
