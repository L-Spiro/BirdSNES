/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Error codes and functions for handling errors.
 */

#pragma once


#include <cstdint>

namespace lsn {

	// == Types.
	/** Error codes. */
	enum LSN_STRINGS : uint32_t {
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						ENUM,
#include "LSNStringsEnum.inl"
#undef LSN_STR
	};


	// == Functions.
	/**
	 * Gets a string by ID.
	 * 
	 * \param _ui32Id The ID of the string to return.
	 * \return Returns the requested string as an L"" string.
	 **/
	constexpr const wchar_t *										StrL( uint32_t _ui32Id ) {
		switch ( _ui32Id ) {
#if defined( LSN_JAPANESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return L##JPN; }
#elif defined( LSN_FRENCH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return L##FR; }
#elif defined( LSN_SPANISH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return L##SP; }
#elif defined( LSN_CHINESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return L##CH; }
#else
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return L##TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNStringsEnum.inl"
#undef LSN_STR
			default : { return L""; }
		}
	}

	/**
	 * Gets a string by ID.
	 * 
	 * \param _ui32Id The ID of the string to return.
	 * \return Returns the requested string as a u"" string.
	 **/
	constexpr const char16_t *										StrU( uint32_t _ui32Id ) {
		switch ( _ui32Id ) {
#if defined( LSN_JAPANESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u##JPN; }
#elif defined( LSN_FRENCH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u##FR; }
#elif defined( LSN_SPANISH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u##SP; }
#elif defined( LSN_CHINESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u##CH; }
#else
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u##TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNStringsEnum.inl"
#undef LSN_STR
			default : { return u""; }
		}
	}

	/**
	 * Gets a string by ID.
	 * 
	 * \param _ui32Id The ID of the string to return.
	 * \return Returns the requested string as a "" string.
	 **/
	constexpr const char *											Str( uint32_t _ui32Id ) {
		switch ( _ui32Id ) {
#if defined( LSN_JAPANESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return JPN; }
#elif defined( LSN_FRENCH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return FR; }
#elif defined( LSN_SPANISH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return SP; }
#elif defined( LSN_CHINESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return CH; }
#else
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNStringsEnum.inl"
#undef LSN_STR
			default : { return ""; }
		}
	}

	/**
	 * Gets a string by ID.
	 * 
	 * \param _ui32Id The ID of the string to return.
	 * \return Returns the requested string as a u8"" string.
	 **/
	constexpr const char8_t *										StrU8( uint32_t _ui32Id ) {
		switch ( _ui32Id ) {
#if defined( LSN_JAPANESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u8##JPN; }
#elif defined( LSN_FRENCH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u8##FR; }
#elif defined( LSN_SPANISH )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u8##SP; }
#elif defined( LSN_CHINESE )
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u8##CH; }
#else
#define LSN_STR( ENUM, TXT, JPN, FR, SP, CH )						case ENUM : { return u8##TXT; }
#endif	// #if defined( LSN_JAPANESE )
#include "LSNStringsEnum.inl"
#undef LSN_STR
			default : { return u8""; }
		}
	}

}	// namespace lsn
