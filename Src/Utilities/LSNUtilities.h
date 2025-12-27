/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Useful utility functions.
 */


#pragma once

#include "../Errors/NN9Errors.h"
#include "../Foundation/NN9FeatureSet.h"
#include "../OS/NN9Os.h"

#include <cassert>
#include <cmath>
#include <curl/curl.h>
#include <filesystem>
#include <numbers>
#include <set>
#include <string>
#include <vector>



#ifndef NN9_PI
#define NN9_PI												3.141592653589793115997963468544185161590576171875	// 3.14159265358979323846264338327950288419716939937510 rounded to the nearest representable double.
#endif	// #ifndef NN9_PI

#ifndef NN9_ROUND_UP
/** Round up to the next nearest Xth, where X is a power of 2. */
#define NN9_ROUND_UP( VALUE, X )							((VALUE) + (((X) - (VALUE) & ((X) - 1)) & ((X) - 1)))
#endif	// #ifndef NN9_ROUND_UP

#ifndef NN9_UTF_INVALID
#define NN9_UTF_INVALID										~static_cast<uint32_t>(0)
#endif	// EE_UTF_INVALID



namespace nn9 {

	/**
	 * Class Utilities
	 * \brief Useful utility functions.
	 *
	 * Description: Useful utility functions.
	 */
	class Utilities {
	public :
		// ===============================
		// UTF
		// ===============================
		/**
		 * Gets the next UTF-32 character from a stream or error (EE_UTF_INVALID).  _tCharType should typically be char32_t or a 32-bit integer.
		 * 
		 * \param _pcString The string to parse.
		 * \param _sLen The length of the string to which _pcString points.
		 * \param _psSize Optional pointer to a size_t that will contain the number of characters eaten from _pcString during the parsing.
		 * \return Returns the next character as a UTF-32 code.
		 **/
		template <typename _tCharType>
		static inline char32_t								NextUtf32Char( const _tCharType * _pcString, size_t _sLen, size_t * _psSize = nullptr ) {
			if ( _sLen == 0 ) {
				if ( _psSize ) { (*_psSize) = 0; }
				return 0;
			}
			if ( _psSize ) { (*_psSize) = 1; }
			uint32_t ui32Ret = (*_pcString);
			if ( ui32Ret & 0xFFE00000 ) { return NN9_UTF_INVALID; }
			return ui32Ret;
		}

		/**
		 * Gets the next UTF-16 character from a stream or error (EE_UTF_INVALID).
		 * 
		 * \param _pwcString The string to parse.
		 * \param _sLen The length of the string to which _pwcString points.
		 * \param _psSize Optional pointer to a size_t that will contain the number of characters eaten from _pwcString during the parsing.
		 * \return Returns the next character as a UTF-32 code.
		 **/
		static char32_t										NextUtf16Char( const char16_t * _pwcString, size_t _sLen, size_t * _psSize = nullptr );

		/**
		 * Gets the next UTF-8 character from a stream or error (EE_UTF_INVALID).
		 * 
		 * \param _pcString The string to parse.
		 * \param _sLen The length of the string to which _pcString points.
		 * \param _psSize Optional pointer to a size_t that will contain the number of characters eaten from _pcString during the parsing.
		 * \return Returns the next character as a UTF-32 code.
		 **/
		static char32_t										NextUtf8Char( const char8_t * _pcString, size_t _sLen, size_t * _psSize = nullptr );

		/**
		 * Gets the size of the given UTF-8 character.
		 * 
		 * \param _pcString Pointer to the UTF-8 characters to decode.
		 * \param _sLen The number of characters to which _pcString points.
		 * \return Returns the size of the UTF-8 character to which _pcString points.
		 **/
		static size_t										Utf8CharSize( const char8_t * _pcString, size_t _sLen );

		/**
		 * Converts a UTF-32 character to a UTF-16 character.
		 * 
		 * \param _c32Utf32 The UTF-32 character to convert to UTF-16.
		 * \param _ui32Len Holds the returned number of 16-bit characters held in the return value.
		 * \return Returns up to 2 UTF-16 characters.
		 **/
		static uint32_t										Utf32ToUtf16( char32_t _c32Utf32, uint32_t &_ui32Len );

		/**
		 * Converts a UTF-32 character to a UTF-8 character.
		 * 
		 * \param _c32Utf32 The UTF-32 character to convert to UTF-8.
		 * \param _ui32Len Holds the returned number of 16-bit characters held in the return value.
		 * \return Returns up to 4 UTF-8 characters.
		 **/
		static uint32_t										Utf32ToUtf8( char32_t _c32Utf32, uint32_t &_ui32Len );

		/**
		 * Converts a UTF-8 string to a UTF-16 string.  The resulting string may have allocated more characters than necessary but will be terminated with a NULL.
		 *
		 * \tparam _tInType The input character type.
		 * \tparam _tOutType The output string type.
		 * \param _pitString String to convert.
		 * \param _sLen The number of _tInType's to which _pitString points.
		 * \param _pbErrored If not nullptr, holds a returned boolean indicating success or failure of the conversion.
		 * \return Returns the converted UTF-16 string.
		 */
		template <typename _tInType = char8_t, typename _tOutType = std::u16string>
		static _tOutType									Utf8ToUtf16( const _tInType * _pitString, size_t _sLen, bool * _pbErrored = nullptr ) {
			static_assert( sizeof( _tInType ) == sizeof( char8_t ), "CUtilities::Utf8ToUtf16: sizeof( _tInType ) must equal sizeof( char8_t )." );
			_tOutType otTmp;
			if ( _pbErrored ) { (*_pbErrored) = false; }
			const char8_t * pc8In = reinterpret_cast<const char8_t *>(_pitString);
			for ( size_t I = 0; I < _sLen; ) {
				size_t sThisSize = 0;
				uint32_t ui32This = NextUtf8Char( &pc8In[I], _sLen - I, &sThisSize );
				if ( ui32This == NN9_UTF_INVALID ) {
					for ( size_t J = 0; J < sThisSize; ++J ) {
						otTmp.push_back( static_cast<_tOutType::value_type>(pc8In[I+J]) );
					}
					if ( _pbErrored ) { (*_pbErrored) = true; }
					I += sThisSize;
					continue;
				}
				I += sThisSize;
				uint32_t ui32Len;
				uint32_t ui32Converted = Utf32ToUtf16( ui32This, ui32Len );
				for ( uint32_t J = 0; J < ui32Len; ++J ) {
					otTmp.push_back( static_cast<_tOutType::value_type>(ui32Converted & 0xFFFFU) );
					ui32Converted >>= 16;
				}
			}
			return otTmp;
		}

		/**
		 * Converts a UTF-8 string to a UTF-16 string (NULL-terminated).  The resulting string may have allocated more characters than necessary but will be terminated with a NULL.
		 *
		 * \tparam _tInType The input character type.
		 * \tparam _tOutType The output string type.
		 * \param _pitString String to convert.
		 * \param _pbErrored If not nullptr, holds a returned boolean indicating success or failure of the conversion.
		 * \return Returns the converted UTF-16 string.
		 */
		template <typename _tInType = char8_t, typename _tOutType = std::u16string>
		static inline _tOutType								Utf8ToUtf16( const _tInType * _pitString, bool * _pbErrored = nullptr ) {
			size_t I = 0;
			while ( _pitString[I] ) { ++I; }
			return Utf8ToUtf16<_tInType, _tOutType>( _pitString, I, _pbErrored );
		}

