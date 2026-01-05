/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Cross-platform macros.
 */

#pragma once


#if defined( _MSC_VER )
	#define LSN_FASTCALL										__fastcall
	#define LSN_CDECL											__cdecl
	#define LSN_EXPECT( COND, VAL )								(COND)
	#define LSN_PREFETCH_LINE( ADDR )							_mm_prefetch( reinterpret_cast<const char *>(ADDR), _MM_HINT_T0 )
	#define LSN_PREFETCH_LINE_WRITE( ADDR )

	// Microsoft Visual Studio Compiler
	#define LSN_ALIGN( N ) 										__declspec( align( N ) )
	#define LSN_ALIGN_STRUCT( N )								LSN_ALIGN( N )
	#define LSN_ALIGN_STRUCT_END( N )
	#define LSN_FALLTHROUGH										[[fallthrough]];
	#define LSN_LIKELY( x )										( x ) [[likely]]
	#define LSN_UNLIKELY( x )									( x ) [[unlikely]]

	#define LSN_ASM_BEGIN										__asm {
	#define LSN_ASM_END											}
#elif defined( __GNUC__ ) || defined( __clang__ )
	#define LSN_FASTCALL
	#if defined( __i386__ ) || defined( __x86_64__ ) || defined( __amd64__ )
		#define LSN_CDECL										__attribute__( (cdecl) )
	#else
		#define LSN_CDECL
	#endif
	#define LSN_EXPECT( COND, VAL )								__builtin_expect( !!(COND), (VAL) )
	#define LSN_PREFETCH_LINE( ADDR )							__builtin_prefetch( reinterpret_cast<const void *>(ADDR), 0, 3 )
	#define LSN_PREFETCH_LINE_WRITE( ADDR )						__builtin_prefetch( reinterpret_cast<const void *>(ADDR), 1, 3 )

	// GNU Compiler Collection (GCC) or Clang
	#define LSN_ALIGN( N )										__attribute__( (aligned( N )) )
	#define LSN_ALIGN_STRUCT( N )
	#define LSN_ALIGN_STRUCT_END( N ) 							LSN_ALIGN( N )
	#define LSN_FALLTHROUGH
	#define LSN_LIKELY( x )										( __builtin_expect( !!(x), 1 ) )
	#define LSN_UNLIKELY( x )									( __builtin_expect( !!(x), 0 ) )
#else
	#error "Unsupported compiler"
#endif	// #if defined( _MSC_VER )


#if defined( _M_IX86 ) || defined( __i386__ )
	#define LSN_X86												1
#elif defined( _M_X64 ) || defined( __x86_64__ ) || defined( __amd64__ )
	#define LSN_X64												1
#endif	// #if defined( _M_IX86 ) || defined( __i386__ )


#ifdef _DEBUG
	#if defined( _MSC_VER )
		// For Microsoft Visual C++
		#define LSN_OPTIMIZE_ON                             	__pragma( optimize( "", on ) )
		#define LSN_OPTIMIZE_OFF                            	__pragma( optimize( "", off ) )
	#elif defined( __clang__ ) && defined( __APPLE__ )
		// For Apple Clang (Xcode)
		#define LSN_OPTIMIZE_ON                             	_Pragma( "clang optimize on" )
		#define LSN_OPTIMIZE_OFF                            	_Pragma( "clang optimize off" )
	#elif defined( __clang__ )
		// For Clang (non-Apple)
		#define LSN_OPTIMIZE_ON                             	_Pragma( "clang optimize on" )
		#define LSN_OPTIMIZE_OFF                            	_Pragma( "clang optimize off" )
	#elif defined( __GNUC__ )
		// For GCC
		#define LSN_OPTIMIZE_ON                             	\
			_Pragma( "GCC push_options" )                   	\
			_Pragma( "GCC optimize (\"O3\")" )
		#define LSN_OPTIMIZE_OFF                            	\
			_Pragma( "GCC pop_options" )
	#else
		#define LSN_OPTIMIZE_ON
		#define LSN_OPTIMIZE_OFF
	#endif
#else
	#define LSN_OPTIMIZE_ON
	#define LSN_OPTIMIZE_OFF
#endif
