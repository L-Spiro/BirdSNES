/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Useful utility functions.
 */

#include "NN9Utilities.h"
#include "../Files/NN9StdFile.h"
#include "../OS/NN9Os.h"

#include <random>

namespace nn9 {

	// == Members.
#ifndef NN9_CPUID
	int Utilities::m_iNeon = 3;						/**< Tracks support for NEON. */
	int Utilities::m_iBf16 = 3;						/**< Tracks support for BF16. */
	int Utilities::m_iFp16 = 3;						/**< Tracks support for FP16. */
	int Utilities::m_iSve = 3;						/**< Tracks support for SVE. */
#endif	// #ifndef NN9_CPUID

	// == Functions.
	/**
	 * Gets the next UTF-16 character from a stream or error (NN9_UTF_INVALID).
	 * 
	 * \param _pwcString The string to parse.
	 * \param _sLen The length of the string to which _pwcString points.
	 * \param _psSize Optional pointer to a size_t that will contain the number of characters eaten from _pwcString during the parsing.
	 * \return Returns the next character as a UTF-32 code.
	 **/
	char32_t Utilities::NextUtf16Char( const char16_t * _pwcString, size_t _sLen, size_t * _psSize ) {
		if ( _sLen == 0 ) { return 0; }

		// Get the low bits (which may be all there are).
		uint32_t ui32Ret = (*reinterpret_cast<const uint16_t *>(_pwcString));

		uint32_t ui32Top = ui32Ret & 0xFC00U;
		// Check to see if this is a surrogate pair.
		if ( ui32Top == 0xD800U ) {
			if ( _sLen < 2 ) {
				// Not enough space to decode correctly.
				if ( _psSize ) {
					(*_psSize) = 1;
				}
				return NN9_UTF_INVALID;
			}

			// Need to add the next character to it.
			// Remove the 0xD800.
			ui32Ret &= ~0xD800U;
			ui32Ret <<= 10;

			// Get the second set of bits.
			uint32_t ui32Next = (*reinterpret_cast<const uint16_t *>(++_pwcString));
			if ( (ui32Next & 0xFC00U) != 0xDC00U ) {
				// Invalid second character.
				// Standard defines this as an error.
				if ( _psSize ) {
					(*_psSize) = 1;
				}
				return NN9_UTF_INVALID;
			}
			if ( _psSize ) {
				(*_psSize) = 2;
			}

			ui32Next &= ~0xDC00U;

			// Add the second set of bits.
			ui32Ret |= ui32Next;

			return ui32Ret + 0x10000U;
		}

		if ( _psSize ) {
			(*_psSize) = 1;
		}
		return ui32Ret;
	}

	/**
	 * Gets the next UTF-8 character from a stream or error (NN9_UTF_INVALID).
	 * 
	 * \param _pcString The string to parse.
	 * \param _sLen The length of the string to which _pcString points.
	 * \param _psSize Optional pointer to a size_t that will contain the number of characters eaten from _pcString during the parsing.
	 * \return Returns the next character as a UTF-32 code.
	 **/
	char32_t Utilities::NextUtf8Char( const char8_t * _pcString, size_t _sLen, size_t * _psSize ) {
		if ( _sLen == 0 ) { if ( _psSize ) { (*_psSize) = 0; } return 0; }

		// Get the low bits (which may be all there are).
		uint32_t ui32Ret = (*reinterpret_cast<const uint8_t *>(_pcString));

		// The first byte is a special case.
		if ( (ui32Ret & 0x80U) == 0 ) {
			// We are done.
			if ( _psSize ) { (*_psSize) = 1; }
			return ui32Ret;
		}

		// We are in a multi-byte sequence.  Get bits from the top, starting
		//	from the second bit.
		uint32_t I = 0x20;
		uint32_t ui32Len = 2;
		uint32_t ui32Mask = 0xC0U;
		while ( ui32Ret & I ) {
			// Add this bit to the mask to be removed later.
			ui32Mask |= I;
			I >>= 1;
			++ui32Len;
			if ( I == 0 ) {
				// Invalid sequence.
				if ( _psSize ) {
					(*_psSize) = 1;
				}
				return NN9_UTF_INVALID;
			}
		}

		// Bounds checking.
		if ( ui32Len > _sLen ) {
			if ( _psSize ) { (*_psSize) = _sLen; }
			return NN9_UTF_INVALID;
		}

		// We know the size now, so set it.
		// Even if we return an invalid character we want to return the correct number of
		//	bytes to skip.
		if ( _psSize ) { (*_psSize) = ui32Len; }

		// If the length is greater than 4, it is invalid.
		if ( ui32Len > 4 ) {
			// Invalid sequence.
			return NN9_UTF_INVALID;
		}

		// Mask out the leading bits.
		ui32Ret &= ~ui32Mask;

		// For every trailing bit, add it to the final value.
		for ( I = ui32Len - 1; I--; ) {
			uint32_t ui32This = (*reinterpret_cast<const uint8_t *>(++_pcString));
			// Validate the byte.
			if ( (ui32This & 0xC0U) != 0x80U ) {
				// Invalid.
				return NN9_UTF_INVALID;
			}

			ui32Ret <<= 6;
			ui32Ret |= (ui32This & 0x3F);
		}

		// Finally done.
		return ui32Ret;
	}