		/**
		 * Converts a UTF-8 string to a UTF-16 string.  The resulting string may have allocated more characters than necessary but will be terminated with a NULL.
		 *
		 * \tparam _tInType The input string type.
		 * \tparam _tOutType The output string type.
		 * \param _pitString String to convert.
		 * \param _pbErrored If not nullptr, holds a returned boolean indicating success or failure of the conversion.
		 * \return Returns the converted UTF-16 string.
		 */
		template <typename _tInType = char8_t, typename _tOutType = std::u16string>
		static inline _tOutType								Utf8ToUtf16( const _tInType &_pitString, bool * _pbErrored = nullptr ) { return Utf8ToUtf16<typename _tInType::value_type, _tOutType>( _pitString.c_str(), _pitString.size(), _pbErrored ); }

		/**
		 * Converts a UTF-16 string to a UTF-8 string.  The resulting string may have allocated more characters than necessary but will be terminated with a NULL.
		 *
		 * \tparam _tInType The input character type.
		 * \tparam _tOutType The output string type.
		 * \param _pitString String to convert.
		 * \param _sLen The number of _tInType's to which _pitString points.
		 * \param _pbErrored If not nullptr, holds a returned boolean indicating success or failure of the conversion.
		 * \return Returns the converted UTF-8 string.
		 */
		template <typename _tInType = char16_t, typename _tOutType = std::u8string>
		static _tOutType									Utf16ToUtf8( const _tInType * _pitString, size_t _sLen, bool * _pbErrored = nullptr ) {
			static_assert( sizeof( _tInType ) == sizeof( char16_t ), "CUtilities::Utf16ToUtf8: sizeof( _tInType ) must equal sizeof( char16_t )." );

			_tOutType sRet;
			if ( _pbErrored ) { (*_pbErrored) = false; }
			const char16_t * pc16In = reinterpret_cast<const char16_t *>(_pitString);
			for ( size_t I = 0; I < _sLen; ) {
				size_t sThisSize = 0;
				uint32_t ui32Char = NextUtf16Char( &pc16In[I], _sLen - I, &sThisSize );
				if ( ui32Char == NN9_UTF_INVALID ) {
					ui32Char = pc16In[I];
					if ( _pbErrored ) { (*_pbErrored) = true; }
				}
				I += sThisSize;
				uint32_t ui32Len = 0;
				uint32_t ui32BackToUtf8 = Utf32ToUtf8( ui32Char, ui32Len );
				for ( uint32_t J = 0; J < ui32Len; ++J ) {
					sRet.push_back( static_cast<_tOutType::value_type>(ui32BackToUtf8) );
					ui32BackToUtf8 >>= 8;
				}
			}
			return sRet;
		}

		/**
		 * Converts a UTF-16 string to a UTF-8 string (NULL-terminated).  The resulting string may have allocated more characters than necessary but will be terminated with a NULL.
		 *
		 * \tparam _tInType The input character type.
		 * \tparam _tOutType The output string type.
		 * \param _pitString String to convert.
		 * \param _pbErrored If not nullptr, holds a returned boolean indicating success or failure of the conversion.
		 * \return Returns the converted UTF-8 string.
		 */
		template <typename _tInType = char16_t, typename _tOutType = std::u8string>
		static inline _tOutType								Utf16ToUtf8( const _tInType * _pitString, bool * _pbErrored = nullptr ) {
			size_t I = 0;
			while ( _pitString[I] ) { ++I; }
			return Utf16ToUtf8<_tInType, _tOutType>( _pitString, I, _pbErrored );
		}

		/**
		 * Converts a UTF-16 string to a UTF-8 string.  The resulting string may have allocated more characters than necessary but will be terminated with a NULL.
		 *
		 * \tparam _tInType The input string type.
		 * \tparam _tOutType The output string type.
		 * \param _pitString String to convert.
		 * \param _pbErrored If not nullptr, holds a returned boolean indicating success or failure of the conversion.
		 * \return Returns the converted UTF-8 string.
		 */
		template <typename _tInType = std::u16string, typename _tOutType = std::u8string>
		static inline _tOutType								Utf16ToUtf8( const _tInType &_pitString, bool * _pbErrored = nullptr ) { return Utf16ToUtf8<typename _tInType::value_type, _tOutType>( _pitString.c_str(), _pitString.size(), _pbErrored ); }


		// ===============================
		// String Operations
		// ===============================
		// == Functions.
		/**
		 * Creates a string with _cReplaceMe replaced with _cWithMe inside _s16String.
		 *
		 * \param _s16String The string in which replacements are to be made.
		 * \param _cReplaceMe The character to replace.
		 * \param _cWithMe The character with which to replace _cReplaceMe.
		 * \return Returns the new string with the given replacements made.
		 */
		template <typename _tType = std::u8string>
		static _tType										Replace( const _tType &_s16String, _tType::value_type _cReplaceMe, _tType::value_type _cWithMe ) {
			_tType s16Copy = _s16String;
			auto aFound = s16Copy.find( _cReplaceMe );
			while ( aFound != _tType::npos ) {
				s16Copy[aFound] = _cWithMe;
				aFound = s16Copy.find( _cReplaceMe, aFound + 1 );
			}
			return s16Copy;
		}

		/**
		 * Replaces a string inside a data vector.
		 * 
		 * \param _vData The buffer of data in which to replace a string.
		 * \param _sReplaceMe The string to replace.
		 * \param _sWithMe The string with which to replace _sReplaceMe inside _vData.
		 * \return Returns a reference to _vData.
		 **/
		template <typename _tType = std::vector<uint8_t>, typename _tReplaceType = std::string>
		static _tType &										Replace( _tType &_vData, const _tReplaceType &_sReplaceMe, const _tReplaceType &_sWithMe ) {
			if ( _sReplaceMe.size() > _vData.size() || _sReplaceMe.size() == 0 ) { return _vData; }

			for ( size_t I = 0; I < _vData.size() - _sReplaceMe.size(); ) {
				bool bMatch = true;
				for ( auto J = I; J < I + _sReplaceMe.size(); ++I ) {
					if ( _vData.data() + J != _sReplaceMe[J-I] ) {
						bMatch = false;
						break;
					}
				}
				if ( bMatch ) {
					_vData.erase( _vData.begin() + I, _vData.begin() + I + _sReplaceMe.size() );
					for ( size_t J = I; J < I + _sWithMe.size(); ++J ) {
						_vData.insert( _vData.begin() + J, _sWithMe.c_str()[J-I] );
					}
					I += _sWithMe.size();
					continue;
				}
				++I;
			}
			return _vData;
		}

		/**
		 * Converts any string to an std::u16string.  Call inside try/catch block.
		 * 
		 * \param _pctStr The string to convert.
		 * \param _sLen The length of the string or 0.
		 * \return Returns the converted string.
		 **/
		template <typename _tCharType>
		static inline std::u16string						XStringToU16String( const _tCharType * _pctStr, size_t _sLen = 0 ) {
			std::u16string u16Tmp;
			if ( _sLen ) {
				u16Tmp.reserve( _sLen );
			}
			for ( size_t I = 0; (I < _sLen) || (_sLen == 0 && !_pctStr[I]); ++I ) {
				u16Tmp.push_back( static_cast<char16_t>(_pctStr[I]) );
			}
			return u16Tmp;
		}

