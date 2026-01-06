/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Cross-platform bit hacks & operations.
 */

#pragma once

#include <cstdint>
#if defined( _MSC_VER )
#include <intrin.h>
#endif  // #if defined( _MSC_VER )


namespace lsn {

	// == Functions.
	/**
	 * Sets a bit in a flag to 1 or 0.
	 *
	 * \tparam _uBit Bit mask.
	 * \param _ui8Val The value to modify in-place.
	 * \param _bOn If true, the bit is set, otherwise it is unset.
	 */
	template <unsigned _uBit>
	inline uint8_t							SetBit( uint8_t &_ui8Val, const bool _bOn ) {
		if ( _bOn ) { _ui8Val |= _uBit; }
		else { _ui8Val &= ~_uBit; }
		return _ui8Val;
	}

	/**
	 * Sets a bit in a flag to 1 or 0.
	 *
	 * \tparam _uBit Bit mask.
	 * \tparam _bVal The bit value to write (0 or 1).
	 * \param _ui8Val The value to modify in-place.
	 */
	template <unsigned _uBit, bool _bVal>
	inline uint8_t							SetBit( uint8_t &_ui8Val ) {
		if constexpr ( _bVal != 0 ) { _ui8Val |= _uBit; }
		else { _ui8Val &= ~_uBit; }
		return _ui8Val;
	}

	/**
	 * Checks for a bit being set.
	 *
	 * \param _ui8Val The value to check.
	 * \param _ui8Bit The bit to check.
	 * \return Returns true if the bit is set, otherwise false.
	 */
	inline bool								CheckBit( const uint8_t _ui8Val, const uint8_t _ui8Bit ) {
		return (_ui8Val & _ui8Bit) ? true : false;
	}

}	// namespace lsn


// ===============================
// Byte Swapping
// ===============================

#if defined( _MSC_VER )
#define bswap_16( X )							_byteswap_ushort( X )
#define bswap_32( X )							_byteswap_ulong( X )
#define bswap_64( X )							_byteswap_uint64( X )
#elif defined( __APPLE__ )
// Mac OS X/Darwin features.
#include <libkern/OSByteOrder.h>
#define bswap_16( X )							OSSwapInt16( X )
#define bswap_32( X )							OSSwapInt32( X )
#define bswap_64( X )							OSSwapInt64( X )
#elif defined( __sun ) || defined( sun )

#include <sys/byteorder.h>
#define bswap_16( X )							BSWAP_16( X )
#define bswap_32( X )							BSWAP_32( X )
#define bswap_64( X )							BSWAP_64( X )

#elif defined( __FreeBSD__ )

#include <sys/endian.h>
#define bswap_16( X )							bswap16( X )
#define bswap_32( X )							bswap32( X )
#define bswap_64( X )							bswap64( X )

#elif defined( __OpenBSD__ )

#include <sys/types.h>
#define bswap_16( X )							swap16( X )
#define bswap_32( X )							swap32( X )
#define bswap_64( X )							swap64( X )

#elif defined( __NetBSD__ )

#include <sys/types.h>
#include <machine/bswap.h>
#if defined( __BSWAP_RENAME ) && !defined( __bswap_32 )
#define bswap_16( X )							bswap16( X )
#define bswap_32( X )							bswap32( X )
#define bswap_64( X )							bswap64( X )
#endif

#else
inline uint16_t                                 bswap_16( uint16_t _ui16Val ) { return (_ui16Val >> 8) | (_ui16Val << 8); }
inline unsigned long                            bswap_32( unsigned long _ui32Val ) { return uint32_t( (uint32_t( _ui32Val ) >> 24) |
	((_ui32Val >> 8) & 0x0000FF00) |
	((_ui32Val << 8) & 0x00FF0000) |
	(_ui32Val << 24) ); }
inline uint64_t                                 bswap_64( uint64_t _ui64Val ) { return (_ui64Val >> 56) |
	((_ui64Val >> 40) & 0x000000000000FF00ULL) |
	((_ui64Val >> 24) & 0x0000000000FF0000ULL) |
	((_ui64Val >> 8) & 0x00000000FF000000ULL) |
	((_ui64Val << 8) & 0x000000FF00000000ULL) |
	((_ui64Val << 24) & 0x0000FF0000000000ULL) |
	((_ui64Val << 40) & 0x00FF000000000000ULL) |
	(_ui64Val << 56); }
#endif	// #if defined( _MSC_VER )