	/**
	 * Gets the size of the given UTF-8 character.
	 * 
	 * \param _pcString Pointer to the UTF-8 characters to decode.
	 * \param _sLen The number of characters to which _pcString points.
	 * \return Returns the size of the UTF-8 character to which _pcString points.
	 **/
	size_t Utilities::Utf8CharSize( const char8_t * _pcString, size_t _sLen ) {
		if ( _sLen == 0 ) { return 0; }

		// Get the low bits (which may be all there are).
		uint32_t ui32Ret = (*reinterpret_cast<const uint8_t *>(_pcString));

		// The first byte is a special case.
		if ( (ui32Ret & 0x80U) == 0 ) {
			// We are done.
			return 1;
		}

		// We are in a multi-byte sequence.  Get bits from the top, starting
		//	from the second bit.
		uint32_t I = 0x20;
		size_t sLen = 2;
		while ( ui32Ret & I ) {
			// Add this bit to the mask to be removed later.
			I >>= 1;
			++sLen;
			if ( I == 0 ) { return 1; }
		}

		// Bounds checking.
		if ( sLen > _sLen ) {
			return _sLen;
		}
		return sLen;
	}

	/**
	 * Converts a UTF-32 character to a UTF-16 character.
	 * 
	 * \param _c32Utf32 The UTF-32 character to convert to UTF-16.
	 * \param _ui32Len Holds the returned number of 16-bit characters held in the return value.
	 * \return Returns up to 2 UTF-16 characters.
	 **/
	uint32_t Utilities::Utf32ToUtf16( char32_t _c32Utf32, uint32_t &_ui32Len ) {
		if ( _c32Utf32 > 0x10FFFF ) {
			_ui32Len = 1;
			return NN9_UTF_INVALID;
		}
		if ( 0x10000 <= _c32Utf32 ) {
			_ui32Len = 2;

			// Break into surrogate pairs.
			_c32Utf32 -= 0x10000UL;
			uint32_t ui32Hi = (_c32Utf32 >> 10) & 0x3FF;
			uint32_t ui32Low = _c32Utf32 & 0x3FF;

			return (0xD800 | ui32Hi) |
				((0xDC00 | ui32Low) << 16);
		}
		_ui32Len = 1;
		return _c32Utf32;
	}