		/**
		 * Converts any string to an std::u16string.  Call inside try/catch block.
		 * 
		 * \param _sStr The string to convert.
		 * \return Returns the converted string.
		 **/
		template <typename _tCharType>
		static inline std::u16string						XStringToU16String( const _tCharType &_sStr ) {
			std::u16string u16Tmp;
			if ( _sStr.size() ) {
				u16Tmp.reserve( _sStr.size() );
			}
			for ( size_t I = 0; I < _sStr.size(); ++I ) {
				u16Tmp.push_back( static_cast<char16_t>(_sStr[I]) );
			}
			return u16Tmp;
		}

		/**
		 * Converts any string to an std::wstring.  Call inside try/catch block.
		 * 
		 * \param _pctStr The string to convert.
		 * \param _sLen The length of the string or 0.
		 * \return Returns the converted string.
		 **/
		template <typename _tCharType>
		static inline std::wstring							XStringToWString( const _tCharType * _pctStr, size_t _sLen = 0 ) {
			std::wstring wsTmp;
			if ( _sLen ) {
				wsTmp.reserve( _sLen );
			}
			for ( size_t I = 0; (I < _sLen) || (_sLen == 0 && !_pctStr[I]); ++I ) {
				wsTmp.push_back( static_cast<wchar_t>(_pctStr[I]) );
			}
			return wsTmp;
		}

		/**
		 * Converts any string to an std::wstring.  Call inside try/catch block.
		 * 
		 * \param _sStr The string to convert.
		 * \return Returns the converted string.
		 **/
		template <typename _tCharType>
		static inline std::wstring							XStringToWString( const _tCharType &_sStr ) {
			std::wstring wsTmp;
			if ( _sStr.size() ) {
				wsTmp.reserve( _sStr.size() );
			}
			for ( size_t I = 0; I < _sStr.size(); ++I ) {
				wsTmp.push_back( static_cast<wchar_t>(_sStr[I]) );
			}
			return wsTmp;
		}

		/**
		 * Reads a line from a buffer.
		 * 
		 * \param _vBuffer The buffer from which to read a line.
		 * \param _stPos The current position inside the buffer, updated on return.
		 * \return Returns the line read from the file.
		 **/
		static std::string									ReadLine( const std::vector<uint8_t> &_vBuffer, size_t &_stPos );

		/**
		 * Tokenizes a string by a given character.
		 * 
		 * \param _sString The string to tokenize.
		 * \param _vtDelimiter The character by which to deliminate the string into sections.
		 * \param _bAllowEmptyStrings If true, the return value could contain empty strings when the delimiter is found more than once in a row.
		 * \return Returns a vector containing all of the tokens.
		 **/
		static std::vector<std::string>						Tokenize( const std::string &_sString, std::string::value_type _vtDelimiter, bool _bAllowEmptyStrings );

		/**
		 * Parse a string into an array of strings given a UTF-32 delimiter.
		 * 
		 * \param _sInput The string to tokenize.
		 * \param _ui32Token The UTF character delimiter.
		 * \param _bIncludeEmptyTokens If true, multiple delimiters in a row or at the start and end of the string will result in empty results being returned in the array of results.
		 * \param pbErrored Optional boolean pointer to indicate any failures during the process.
		 * \return Returns an array of tokenized strings.
		 **/
		template <typename _tType = std::u8string>
		static std::vector<_tType>							TokenizeUtf( const _tType &_sInput, uint32_t _ui32Token, bool _bIncludeEmptyTokens = true, bool * pbErrored = nullptr ) {
			std::vector<_tType> vRet;
			try {
				_tType tCurLine;
				size_t sSize = 1;
				for ( size_t I = 0; I < _sInput.size(); I += sSize ) {
					uint32_t ui32Char;
					if constexpr ( sizeof( _tType::value_type ) == sizeof( char8_t ) ) {
						ui32Char = NextUtf8Char( reinterpret_cast<const char8_t *>(&_sInput[I]), _sInput.size() - I, &sSize );
					}
					else if constexpr ( sizeof( _tType::value_type ) == sizeof( char16_t ) ) {
						ui32Char = NextUtf16Char( reinterpret_cast<const char16_t *>(&_sInput[I]), _sInput.size() - I, &sSize );
					}
					else {
						sSize = 1;
						ui32Char = _sInput[I];
					}

					if ( ui32Char == _ui32Token ) {
						if ( tCurLine.size() || _bIncludeEmptyTokens ) {
							vRet.push_back( tCurLine );
						}
						tCurLine.clear();
					}
					else {
						tCurLine.append( &_sInput[I], sSize );
					}
				}
				if ( tCurLine.size() || _bIncludeEmptyTokens ) {
					vRet.push_back( tCurLine );
				}
				if ( pbErrored ) { (*pbErrored) = false; }
			}
			catch ( ... ) {
				if ( pbErrored ) { (*pbErrored) = true; }
			}
			return vRet;
		}

		/**
		 * Gets the last character in a string or std::u16string::traits_type::char_type( 0 ).
		 * 
		 * \tparam _tType The string (or array) type.
		 * \param _tStr The string whose last character is to be returned, if it has any characters.
		 * \return Returns the last character in the given string or std::u16string::traits_type::char_type( 0 ).
		 **/
		template <typename _tType = std::u16string>
		static _tType::traits_type::char_type				LastChar( const _tType &_tStr ) {
			return _tStr.size() ? _tStr[_tStr.size()-1] : _tType::traits_type::char_type( 0 );
		}

		/**
		 * Appends a char string to a char16_t string.
		 * 
		 * \param _sDst The string to which to append the string.
		 * \param _pcString The string to append to the string.
		 * \return Returns the new string.
		 **/
		template <typename _tType = std::u16string, typename _tCharType>
		static _tType										Append( const _tType &_sDst, const _tCharType * _pcString ) {
			try {
				_tType sTmp = _sDst;
				while ( (*_pcString) ) {
					sTmp.push_back( _tType::value_type( (*_pcString++) ) );
				}
				return sTmp;
			}
			catch ( ... ) { return _tType(); }
		}

		/**
		 * Appends a std::u16string string to a std::filesystem::path.  Call inside a try/catch.
		 * 
		 * \param _pStr The path to which to append the given string.
		 * \param _u16String The string to append to the given path.
		 * \return Returns the string with _u16String appended.
		 **/
		static inline std::filesystem::path					Append( const std::filesystem::path &_pStr, const std::u16string &_u16String ) {
			std::filesystem::path pTmp = _pStr;
			for ( size_t I = 0; I < _u16String.size(); ++I ) {
				pTmp += std::filesystem::path( std::u16string( 1, _u16String[I] ) );
			}
			return pTmp;
		}

		/**
		 * Performs ::towlower() on the given input.
		 * 
		 * \param _sStr The string to convert to lower-case.
		 * \return Returns the lower-cased input.
		 **/
		template <typename _tType = std::u8string>
		static inline _tType								ToLower( const _tType &_sStr ) {
			_tType sRet = _sStr;
			std::transform( sRet.begin(), sRet.end(), sRet.begin(), []( _tType::value_type _iC ) { return ::towlower( static_cast<wint_t>(_iC) ); } );
			return sRet;
		}

