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


namespace nn9 {



}	// namespace nn9


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


// ===============================
// Count Leading Zeros
// ===============================
#if defined( _MSC_VER )
		#pragma intrinsic( _BitScanReverse )
	#ifdef _WIN64
		#pragma intrinsic( _BitScanReverse64 )
	#endif  // #ifdef _WIN64
#endif  // #if defined( _MSC_VER )

inline unsigned int                             CountLeadingZeros( uint16_t _ui16X ) {
#if defined( _MSC_VER )
	unsigned long ulIndex;
	auto ucIsNonZero = ::_BitScanReverse( &ulIndex, _ui16X );
	return ucIsNonZero ? (15 - static_cast<int>(ulIndex - 16)) : 16;
#else
	return _ui32X != 0 ? (__builtin_clz( static_cast<uint32_t>(_ui16X) ) - 16) : 16;
#endif  // #if defined( _MSC_VER )
}

inline unsigned int                             CountLeadingZeros( uint32_t _ui32X ) {
#if defined( _MSC_VER )
	unsigned long ulIndex;
	auto ucIsNonZero = ::_BitScanReverse( &ulIndex, _ui32X );
	return ucIsNonZero ? (31 - static_cast<int>(ulIndex)) : 32;
#else
	return _ui32X != 0 ? __builtin_clz( _ui32X ) : 32;
#endif  // #if defined( _MSC_VER )
}

inline unsigned int                             CountLeadingZeros( uint64_t _ui64X ) {
#if defined( _MSC_VER )
	#if defined( _WIN64 )
		// Benchmark against (1000000*50) values.
		// _BitScanReverse64(): 0.06879443333333333 seconds
		// Manual version: 0.188431 seconds.
		#if 1
			unsigned long ulIndex;
			auto ucIsNonZero = ::_BitScanReverse64( &ulIndex, _ui64X ) != 0;
			//return ((63 - static_cast<int>(ulIndex)) * ucIsNonZero) + (64 * !ucIsNonZero);
			return ucIsNonZero ? (63 - static_cast<int>(ulIndex)) : 64;
		#else
			unsigned long uiN = 0;
			if ( _ui64X == 0 ) { return 64; }
			if ( (_ui64X & 0xFFFFFFFF00000000ULL) == 0 ) { uiN += 32; _ui64X <<= 32; }
			if ( (_ui64X & 0xFFFF000000000000ULL) == 0 ) { uiN += 16; _ui64X <<= 16; }
			if ( (_ui64X & 0xFF00000000000000ULL) == 0 ) { uiN += 8;  _ui64X <<= 8; }
			if ( (_ui64X & 0xF000000000000000ULL) == 0 ) { uiN += 4;  _ui64X <<= 4; }
			if ( (_ui64X & 0xC000000000000000ULL) == 0 ) { uiN += 2;  _ui64X <<= 2; }
			if ( (_ui64X & 0x8000000000000000ULL) == 0 ) { uiN += 1; }

			return uiN;
		#endif  // #if 0
	#else
		if ( _ui64X == 0 ) { return 64; }
		unsigned int uiN = 0;

		#if 0
			// Benchmark against (1000000*50) values (x86 on x64 hardware). 
			// 0.0002651
			// 0.0002426333333333333
			if ( (_ui64X & 0xFFFFFFFF00000000ULL) == 0 ) { uiN += 32; _ui64X <<= 32; }
			if ( (_ui64X & 0xFFFF000000000000ULL) == 0 ) { uiN += 16; _ui64X <<= 16; }
			if ( (_ui64X & 0xFF00000000000000ULL) == 0 ) { uiN += 8;  _ui64X <<= 8; }
			if ( (_ui64X & 0xF000000000000000ULL) == 0 ) { uiN += 4;  _ui64X <<= 4; }
			if ( (_ui64X & 0xC000000000000000ULL) == 0 ) { uiN += 2;  _ui64X <<= 2; }
			if ( (_ui64X & 0x8000000000000000ULL) == 0 ) { uiN += 1; }
			return uiN;
		#else
			// Benchmark against (1000000*50) values (x86 on x64 hardware). 
			// 0.0002392 seconds.
			if ( _ui64X & 0xFFFFFFFF00000000ULL )        { uiN += 32; _ui64X >>= 32; }
			if ( _ui64X & 0xFFFF0000 )                   { uiN += 16; _ui64X >>= 16; }
			if ( _ui64X & 0xFFFFFF00 )                   { uiN += 8;  _ui64X >>= 8; }
			if ( _ui64X & 0xFFFFFFF0 )                   { uiN += 4;  _ui64X >>= 4; }
			if ( _ui64X & 0xFFFFFFFC )                   { uiN += 2;  _ui64X >>= 2; }
			if ( _ui64X & 0xFFFFFFFE )                   { uiN += 1; }
			return 63 - uiN;
		#endif  // #if 0
	#endif  // #if defined( _WIN64 )
#elif defined( __GNUC__ )
	return _ui64X != 0 ? __builtin_clzll( _ui64X ) : 64;
#endif  // #if defined( __GNUC__ )
}
