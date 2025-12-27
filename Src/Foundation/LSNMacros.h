/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Cross-platform macros.
 */

#pragma once


#if defined( _MSC_VER )
	#define NN9_FASTCALL										__fastcall
	#define NN9_CDECL											__cdecl
	#define NN9_EXPECT( COND, VAL )								(COND)
	#define NN9_PREFETCH_LINE( ADDR )							_mm_prefetch( reinterpret_cast<const char *>(ADDR), _MM_HINT_T0 )
	#define NN9_PREFETCH_LINE_WRITE( ADDR )

	// Microsoft Visual Studio Compiler
	#define NN9_ALIGN( N ) 										__declspec( align( N ) )
	#define NN9_FALLTHROUGH										[[fallthrough]];
	#define NN9_LIKELY( x )										( x ) [[likely]]
	#define NN9_UNLIKELY( x )									( x ) [[unlikely]]

	#define NN9_ASM_BEGIN										__asm {
	#define NN9_ASM_END											}
#elif defined( __GNUC__ ) || defined( __clang__ )
	#define NN9_FASTCALL
	#if defined( __i386__ ) || defined( __x86_64__ ) || defined( __amd64__ )
		#define NN9_CDECL										__attribute__( (cdecl) )
	#else
		#define NN9_CDECL
	#endif
	#define NN9_EXPECT( COND, VAL )								__builtin_expect( !!(COND), (VAL) )
	#define NN9_PREFETCH_LINE( ADDR )							__builtin_prefetch( reinterpret_cast<const void *>(ADDR), 0, 3 )
	#define NN9_PREFETCH_LINE_WRITE( ADDR )						__builtin_prefetch( reinterpret_cast<const void *>(ADDR), 1, 3 )

	// GNU Compiler Collection (GCC) or Clang
	#define NN9_ALIGN( N ) 										__attribute__( (aligned( N )) )
	#define NN9_FALLTHROUGH
	#define NN9_LIKELY( x )										( __builtin_expect( !!(x), 1 ) )
	#define NN9_UNLIKELY( x )									( __builtin_expect( !!(x), 0 ) )
#else
	#error "Unsupported compiler"
#endif	// #if defined( _MSC_VER )


#if defined( _M_IX86 ) || defined( __i386__ )
	#define NN9_X86												1
#elif defined( _M_X64 ) || defined( __x86_64__ ) || defined( __amd64__ )
	#define NN9_X64												1
#endif	// #if defined( _M_IX86 ) || defined( __i386__ )


#ifdef _DEBUG
	#if defined( _MSC_VER )
		// For Microsoft Visual C++
		#define NN9_OPTIMIZE_ON                             	__pragma( optimize( "", on ) )
		#define NN9_OPTIMIZE_OFF                            	__pragma( optimize( "", off ) )
	#elif defined( __clang__ ) && defined( __APPLE__ )
		// For Apple Clang (Xcode)
		#define NN9_OPTIMIZE_ON                             	_Pragma( "clang optimize on" )
		#define NN9_OPTIMIZE_OFF                            	_Pragma( "clang optimize off" )
	#elif defined( __clang__ )
		// For Clang (non-Apple)
		#define NN9_OPTIMIZE_ON                             	_Pragma( "clang optimize on" )
		#define NN9_OPTIMIZE_OFF                            	_Pragma( "clang optimize off" )
	#elif defined( __GNUC__ )
		// For GCC
		#define NN9_OPTIMIZE_ON                             	\
			_Pragma( "GCC push_options" )                   	\
			_Pragma( "GCC optimize (\"O3\")" )
		#define NN9_OPTIMIZE_OFF                            	\
			_Pragma( "GCC pop_options" )
	#else
		#define NN9_OPTIMIZE_ON
		#define NN9_OPTIMIZE_OFF
	#endif
#else
	#define NN9_OPTIMIZE_ON
	#define NN9_OPTIMIZE_OFF
#endif
