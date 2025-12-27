/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A class for working with GZ files.
 */


#pragma once

#include "NN9StdFile.h"

namespace nn9 {

	/**
	 * Class GzFile
	 * \brief A class for working with GZ files.
	 *
	 * Description: A class for working with GZ files.
	 */
	class GzFile : public StdFile {
	public :
		GzFile();
		virtual ~GzFile();


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
		 * Decompresses the whole archive into a single result.
		 *
		 * \param _vResult The location where to store the file in memory.
		 * \return Returns an error code indicating the result of the operation.
		 */
		virtual NN9_ERRORS									ExtractToMemory( std::vector<uint8_t> &_vResult ) const;

		/**
		 * Decompresses a file to memory.
		 * 
		 * \param _pcFile The path to the file to open and decompress.
		 * \param _vResult The Holds the resulting decompressed file data.
		 * \return Returns an error code indicating the result of the operation.
		 **/
		template <typename _tStrType = char8_t>
		static NN9_ERRORS									ExtractToMemory( const _tStrType * _pcFile, std::vector<uint8_t> &_vResult );


	protected :
		// == Members.
		std::vector<uint8_t>								m_vData;								/**< The compressed file data. */


	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Functions.
	/**
	 * Decompresses a file to memory.
	 * 
	 * \param _pcFile The path to the file to open and decompress.
	 * \param _vResult The Holds the resulting decompressed file data.
	 * \return Returns an error code indicating the result of the operation.
	 **/
	template <typename _tStrType>
	NN9_ERRORS GzFile::ExtractToMemory( const _tStrType * _pcFile, std::vector<uint8_t> &_vResult ) {
		GzFile gfFile;
		auto eCode = gfFile.Open( _pcFile );
		if ( eCode != NN9_E_SUCCESS ) { return eCode; }
		return gfFile.ExtractToMemory( _vResult );
	}

}	// namespace nn9
