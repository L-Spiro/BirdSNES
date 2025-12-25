#pragma once

#include <cmath>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( _MSC_VER ) && defined( _M_AMD64 )

// 64-bit implementation in MASM (MSVC only).
extern void 		SinCos( double _dRadians, double * _pdSin, double * _pdCos );

#elif defined( _MSC_VER ) && defined( _M_IX86 )

// 32-bit implementation in MSVC inline assembly (MSVC only).
inline void 		SinCos( double _dRadians, double * _pdSin, double * _pdCos ) {
	double dSin, dCos;
	__asm {
		fld QWORD PTR[_dRadians]
		fsincos
		fstp QWORD PTR[dCos]
		fstp QWORD PTR[dSin]
		fwait
	}
	(*_pdSin) = dSin;
	(*_pdCos) = dCos;
}

inline void 		SinCosF( float _fAngle, float * _pfSin, float * _pfCos ) {
	float fSinT, fCosT;
	__asm {
		fld DWORD PTR[_fAngle]
		fsincos
		fstp DWORD PTR[fCosT]
		fstp DWORD PTR[fSinT]
		fwait
	}
	(*_pfSin) = fSinT;
	(*_pfCos) = fCosT;
}

#else

// Clang/GCC (including Xcode): use libm.
inline void 		SinCos( double _dRadians, double * _pdSin, double * _pdCos ) {
#if defined( __APPLE__ ) || defined( __GNUC__ ) || defined( __clang__ )
	::__sincos( _dRadians, _pdSin, _pdCos );
#else
	(*_pdSin) = std::sin( _dRadians );
	(*_pdCos) = std::cos( _dRadians );
#endif
}

inline void 		SinCosF( float _fAngle, float * _pfSin, float * _pfCos ) {
#if defined( __APPLE__ ) || defined( __GNUC__ ) || defined( __clang__ )
	::__sincosf( _fAngle, _pfSin, _pfCos );
#else
	(*_pfSin) = std::sinf( _fAngle );
	(*_pfCos) = std::cosf( _fAngle );
#endif
}

#endif

#if defined( __cplusplus )
} // extern "C"
#endif