		/**
		 * Performs ::towupper() on the given input.
		 * 
		 * \param _sStr The string to convert to upper-case.
		 * \return Returns the upper-cased input.
		 **/
		template <typename _tType = std::u8string>
		static inline _tType								ToUpper( const _tType &_sStr ) {
			_tType sRet = _sStr;
			std::transform( sRet.begin(), sRet.end(), sRet.begin(), []( _tType::value_type _iC ) { return ::towupper( static_cast<wint_t>(_iC) ); } );
			return sRet;
		}

		/**
		 * Determines if the given character array has any UTF encodings.
		 * 
		 * \param _ptString Pointer to the array to scan for UTF characters.
		 * \param _sLen Length of the array to which _ptString points.
		 * \return Returns true if any of the characters in the given array have any bits set above the 7th.
		 **/
		template <typename _tType>
		static bool											HasUtf( const _tType * _ptString, size_t _sLen = 0 ) {
			if ( !_sLen ) {
				for ( size_t I = 0; _ptString[I]; ++I ) {
					if ( _ptString[I] & ~static_cast<_tType>(0x7F) ) { return true; }
				}
				return false;
			}
			for ( auto I = _sLen; I--; ) {
				if ( _ptString[I] & ~static_cast<_tType>(0x7F) ) { return true; }
			}
			return false;
		}

		/**
		 * Creates an ASCII path from the given file name, even if it is already an ASCII path.
		 *
		 * \param _sPath The input path, including the file name.
		 * \param _pAsciiPath The output folder.
		 * \param _pAsciiFileName The output file name.
		 * \return Returns true if allocation of all strings succeeded.  Failure indicates a memory failure.
		 **/
		static bool											CreateAsciiPath( const std::u16string &_sPath, std::filesystem::path &_pAsciiPath, std::filesystem::path &_pAsciiFileName );


		// ===============================
		// Sorting
		// ===============================
		/**
		 * Converts a vector to a set.  Call within a try/catch block.
		 * 
		 * \param _vVec The input vector to convert to a set.
		 * \return Returns the converted set.
		 **/
		template <typename _tnType>
		static std::set<_tnType>							ToSet( const std::vector<_tnType> &_vVec );

		/**
		 * Performs a radix sort on the given integer vector.  Call within a try/catch block.
		 * 
		 * \param _vVec The vector to sort.
		 * \return Returns _vVec.
		 **/
		template <typename _tnType>
		static std::vector<_tnType> &						RadixSort( std::vector<_tnType> &_vVec );


		// ===============================
		// Networking
		// ===============================
		/**
		 * Downloads a file and saves it to the given path.
		 * 
		 * \param _pcUrl The URL to the file to download.
		 * \param _pcPath The path to which to save the given file.
		 * \return Returns an error code indicating the result of the operation.
		 **/
		static NN9_ERRORS									DownloadFile( const std::u16string &_pcUrl, const std::u16string &_pcPath );

		/**
		 * Callback for writing the file during curl downloading.
		 * 
		 * \param _pvPtr Pointer to the data to write.
		 * \param _sSize The size of each data item.
		 * \param _sMem The total number of data items to write.
		 * \param _pvFile Pointer to a StdFile object used for the write process.
		 * \return Returns the number of bytes actually writtem.
		 **/
		static size_t NN9_CDECL								WriteCurlData( void * _pvPtr, size_t _sSize, size_t _sMem, void * _pvFile );

		/**
		 * Downloads the MNIST files to the given folder.
		 * 
		 * \param _pcFolder The path to the folder to where to download the MNIST files.
		 * \return Returns an error code indicating the result of the operation.
		 **/
		static NN9_ERRORS									DownloadMnist( const std::u16string &_pcFolder );


		// ===============================
		// Color Space Curves
		// ===============================
		/**
		 * Converts a single double value from sRGB space to linear space.  Performs a conversion according to the standard.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the converted value.
		 */
		static inline double NN9_FASTCALL					sRGBtoLinear( double _dVal ) {
			if ( _dVal < -0.04045 ) { return -std::pow( (-_dVal + 0.055) / 1.055, 2.4 ); }
			return _dVal <= 0.04045 ?
				_dVal / 12.92 :
				std::pow( (_dVal + 0.055) / 1.055, 2.4 );
		}

		/**
		 * Converts a single double value from linear space to sRGB space.  Performs a conversion according to the standard.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the converted value.
		 */
		static inline double NN9_FASTCALL					LinearTosRGB( double _dVal ) {
			if ( _dVal < -0.0031308 ) { return -1.055 * std::pow( -_dVal, 1.0 / 2.4 ) + 0.055; }
			return _dVal <= 0.0031308 ?
				_dVal * 12.92 :
				1.055 * std::pow( _dVal, 1.0 / 2.4 ) - 0.055;
		}

		/**
		 * Converts a single double value from sRGB space to linear space.  Performs a precise conversion without a gap.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the converted value.
		 */
		static inline double NN9_FASTCALL					sRGBtoLinear_Precise( double _dVal ) {
			/*constexpr double dAlpha = 0.05501071894758659264201838823282741941511631011962890625;
			constexpr double dBeta = 1.055010718947586578764230580418370664119720458984375;
			constexpr double dTheta = 12.9200000000000017053025658242404460906982421875;
			constexpr double dCut = 0.03929337067684757212049362351535819470882415771484375;*/

			constexpr double dAlpha = 0.055000000000000000277555756156289135105907917022705078125;
			constexpr double dBeta = 1.0549999999999999378275106209912337362766265869140625;
			constexpr double dTheta = 12.92321018078785499483274179510772228240966796875;
			constexpr double dCut = 0.039285714285714291860163172032116563059389591217041015625;
			if ( _dVal < -dCut ) { return -std::pow( (-_dVal + dAlpha) / dBeta, 2.4 ); }
			return _dVal <= dCut ?
				_dVal / dTheta :
				std::pow( (_dVal + dAlpha) / dBeta, 2.4 );
		}

		/**
		 * Converts a single double value from linear space to sRGB space.  Performs a precise conversion without a gap.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the converted value.
		 */
		static inline double NN9_FASTCALL					LinearTosRGB_Precise( double _dVal ) {
			/*constexpr double dAlpha = 0.05501071894758659264201838823282741941511631011962890625;
			constexpr double dBeta = 1.055010718947586578764230580418370664119720458984375;
			constexpr double dTheta = 12.9200000000000017053025658242404460906982421875;
			constexpr double dCut = 0.0030412825601275205074369711866211218875832855701446533203125;*/

			constexpr double dAlpha = 0.055000000000000000277555756156289135105907917022705078125;
			constexpr double dBeta = 1.0549999999999999378275106209912337362766265869140625;
			constexpr double dTheta = 12.92321018078785499483274179510772228240966796875;
			constexpr double dCut = 0.003039934639778431833823102437008856213651597499847412109375;
			if ( _dVal < -dCut ) { return -dBeta * std::pow( -_dVal, 1.0 / 2.4 ) + dAlpha; }
			return _dVal <= dCut ?
				_dVal * dTheta :
				dBeta * std::pow( _dVal, 1.0 / 2.4 ) - dAlpha;
		}

