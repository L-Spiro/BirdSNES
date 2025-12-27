/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A class for working with GZ files.
 */

#include "LSNGzFile.h"
#include "../Compression/gzip/include/gzip/compress.hpp"
#include "../Compression/gzip/include/gzip/decompress.hpp"
#include "../Utilities/LSNUtilities.h"


namespace lsn {

	GzFile::GzFile() {
	}
	GzFile::~GzFile() {
		Close();
	}


	// == Functions.
	/**
	 * Closes the opened file.
	 */
	void GzFile::Close() {
		StdFile::Close();
	}

	/**
	 * If true, the file is an archive containing more files.
	 *
	 * \return Returns true if the file is an archive, false otherwise.
	 */
	bool GzFile::IsArchive() const { return false; }

	/**
	 * Decompresses the whole archive into a single result.
	 *
	 * \param _vResult The location where to store the file in memory.
	 * \return Returns an error code indicating the result of the operation.
	 */
	LSN_ERRORS GzFile::ExtractToMemory( std::vector<uint8_t> &_vResult ) const {
		std::vector<uint8_t> vData;
		auto eCode = LoadToMemory( vData );
		if ( eCode != LSN_E_SUCCESS ) { return eCode; }
		try {
			gzip::Decompressor dDecmop( SIZE_MAX );
			dDecmop.decompress( _vResult, reinterpret_cast<const char *>(vData.data()), vData.size() );
		}
		catch ( ... ) {
			return LSN_E_DECOMPRESSION_FAILED;
		}
		return LSN_E_SUCCESS;
	}

}	// namespace lsn