	/**
	 * Converts a UTF-32 character to a UTF-8 character.
	 * 
	 * \param _c32Utf32 The UTF-32 character to convert to UTF-8.
	 * \param _ui32Len Holds the returned number of 16-bit characters held in the return value.
	 * \return Returns up to 4 UTF-8 characters.
	 **/
	uint32_t Utilities::Utf32ToUtf8( char32_t _c32Utf32, uint32_t &_ui32Len ) {
		// Handle the single-character case separately since it is a special case.
		if ( _c32Utf32 < 0x80U ) {
			_ui32Len = 1;
			return _c32Utf32;
		}

		// Upper bounds checking.
		if ( _c32Utf32 > 0x10FFFFU ) {
			// Invalid character.  How do we handle it?
			// Return a default character.
			_ui32Len = 1;
			return NN9_UTF_INVALID;
		}

		// Every other case uses bit markers.
		// Start from the lowest encoding and check upwards.
		uint32_t ui32High = 0x00000800U;
		uint32_t ui32Mask = 0xC0;
		_ui32Len = 2;
		while ( _c32Utf32 >= ui32High ) {
			ui32High <<= 5;
			ui32Mask = (ui32Mask >> 1) | 0x80U;
			++_ui32Len;
		}

		uint32_t ui32Char = _c32Utf32;
		// Encode the first byte.
		uint32_t ui32BottomMask = ~((ui32Mask >> 1) | 0xFFFFFF80U);
		uint32_t ui32Ret = ui32Mask | ((ui32Char >> ((_ui32Len - 1) * 6)) & ui32BottomMask);
		// Now fill in the rest of the bits.
		uint32_t ui32Shift = 8;
		for ( uint32_t I = _ui32Len - 1; I--; ) {
			// Shift down, mask off 6 bits, and add the 10xxxxxx flag.
			uint32_t ui32This = ((ui32Char >> (I * 6)) & 0x3F) | 0x80;

			ui32Ret |= ui32This << ui32Shift;
			ui32Shift += 8;
		}

		return ui32Ret;
	}

	/**
	 * Reads a line from a buffer.
	 * 
	 * \param _vBuffer The buffer from which to read a line.
	 * \param _stPos The current position inside the buffer, updated on return.
	 * \return Returns the line read from the file.
	 **/
	std::string Utilities::ReadLine( const std::vector<uint8_t> &_vBuffer, size_t &_stPos ) {
		std::string sTmp;
		while ( _stPos < _vBuffer.size() ) {
			uint8_t ui8This = _vBuffer[_stPos++];
			if ( ui8This == '\r' ) { continue; }
			if ( ui8This == '\n' ) { break; }
			sTmp.push_back( ui8This );
		}

		return sTmp;
	}

	/**
	 * Tokenizes a string by a given character.
	 * 
	 * \param _sString The string to tokenize.
	 * \param _vtDelimiter The character by which to deliminate the string into sections.
	 * \param _bAllowEmptyStrings If true, the return value could contain empty strings when the delimiter is found more than once in a row.
	 * \return Returns a vector containing all of the tokens.
	 **/
	std::vector<std::string> Utilities::Tokenize( const std::string &_sString, std::string::value_type _vtDelimiter, bool _bAllowEmptyStrings ) {
		std::vector<std::string> vRet;
		std::string sTmp;
		for ( size_t I = 0; I < _sString.size(); ++I ) {
			if ( _sString[I] == _vtDelimiter ) {
				if ( _bAllowEmptyStrings || sTmp.size() ) {
					vRet.push_back( sTmp );
					sTmp.clear();
				}
			}
			else {
				sTmp.push_back( _sString[I] );
			}
		}
		if ( sTmp.size() ) {
			vRet.push_back( sTmp );
		}
		return vRet;
	}

	/**
	 * Creates an ASCII path from the given file name, even if it is already an ASCII path.
	 *
	 * \param _sPath The input path, including the file name.
	 * \param _pAsciiPath The output folder.
	 * \param _pAsciiFileName The output file name.
	 * \return Returns true if allocation of all strings succeeded.  Failure indicates a memory failure.
	 **/
	bool Utilities::CreateAsciiPath( const std::u16string &_sPath, std::filesystem::path &_pAsciiPath, std::filesystem::path &_pAsciiFileName ) {
		try {
			_pAsciiFileName = Append( L"Tmp.", std::filesystem::path( _sPath ).extension().u16string() );
			_pAsciiPath = std::filesystem::temp_directory_path();
			if ( HasUtf( _pAsciiPath.c_str(), _pAsciiPath.native().size() ) ) {
				_pAsciiPath = std::filesystem::path( _sPath ).root_path();
			}
			_pAsciiPath /= "SurfaceLevel2Tmp";

			const char cCharSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			std::random_device rdDevice;
			std::mt19937 mGenerator( rdDevice() );
			std::uniform_int_distribution<> uidDist( 0, std::size( cCharSet ) - 2 );

			for ( size_t I = 0; I < 8; ++I ) {
				_pAsciiPath += cCharSet[uidDist(mGenerator)];
			}

			return true;
		}
		catch ( ... ) {
			return false;
		}
	}