		/**
		 * Converts from SMPTE 170M-2004 to linear.  Performs a conversion according to the standard.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					SMPTE170MtoLinear( double _dVal ) {
			if ( _dVal < -0.081 ) { return -std::pow( (-_dVal + 0.099) / 1.099, 1.0 / 0.45 ); }
			return _dVal <= 0.081 ?
				_dVal / 4.5 :
				std::pow( (_dVal + 0.099) / 1.099, 1.0 / 0.45 );
		}

		/**
		 * Converts from linear to SMPTE 170M-2004.  Performs a conversion according to the standard.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the value converted to SMPTE 170M-2004 space.
		 */
		static inline double NN9_FASTCALL					LinearToSMPTE170M( double _dVal ) {
			if ( _dVal < -0.018 ) { return -1.099 * std::pow( -_dVal, 0.45 ) + 0.099; }
			return _dVal <= 0.018 ?
				_dVal * 4.5 :
				1.099 * std::pow( _dVal, 0.45 ) - 0.099;
		}

		/**
		 * Converts from SMPTE 170M-2004 to linear.  Performs a precise conversion without a gap.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					SMPTE170MtoLinear_Precise( double _dVal ) {
			if ( _dVal < -0.08124285829863515939752716121802222914993762969970703125 ) { return -std::pow( (-_dVal + 0.09929682680944297568093048766968422569334506988525390625) / 1.09929682680944296180314267985522747039794921875, 1.0 / 0.45 ); }
			return _dVal <= 0.08124285829863515939752716121802222914993762969970703125 ?
				_dVal / 4.5 :
				std::pow( (_dVal + 0.09929682680944297568093048766968422569334506988525390625) / 1.09929682680944296180314267985522747039794921875, 1.0 / 0.45 );
		}

		/**
		 * Converts from linear to SMPTE 170M-2004.  Performs a precise conversion without a gap.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the value converted to SMPTE 170M-2004 space.
		 */
		static inline double NN9_FASTCALL					LinearToSMPTE170M_Precise( double _dVal ) {
			if ( _dVal < -0.0180539685108078128139563744980478077195584774017333984375 ) { return -1.09929682680944296180314267985522747039794921875 * std::pow( -_dVal, 0.45 ) + 0.09929682680944297568093048766968422569334506988525390625; }
			return _dVal <= 0.0180539685108078128139563744980478077195584774017333984375 ?
				_dVal * 4.5 :
				1.09929682680944296180314267985522747039794921875 * std::pow( _dVal, 0.45 ) - 0.09929682680944297568093048766968422569334506988525390625;
		}

		/**
		 * Converts from SMPTE 240M to linear.  Performs a conversion according to the standard.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					SMPTE240MtoLinear( double _dVal ) {
			if ( _dVal <= -0.0913 ) { return -std::pow( (-_dVal + 0.1115) / 1.1115, 1.0 / 0.45 ); }
			return _dVal < 0.0913 ?
				_dVal / 4.0 :
				std::pow( (_dVal + 0.1115) / 1.1115, 1.0 / 0.45 );
		}

		/**
		 * Converts from linear to SMPTE 240M.  Performs a conversion according to the standard.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the value converted to SMPTE 240M space.
		 */
		static inline double NN9_FASTCALL					LinearToSMPTE240M( double _dVal ) {
			if ( _dVal <= -0.0228 ) { return -1.1115 * std::pow( -_dVal, 0.45 ) + 0.1115; }
			return _dVal < 0.0228 ?
				_dVal * 4.0 :
				1.1115 * std::pow( _dVal, 0.45 ) - 0.1115;
		}

		/**
		 * Converts from SMPTE 240M to linear.  Performs a precise conversion without a gap.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					SMPTE240MtoLinear_Precise( double _dVal ) {
			if ( _dVal < -0.0912863421177801115380390228892792947590351104736328125 ) { return -std::pow( (-_dVal + 0.1115721959217312597711924126997473649680614471435546875) / 1.1115721959217312875267680283286608755588531494140625, 1.0 / 0.45 ); }
			return _dVal <= 0.0912863421177801115380390228892792947590351104736328125 ?
				_dVal / 4.0 :
				std::pow( (_dVal + 0.1115721959217312597711924126997473649680614471435546875) / 1.1115721959217312875267680283286608755588531494140625, 1.0 / 0.45 );
		}

		/**
		 * Converts from linear to SMPTE 240M.  Performs a precise conversion without a gap.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the value converted to SMPTE 240M space.
		 */
		static inline double NN9_FASTCALL					LinearToSMPTE240M_Precise( double _dVal ) {
			if ( _dVal < -0.022821585529445027884509755722319823689758777618408203125 ) { return -1.1115721959217312875267680283286608755588531494140625 * std::pow( -_dVal, 0.45 ) + 0.1115721959217312597711924126997473649680614471435546875; }
			return _dVal <= 0.022821585529445027884509755722319823689758777618408203125 ?
				_dVal * 4.0 :
				1.1115721959217312875267680283286608755588531494140625 * std::pow( _dVal, 0.45 ) - 0.1115721959217312597711924126997473649680614471435546875;
		}

		/**
		 * Converts from linear to linear.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					PassThrough( double _dVal ) {
			return _dVal;
		}

		/**
		 * Converts from 2.2 to linear.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					Pow2_2toLinear( double _dVal ) {
			if ( _dVal < 0 ) { return -std::pow( -_dVal, 2.2 ); }
			return std::pow( _dVal, 2.2 );
		}

		/**
		 * Converts from linear to 2.2.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the value converted to 2.2 space.
		 */
		static inline double NN9_FASTCALL					LinearToPow2_2( double _dVal ) {
			if ( _dVal < 0 ) { return -std::pow( -_dVal, 1.0 / 2.2 ); }
			return std::pow( _dVal, 1.0 / 2.2 );
		}

		/**
		 * Converts from 2.8 to linear.
		 * 
		 * \param _dVal The value to convert.
		 * \return Returns the color value converted to linear space.
		 **/
		static inline double NN9_FASTCALL					Pow2_8toLinear( double _dVal ) {
			if ( _dVal < 0 ) { return -std::pow( -_dVal, 2.8 ); }
			return std::pow( _dVal, 2.8 );
		}

		/**
		 * Converts from linear to 2.8.
		 *
		 * \param _dVal The value to convert.
		 * \return Returns the value converted to 2.8 space.
		 */
		static inline double NN9_FASTCALL					LinearToPow2_8( double _dVal ) {
			if ( _dVal < 0 ) { return -std::pow( -_dVal, 1.0 / 2.8 ); }
			return std::pow( _dVal, 1.0 / 2.8 );
		}

		/**
		 * Converts XYZ values to chromaticities.
		 * 
		 * \param _dX The input X.
		 * \param _dY The input Y.
		 * \param _dZ The input Z.
		 * \param _dChromaX The output chromaticity X.
		 * \param _dChromaY The output chromaticity Y.
		 **/
		static inline void									XYZtoChromaticity( double _dX, double _dY, double _dZ, double &_dChromaX, double &_dChromaY ) {
			double dX = _dX / _dY;
			constexpr double dY = 1.0;
			double dZ = _dZ / _dY;

			_dChromaX = dX / (dX + dY + dZ);
			_dChromaY = dY / (dX + dY + dZ);
		}

		/**
		 * Converts chromaticities to XYZ values.
		 * 
		 * \param _dChromaX The input chromaticity X.
		 * \param _dChromaY The input chromaticity Y.
		 * \param _dY0 The input XYZ Y value.
		 * \param _dX0 The output XYZ Z value.
		 * \param _dZ0 The output XYZ Z value.
		 **/
		static void											ChromaticityToXYZ( double _dChromaX, double _dChromaY, double _dY0, double &_dX0, double &_dZ0 ) {
			_dX0 = _dChromaX * (_dY0 / _dChromaY);
			_dZ0 = (1.0 - _dChromaX - _dChromaY) * (_dY0 / _dChromaY);
		}


		// ===============================
		// Sampling
		// ===============================
		/**
		 * 6-point, 5th-order Hermite X-form sampling.
		 *
		 * \param _pfsSamples The array of 6 input samples, indices -2, -1, 0, 1, 2, and 3.
		 * \param _dFrac The interpolation amount.
		 * \return Returns the interpolated point.
		 */
		static inline double								Sample_6Point_5thOrder_Hermite_X( const double * _pfsSamples, double _dFrac ) {
			// 6-point, 5th-order Hermite (X-form).
			double dEightThym2 = 1.0 / 8.0 * _pfsSamples[-2+2];
			double dElevenTwentyFourThy2 = 11.0 / 24.0 * _pfsSamples[2+2];
			double dTwelvThy3 = 1.0 / 12.0 * _pfsSamples[3+2];
			double dC0 = _pfsSamples[0+2];
			double dC1 = 1.0 / 12.0 * (_pfsSamples[-2+2] - _pfsSamples[2+2]) + 2.0 / 3.0 * (_pfsSamples[1+2] - _pfsSamples[-1+2]);
			double dC2 = 13.0 / 12.0 * _pfsSamples[-1+2] - 25.0 / 12.0 * _pfsSamples[0+2] + 3.0 / 2.0 * _pfsSamples[1+2] -
				dElevenTwentyFourThy2 + dTwelvThy3 - dEightThym2;
			double dC3 = 5.0 / 12.0 * _pfsSamples[0+2] - 7.0 / 12.0 * _pfsSamples[1+2] + 7.0 / 24.0 * _pfsSamples[2+2] -
				1.0 / 24.0 * (_pfsSamples[-2+2] + _pfsSamples[-1+2] + _pfsSamples[3+2]);
			double dC4 = dEightThym2 - 7.0 / 12.0 * _pfsSamples[-1+2] + 13.0 / 12.0 * _pfsSamples[0+2] - _pfsSamples[1+2] +
				dElevenTwentyFourThy2 - dTwelvThy3;
			double dC5 = 1.0 / 24.0 * (_pfsSamples[3+2] - _pfsSamples[-2+2]) + 5.0 / 24.0 * (_pfsSamples[-1+2] - _pfsSamples[2+2]) +
				5.0 / 12.0 * (_pfsSamples[1+2] - _pfsSamples[0+2]);
			return ((((dC5 * _dFrac + dC4) * _dFrac + dC3) * _dFrac + dC2) * _dFrac + dC1) * _dFrac + dC0;
		}

		/**
		 * 4-point, 3rd-order Hermite X-form sampling.
		 *
		 * \param _pfsSamples The array of 6 input samples, indices -1, 0, 1, and 2.
		 * \param _dFrac The interpolation amount.
		 * \return Returns the interpolated point.
		 */
		static inline double								Sample_4Point_3rdhOrder_Hermite_X( const double * _pfsSamples, double _dFrac ) {
			// 4-point, 5th-order Hermite (X-form).
			double dC0 = _pfsSamples[0+1];
			double dC1 = 1.0 / 2.0 * (_pfsSamples[1+1] - _pfsSamples[-1+1]);
			double dC2 = _pfsSamples[-1+1] - 5.0 / 2.0 * _pfsSamples[0+1] + 2.0 * _pfsSamples[1+1] - 1.0 / 2.0 * _pfsSamples[2+1];
			double dC3 = 1.0 / 2.0 * (_pfsSamples[2+1] - _pfsSamples[-1+1]) + 3.0 / 2.0 * (_pfsSamples[0+1] - _pfsSamples[1+1]);
			return ((dC3 * _dFrac + dC2) * _dFrac + dC1) * _dFrac + dC0;
		}

		/**
		 * Standard sinc() function.
		 * 
		 * \param _dX The operand.
		 * \return Returns sin(x*pi) / x*pi.
		 **/
		static inline double								Sinc( double _dX ) {
			_dX *= std::numbers::pi;
			if ( _dX < 0.01 && _dX > -0.01 ) {
				return 1.0 + _dX * _dX * (-1.0 / 6.0 + _dX * _dX * 1.0 / 120.0);
			}

			return std::sin( _dX ) / _dX;
		}


		// ===============================
		// Bits
		// ===============================
		/**
		 * Is the given value a power of 2?
		 * 
		 * \param _ui32Val The value.
		 * \return Returns true if the given value is a power of 2.
		 **/
		static inline bool									IsPo2( uint32_t _ui32Val ) {
			if ( !_ui32Val ) { return false; }
			return (_ui32Val & (_ui32Val - 1UL)) == 0;
		}

		/**
		 * Gets the lowest power-of-2 value not below the given input value.
		 *
		 * \param _ui32Value Value for which to derive the lowest power-of-2 value not under this value.
		 * \return Returns the lowest power-of-2 value not below the given input value.
		 */
		static uint32_t										GetLowestPo2( uint32_t _ui32Value );

		/**
		 * Takes a bit mask and returns a shift and divisor.
		 * 
		 * \param _ui64Mask The bit mask.
		 * \param _dMaxVal Holds teh returned maximum value for the given mask.
		 * \return Returns the mask shift.
		 **/
		static size_t										BitMaskToShift( uint64_t _ui64Mask, double &_dMaxVal ) {
			if ( !_ui64Mask ) { _dMaxVal = 0.0; return 0; }
			size_t sShift = 0;
			while ( !(_ui64Mask & 1) ) {
				_ui64Mask >>= 1;
				++sShift;
			}
			_dMaxVal = static_cast<double>(_ui64Mask);
			return sShift;
		}


		// ===============================
		// Instruction Sets
		// ===============================
		/**
		 * Is AVX supported?
		 *
		 * \return Returns true if AVX is supported.
		 **/
		static inline bool									IsAvxSupported() {
			return FeatureSet::AVX();
		}

		/**
		 * Is AVX 2 supported?
		 *
		 * \return Returns true if AVX is supported.
		 **/
		static inline bool									IsAvx2Supported() {
			return FeatureSet::AVX2();
		}

		/**
		 * Is AVX-512F supported?
		 *
		 * \return Returns true if AVX-512F is supported.
		 **/
		static inline bool									IsAvx512FSupported() {
			return FeatureSet::AVX512F();
		}

		/**
		 * Is AVX-512BW supported?
		 *
		 * \return Returns true if AVX-512BW is supported.
		 **/
		static inline bool									IsAvx512BWSupported() {
			return FeatureSet::AVX512BW();
		}

		/**
		 * Is AVX-512BF16 (brain float) supported?
		 *
		 * \return Returns true if AVX-512BF16 is supported.
		 **/
		static inline bool									IsAvx512BF16Supported() {
			return FeatureSet::AVX512BF16();
		}