	/**
	 * Downloads a file and saves it to the given path.
	 * 
	 * \param _pcUrl The URL to the file to download.
	 * \param _pcPath The path to which to save the given file.
	 * \return Returns an error code indicating the result of the operation.
	 **/
	NN9_ERRORS Utilities::DownloadFile( const std::u16string &_pcUrl, const std::u16string &_pcPath ) {
		NN9_ERRORS eCode;
		{
			// Must verify that the download folder exists.
			/*try {
				std::filesystem::path pPath = _pcPath;
				if ( !pPath.has_filename() ) { return NN9_E_INVALID_NAME; }
				if ( !std::filesystem::exists( std::filesystem::absolute( pPath.make_preferred().remove_filename() ) ) ) { return NN9_E_FOLDER_NOT_FOUND; }
			}
			catch ( ... ) { return NN9_E_FOLDER_NOT_FOUND; }*/


			NN9_CURL cCurl( ::curl_easy_init() );

			if ( !cCurl.Valid() ) { return NN9_E_CURL_INIT_FAILED; }
#define NN9_CHECK							if ( aCurlCode != CURLE_OK ) { return Errors::LibCurl_To_Native( aCurlCode ); }
			StdFile sfFile;
			auto aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_URL, Utf16ToUtf8( _pcUrl ).c_str() );
			NN9_CHECK;
			 // Set the User-Agent to mimic a web browser.
			aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_USERAGENT, "Mozilla/5.0" );
			NN9_CHECK;
			// Follow redirects if necessary.
			aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_FOLLOWLOCATION, 1L );
			// Enable verbose output for debugging.
			/*aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_VERBOSE, 1L );
			NN9_CHECK;*/


			NN9_CHECK;
			// Write data to our file.
			aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_WRITEFUNCTION, WriteCurlData );
			NN9_CHECK;
			aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_WRITEDATA, &sfFile );
			NN9_CHECK;
			// Set SSL options.
			aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_SSL_VERIFYPEER, 1L ); // Enable certificate validation.
			NN9_CHECK;
			aCurlCode = ::curl_easy_setopt( cCurl.pcCurl, CURLOPT_SSL_VERIFYHOST, 2L ); // Verify that the host name matches the certificate.
			NN9_CHECK;

			std::filesystem::create_directories( std::filesystem::absolute( std::filesystem::path( _pcPath ) ).remove_filename() );
			eCode = sfFile.Create( _pcPath.c_str() );
			if ( eCode == NN9_E_SUCCESS ) {
				aCurlCode = ::curl_easy_perform( cCurl.pcCurl );

				// Check HTTP response code.
				//long lRespCode = 0;
				//aCurlCode = ::curl_easy_getinfo( cCurl.pcCurl, CURLINFO_RESPONSE_CODE, &lRespCode );
				//if ( lRespCode != 200 ) {
				//	std::cerr << "Failed to download file. HTTP Response Code: " << lRespCode << std::endl;
				//	//return Errors::LibCurl_To_Native( aCurlCode );
				//}
				NN9_CHECK;
			}

        
			//::curl_easy_cleanup( cCurl.pcCurl );	// Called by NN9_CURL::~NN9_CURL().
		}


		auto aCrc = StdFile::Crc( _pcPath.c_str() );
		std::wcout << "Downloaded file \"" << reinterpret_cast<const wchar_t *>(_pcPath.c_str()) << "\": " << std::uppercase << std::hex << std::setfill( L'0' ) << std::setw( 8 ) << aCrc << std::endl;

		return eCode;
	}

	/**
	 * Callback for writing the file during curl downloading.
	 * 
	 * \param _pvPtr Pointer to the data to write.
	 * \param _sSize The size of each data item.
	 * \param _sMem The total number of data items to write.
	 * \param _pvFile Pointer to a StdFile object used for the write process.
	 * \return Returns the number of bytes actually writtem.
	 **/
	size_t NN9_CDECL Utilities::WriteCurlData( void * _pvPtr, size_t _sSize, size_t _sMem, void * _pvFile ) {
		StdFile * psfFile = reinterpret_cast<StdFile *>(_pvFile);
		size_t sTotal = _sSize * _sMem;
		if ( psfFile->WriteToFile( static_cast<uint8_t *>(_pvPtr), sTotal ) == NN9_E_SUCCESS ) {
			return sTotal;
		}
		return 0;
	}

	/**
	 * Downloads the MNIST files to the given folder.
	 * 
	 * \param _pcFolder The path to the folder to where to download the MNIST files.
	 * \return Returns an error code indicating the result of the operation.
	 **/
	NN9_ERRORS Utilities::DownloadMnist( const std::u16string &_pcFolder ) {
		static std::u16string sUrls[] = {
			u"https://ossci-datasets.s3.amazonaws.com/mnist/train-images-idx3-ubyte.gz",
			u"https://ossci-datasets.s3.amazonaws.com/mnist/train-labels-idx1-ubyte.gz",
			u"https://ossci-datasets.s3.amazonaws.com/mnist/t10k-images-idx3-ubyte.gz",
			u"https://ossci-datasets.s3.amazonaws.com/mnist/t10k-labels-idx1-ubyte.gz"
		};

		static std::u16string sFileNames[] = {
			u"train-images-idx3-ubyte.gz",
			u"train-labels-idx1-ubyte.gz",
			u"t10k-images-idx3-ubyte.gz",
			u"t10k-labels-idx1-ubyte.gz"
		};
		static uint32_t ui32Crc[] = {
			0xEB392171,
			0x28EE680A,
			0xDF9322EE,
			0x5C1CF43B,
		};

		try {
			std::filesystem::path pPath = _pcFolder;
			pPath = std::filesystem::absolute( pPath );
			std::filesystem::create_directories( pPath );
			if ( !std::filesystem::exists( pPath ) ) { return NN9_E_FOLDER_NOT_FOUND; }

			for ( size_t I = 0; I < std::size( sUrls ); ++I ) {
				std::filesystem::path pThisPath = pPath;
				pThisPath /= sFileNames[I];

				auto aCrc = StdFile::Crc( pThisPath.u16string().c_str() );
				if ( aCrc != ui32Crc[I] ) {
					auto aCode = DownloadFile( sUrls[I], pThisPath.u16string() );
					if ( aCode != NN9_E_SUCCESS ) { return aCode; }
				}
			}
		}
		catch ( ... ) { return NN9_E_OUT_OF_MEMORY; }
		return NN9_E_SUCCESS;
	}

	/**
	 * Gets the lowest power-of-2 value not below the given input value.
	 *
	 * \param _ui32Value Value for which to derive the lowest power-of-2 value not under this value.
	 * \return Returns the lowest power-of-2 value not below the given input value.
	 */
	uint32_t Utilities::GetLowestPo2( uint32_t _ui32Value ) {
		if ( !_ui32Value ) { return 0; }
#ifdef NN9_X86
		// On x86 processors there is an instruction that gets the highest-
		//	set bit automatically.
		uint32_t ui32Ret;
		NN9_ASM_BEGIN
			xor eax, eax
			bsr eax, _ui32Value
			mov ui32Ret, eax
		NN9_ASM_END
		ui32Ret = 1 << ui32Ret;
		return (ui32Ret == _ui32Value) ? ui32Ret : ui32Ret << 1;
#else	// NN9_X86
		// Get it the hard way.
		uint32_t ui32Ret = 1;
		while ( ui32Ret < _ui32Value ) { ui32Ret <<= 1; }

		// By now, ui32Ret either equals _ui32Value or is the next power of 2 up.
		// If they are equal, _ui32Value is already a power of 2.
		return ui32Ret;
#endif	// NN9_X86
	}

}	// namespace nn9