		/**
		 * Is AVX-VNNI supported?
		 *
		 * \return Returns true if AVX-VNNI is supported.
		 **/
		static inline bool									IsAvxVNNISupported() {
			return FeatureSet::AVX_VNNI();
		}

		/**
		 * Is NEON supported?
		 *
		 * \return Returns true if NEON is supported.
		 **/
		static inline bool									IsNeonSupported() {
#ifndef NN9_CPUID
			if ( m_iNeon == 3 ) { m_iNeon = FeatureSet::NEON(); }
			return m_iNeon != 0;
#else
			return false;
#endif	// #ifndef NN9_CPUID
		}

		/**
		 * Is non-AVX BF16 supported?
		 *
		 * \return Returns true if non-AVX BF16 is supported.
		 **/
		static inline bool									IsBf16Supported() {
#ifndef NN9_CPUID
			if ( m_iBf16 == 3 ) { m_iBf16 = FeatureSet::BF16(); }
			return m_iBf16 != 0;
#else
			return false;
#endif	// #ifndef NN9_CPUID
		}

		/**
		 * Is non-AVX FP16 supported?
		 *
		 * \return Returns true if non-AVX FP16 is supported.
		 **/
		static inline bool									IsFp16Supported() {
#ifndef NN9_CPUID
			if ( m_iFp16 == 3 ) { m_iFp16 = FeatureSet::FP16(); }
			return m_iFp16 != 0;
#else
			return false;
#endif	// #ifndef NN9_CPUID
		}

		/**
		 * Is SVE supported?
		 *
		 * \return Returns true if SVE is supported.
		 **/
		static inline bool									IsSveSupported() {
#ifndef NN9_CPUID
			if ( m_iSve == 3 ) { m_iSve = FeatureSet::SVE(); }
			return m_iSve != 0;
#else
			return false;
#endif	// #ifndef NN9_CPUID
		}

#ifdef __AVX512F__
		/**
		 * Horizontally adds all the floats in a given AVX-512 register.
		 * 
		 * \param _mReg The register containing all of the values to sum.
		 * \return Returns the sum of all the floats in the given register.
		 **/
		static inline double								HorizontalSum( __m512d _mReg ) {
			return _mm512_reduce_add_pd( _mReg );
#if 0
			// Step 1: Reduce 512 bits to 256 bits by summing the high and low 256 bits.
			__m256d mLow256 = _mm512_castpd512_pd256( _mReg );					// Low 256 bits.
			__m256d mHigh256 = _mm512_extractf64x4_pd( _mReg, 1 );				// High 256 bits.
			__m256d mSum256 = _mm256_add_pd( mLow256, mHigh256 );				// Add high and low 256-bit parts.

			// Step 2: Follow the same 256-bit reduction routine.
			__m256d mShuf = _mm256_permute2f128_pd( mSum256, mSum256, 0x1 );	// Swap low and high 128-bit halves.
			__m256d mSums = _mm256_add_pd( mSum256, mShuf );					// Add low and high halves.

			mShuf = _mm256_shuffle_pd( mSums, mSums, 0x5 );						// Swap the pairs of doubles.
			mSums = _mm256_add_pd( mSums, mShuf );								// Add the pairs.

			// Step 3: Extract the scalar value (final sum).
			return _mm256_cvtsd_f64( mSums );									// Extract the lower double as the sum.
#endif	// #if 0
		}

		/**
		 * Horizontally adds all the floats in a given AVX-512 register.
		 * 
		 * \param _mReg The register containing all of the values to sum.
		 * \return Returns the sum of all the floats in the given register.
		 **/
		static inline float									HorizontalSum( __m512 _mReg ) {
			return _mm512_reduce_add_ps( _mReg );
#if 0
			// Step 1: Reduce 512 bits to 256 bits by permuting and adding high and low 256 bits.
			__m256 mLow256 = _mm512_castps512_ps256( _mReg );					// Low 256 bits.
			__m256 mHigh256 = _mm512_extractf32x8_ps( _mReg, 1 );				// High 256 bits.
			__m256 mSum256 = _mm256_add_ps( mLow256, mHigh256 );				// Add high and low 256-bit parts.

			// Step 2: Perform horizontal addition on 256 bits.
			mSum256 = _mm256_hadd_ps( mSum256, mSum256 );						// First horizontal add.
			mSum256 = _mm256_hadd_ps( mSum256, mSum256 );						// Second horizontal add.

			// Step 3: Extract the lower float which now contains the sum.
			return _mm256_cvtss_f32( mSum256 );
#endif	// #if 0
		}
#endif	// #ifdef __AVX512F__

#ifdef __AVX__
		/**
		 * Horizontally adds all the floats in a given AVX register.
		 * 
		 * \param _mReg The register containing all of the values to sum.
		 * \return Returns the sum of all the floats in the given register.
		 **/
		static inline double								HorizontalSum( __m256d &_mReg ) {
			__m256d mT1 = _mm256_hadd_pd( _mReg, _mReg );
			__m128d mT2 = _mm256_extractf128_pd( mT1, 1 );
			__m128d mT3 = _mm256_castpd256_pd128( mT1 );
			return _mm_cvtsd_f64( _mm_add_pd( mT2, mT3 ) );
#if 0
			__m256d mShuf = _mm256_permute2f128_pd( _mReg, _mReg, 0x1 );		// Swap the low and high halves.
			__m256d mSums = _mm256_add_pd( _mReg, mShuf );						// Add the low and high halves.

			mShuf = _mm256_shuffle_pd( mSums, mSums, 0x5 );						// Swap the pairs of doubles.
			mSums = _mm256_add_pd( mSums, mShuf );								// Add the pairs.

			return _mm256_cvtsd_f64( mSums );									// Extract the sum.
#endif	// #if 0
		}

		/**
		 * Horizontally adds all the floats in a given AVX register.
		 * 
		 * \param _mReg The register containing all of the values to sum.
		 * \return Returns the sum of all the floats in the given register.
		 **/
		static inline float									HorizontalSum( const __m256 &_mReg ) {
			NN9_ALIGN( 32 )
			float fSumArray[8];
			__m256 mTmp = _mm256_hadd_ps( _mReg, _mReg );
			mTmp = _mm256_hadd_ps( mTmp, mTmp );
			_mm256_store_ps( fSumArray, mTmp );
			return fSumArray[0] + fSumArray[4];
#if 0
			__m256 mTmp = _mm256_permute2f128_ps(_mReg, _mReg, 1);				// Shuffle high 128 to low.
			mTmp = _mm256_add_ps( _mReg, mTmp );								// Add high and low parts.

			mTmp = _mm256_hadd_ps( mTmp, mTmp );								// First horizontal add.
			mTmp = _mm256_hadd_ps( mTmp, mTmp );								// Second horizontal add.

			// Extract the lower float which now contains the sum.
			return _mm256_cvtss_f32( mTmp );
#endif	// #if 0
		}
#endif	// #ifdef __AVX__

#ifdef __SSE4_1__
		/**
		 * Horizontally adds all the floats in a given SSE register.
		 * 
		 * \param _mReg The register containing all of the values to sum.
		 * \return Returns the sum of all the floats in the given register.
		 **/
		static inline double								HorizontalSum( const __m128d &_mReg ) {
			__m128d mAddH1 = _mm_shuffle_pd( _mReg, _mReg, 0x1 );
			__m128d mAddH2 = _mm_add_pd( _mReg, mAddH1 );
			return _mm_cvtsd_f64( mAddH2 );
		}

		/**
		 * Horizontally adds all the floats in a given SSE register.
		 * 
		 * \param _mReg The register containing all of the values to sum.
		 * \return Returns the sum of all the floats in the given register.
		 **/
		static inline float									HorizontalSum( const __m128 &_mReg ) {
			__m128 mAddH1 = _mm_hadd_ps( _mReg, _mReg );
			__m128 mAddH2 = _mm_hadd_ps( mAddH1, mAddH1 );
			return _mm_cvtss_f32( mAddH2 );
		}
#endif	// #ifdef __SSE4_1__


	protected :
		// == Members.
#ifndef NN9_CPUID
		static int											m_iNeon;					/**< Tracks support for NEON. */
		static int											m_iBf16;					/**< Tracks support for BF16. */
		static int											m_iFp16;					/**< Tracks support for FP16. */
		static int											m_iSve;						/**< Tracks support for SVE. */
#endif	// #ifndef NN9_CPUID
	};


#if defined( _WIN32 )
	/** A wrapper for Windows HANDLE. **/
	struct NN9_HANDLE {
		NN9_HANDLE() : hHandle( NULL ) {}
		NN9_HANDLE( HANDLE _hHandle ) : hHandle( _hHandle ) {}
		~NN9_HANDLE() {
			Reset();
		}

		NN9_HANDLE &										operator = ( HANDLE &_hHandle ) {
			Reset();
			hHandle = _hHandle;
			_hHandle = NULL;
			return (*this);
		}


		// == Functions.
		VOID												Reset() {
			if ( Valid() ) {
				::CloseHandle( hHandle );
				hHandle = NULL;
			}
		}

		inline BOOL											Valid() const { return hHandle && hHandle != INVALID_HANDLE_VALUE; }

		static inline  BOOL									Valid( HANDLE _hHandle ) { return _hHandle && _hHandle != INVALID_HANDLE_VALUE; }


		// == Members.
		HANDLE												hHandle;					/**< The wrapped object. */
	};

	/** A wrapper for Windows HMODULE. **/
	struct NN9_HMODULE {
		NN9_HMODULE() : hHandle( NULL ) {}
		NN9_HMODULE( LPCSTR _sPath ) :
			hHandle( ::LoadLibraryW( nn9::Utilities::Utf8ToUtf16<CHAR, std::wstring>( _sPath ).c_str() ) ) {
		}
		NN9_HMODULE( LPCWSTR _wsPath ) :
			hHandle( ::LoadLibraryW( _wsPath ) ) {
		}
		NN9_HMODULE( const char16_t * _pu16Path ) :
			hHandle( ::LoadLibraryW( reinterpret_cast<LPCWSTR>(_pu16Path) ) ) {
		}
		~NN9_HMODULE() {
			Reset();
		}


		// == Functions.
		BOOL												LoadLib( LPCSTR _sPath ) {
			Reset();
			hHandle = ::LoadLibraryW( nn9::Utilities::Utf8ToUtf16<CHAR, std::wstring>( _sPath ).c_str() );
			return hHandle != NULL;
		}

		BOOL												LoadLib( LPCWSTR _wsPath ) {
			Reset();
			hHandle = ::LoadLibraryW( _wsPath );
			return hHandle != NULL;
		}

		BOOL												LoadLib( const char16_t * _pu16Path ) {
			Reset();
			hHandle = ::LoadLibraryW( reinterpret_cast<LPCWSTR>(_pu16Path) );
			return hHandle != NULL;
		}

		inline VOID											Reset() {
			if ( Valid() ) {
				::FreeLibrary( hHandle );
				hHandle = NULL;
			}
		}

		inline BOOL											Valid() const { return hHandle != NULL; }


		// == Members.
		HMODULE												hHandle;					/**< The wrapped object. */
	};
#endif	// #if defined( _WIN32 )

	/** A curl object. */
	struct NN9_CURL {
		NN9_CURL( ::CURL * _pSrc ) :
			pcCurl( _pSrc ) {
		}
		~NN9_CURL() {
			Reset();
		}
		// == Functions.
		void												Reset() {
			if ( pcCurl ) {
				::curl_easy_cleanup( pcCurl );
				pcCurl = nullptr;
			}
		}

		inline ::CURL *										Create() {
			Reset();
			pcCurl = ::curl_easy_init();
			return pcCurl;
		}

		inline bool											Valid() const { return pcCurl != nullptr; }

		::CURL *											pcCurl = nullptr;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Functions.
	/**
	 * Converts a vector to a set.  Call within a try/catch block.
	 * 
	 * \param _vVec The input vector to convert to a set.
	 * \return Returns the converted set.
	 **/
	template <typename _tnType>
	std::set<_tnType> Utilities::ToSet( const std::vector<_tnType> &_vVec ) {
		std::set<_tnType> sRet;
		for ( auto I = _vVec.size(); I--; ) {
			sRet.insert( _vVec[I] );
		}
		return sRet;
	}

NN9_OPTIMIZE_ON
	/**
	 * Performs a radix sort on the given integer vector.  Call within a try/catch block.
	 * 
	 * \param _vVec The vector to sort.
	 * \return Returns _vVec.
	 **/
	template <typename _tnType>
	std::vector<_tnType> & Utilities::RadixSort( std::vector<_tnType> &_vVec ) {
		const size_t sN = _vVec.size();
		if ( sN <= 1 ) { return _vVec; }

		// Number of sBits processed per sPass (using 8 sBits per sPass).
		constexpr size_t sBits = 8;
		constexpr size_t sPasses = (sizeof( _tnType ) * 8 ) / sBits;			// Total number of passes needed.
		constexpr size_t sRadix = size_t( 1 ) << sBits;							// Radix base (256).

		std::vector<_tnType> vBuffer( sN );
		std::vector<_tnType> * pvFrom = &_vVec;
		std::vector<_tnType> * pvTo = &vBuffer;

		for ( size_t sPass = 0; sPass < sPasses; ++sPass ) {
			// Initialize aCount array.
			std::array<size_t, sRadix> aCount = { 0 };

			// Counting occurrences of each digit.
			for ( size_t I = 0; I < sN; ++I ) {
				_tnType tnValue = (*pvFrom)[I];
				size_t sDigit = (tnValue >> (sBits * sPass)) & (sRadix - 1);
				++aCount[sDigit];
			}

			// Compute prefix sums (positions).
			size_t sTotal = 0;
			for ( size_t I = 0; I < sRadix; ++I ) {
				size_t sC = aCount[I];
				aCount[I] = sTotal;
				sTotal += sC;
			}

			// Reorder elements based on the current digit.
			for ( size_t I = 0; I < sN; ++I ) {
				_tnType tnValue = (*pvFrom)[I];
				size_t sDigit = (tnValue >> (sBits * sPass)) & (sRadix - 1);
				(*pvTo)[aCount[sDigit]] = tnValue;
				++aCount[sDigit];
			}

			// Swap the pvFrom and pvTo vectors for the next sPass.
			std::swap( pvFrom, pvTo );
		}

		// If the sorted _vVec is not in the original vector, copy it back.
		if ( pvFrom != &_vVec ) {
			_vVec = std::move( *pvFrom );
		}
		return _vVec;
	}
NN9_OPTIMIZE_OFF

}	// namespace nn9
