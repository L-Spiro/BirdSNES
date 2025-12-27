/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Includes all OS headers.
 */

#pragma once

#if defined( _WIN32 ) || defined( _WIN64 )
#include "LSNWindows.h"
#elif defined( __APPLE__ )
#include "LSNApple.h"

#include <pthread.h>
#include <sched.h>
#else
#endif  // #if defined( _WIN32 ) || defined( _WIN64 )

#include <filesystem>


#ifdef _WIN32

/**
 * Gets the path to this executable.  Must be called within try/catch block.
 * 
 * \return Returns the path to this executable file or throws on error.
 * \throw std::runtime_error Thrown if the path to the file is either 0 characters long or more than 1 megabyte long.
 * \throw std::bad_alloc Thrown if there is not enough memory to handle the internal allocations necessary to store and return the string.
 **/
inline std::filesystem::path					GetThisPath() {
	DWORD dwBufSize = 0x8000;
	std::vector<wchar_t> vBuffer;

	while ( true ) {
		vBuffer.resize( dwBufSize );
		DWORD dwLen = ::GetModuleFileNameW( NULL, vBuffer.data(), dwBufSize );

		if ( dwLen == 0 ) { throw std::runtime_error( "GetThisPath: Error getting executable path." ); }
		else if ( dwLen < dwBufSize ) {
			// Successfully retrieved the path.
			return std::wstring( vBuffer.data(), dwLen );
		}
		else {
			// Buffer was too small, increase size and retry.
			dwBufSize *= 2;
			if ( dwBufSize > 1 << 20 ) { // Limit to 1 MB.
				throw std::runtime_error( "GetThisPath: Executable path is too long." );
			}
		}
	}
}


#elif defined( __linux__ )
#include <unistd.h>
#include <errno.h>

/**
 * Gets the path to this executable.  Must be called within try/catch block.
 * 
 * \return Returns the path to this executable file or throws on error.
 * \throw std::runtime_error Thrown if the path to the file is either 0 characters long or more than 1 megabyte long.
 * \throw std::bad_alloc Thrown if there is not enough memory to handle the internal allocations necessary to store and return the string.
 **/
inline std::filesystem::path					GetThisPath() {
	size_t sBufferSize = 1024;
	std::vector<char> vBuffer;

	while ( true ) {
		vBuffer.resize( sBufferSize );

		ssize_t sLength = readlink( "/proc/self/exe", vBuffer.data(), sBufferSize );

		if ( sLength == -1 ) {
			throw std::runtime_error( "GetThisPath: Error getting executable path: " + std::string( strerror( errno ) ) );
		}
		else if ( static_cast<size_t>(sLength) < sBufferSize ) {
			return std::string( vBuffer.data(), sLength );
		}
		else {
			sBufferSize *= 2;
			if ( sBufferSize > 1 << 20 ) { // Limit to 1 MB.
				throw std::runtime_error( "GetThisPath: Executable path is too long." );
			}
		}
	}
}

#elif defined( __APPLE__ )
#include <limits.h>
#include <mach-o/dyld.h>
#include <sched.h>
#include <stdlib.h>
#include <vector>

/**
 * Gets the path to this executable.  Must be called within try/catch block.
 * 
 * \return Returns the path to this executable file or throws on error.
 * \throw std::runtime_error Thrown if the path to the file is either 0 characters long or more than 1 megabyte long.
 * \throw std::bad_alloc Thrown if there is not enough memory to handle the internal allocations necessary to store and return the string.
 **/
inline std::filesystem::path					GetThisPath() {
	uint32_t ui32BufferSize = 0;
	// Get the required buffer size.
	if ( _NSGetExecutablePath( NULL, &ui32BufferSize ) != -1 ) {
		throw std::runtime_error( "GetThisPath: Unexpected error getting executable path size." );
	}

	std::vector<char> vBuffer( ui32BufferSize );
	if ( _NSGetExecutablePath( vBuffer.data(), &ui32BufferSize ) != 0 ) {
		throw std::runtime_error( "GetThisPath: Error getting executable path." );
	}

	// Resolve any symbolic links to get the absolute path.
	char szRealPath[PATH_MAX];
	if ( ::realpath( vBuffer.data(), szRealPath ) == NULL ) {
		throw std::runtime_error( "GetThisPath: Error resolving real path." );
	}

	return std::string( szRealPath );
}

#endif	// #ifdef _WIN32


#ifdef _WIN32
/**
 * Sets the current thread to its highest priority.
 **/
inline void                                     SetThreadHighPriority() {
    ::SetThreadPriority( ::GetCurrentThread(), THREAD_PRIORITY_HIGHEST );
}
/**
 * Sets the current thread to its normal priority.
 **/
inline void                                     SetThreadNormalPriority() {
    ::SetThreadPriority( ::GetCurrentThread(), THREAD_PRIORITY_NORMAL );
}
#else
/**
 * Sets the current thread to its highest priority.
 **/
inline void                                     SetThreadHighPriority() {
    sched_param spSchParms;
    spSchParms.sched_priority = ::sched_get_priority_max( SCHED_FIFO );
    ::pthread_setschedparam( ::pthread_self(), SCHED_FIFO, &spSchParms );
}
/**
 * Sets the current thread to its normal priority.
 **/
inline void                                     SetThreadNormalPriority() {
    sched_param spSchParms;
    spSchParms.sched_priority = 0;  // Normal priority
    ::pthread_setschedparam( ::pthread_self(), SCHED_OTHER, &spSchParms );
}
#endif  // #ifdef _WIN32


#ifdef _WIN32
/**
 * Assigns thread affinity to a given core.
 * 
 * \param _hHandle A handle to the thread whose core affinity is to be updated.
 * \param _sCoreId The index of the core to which to set the thread’s affinity.
 **/
inline void										SetThreadAffinity( HANDLE _hHandle, size_t _sCoreId ) {
	// Set thread affinity to the specified core on Windows.
	DWORD_PTR dwptrMask = DWORD_PTR( 1 ) << _sCoreId;
	::SetThreadAffinityMask( _hHandle, dwptrMask );
}
#elif defined( __linux__ )
/**
 * Assigns thread affinity to a given core.
 * 
 * \param _tHandle A handle to the thread whose core affinity is to be updated.
 * \param _sCoreId The index of the core to which to set the thread’s affinity.
 **/
inline void										SetThreadAffinity( pthread_t _tHandle, size_t _sCoreId ) {
	// Set thread affinity on Linux
	cpu_set_t csCpuSet;
	CPU_ZERO( &csCpuSet );
	CPU_SET( _sCoreId, &csCpuSet );
	::pthread_setaffinity_np( _tHandle, sizeof( cpu_set_t ), &csCpuSet );
}
#elif defined( __APPLE__ )
#include <mach/mach.h>
#include <mach/thread_policy.h>
#include <pthread.h>

/**
 * Assigns thread affinity to a given core.
 * 
 * \param _tHandle A handle to the thread whose core affinity is to be updated.
 * \param _sCoreId The index of the core to which to set the thread’s affinity.
 **/
inline void 									SetThreadAffinity( pthread_t _tHandle, size_t _sCoreId ) {
	// Set thread affinity on macOS
	::thread_affinity_policy_data_t tapdPolicy = { static_cast<integer_t>(_sCoreId) };
	::thread_port_t mach_thread = ::pthread_mach_thread_np( _tHandle );
	::thread_policy_set( mach_thread, THREAD_AFFINITY_POLICY, reinterpret_cast<::thread_policy_t>(&tapdPolicy), 1 );
}
#endif	// #ifdef _WIN32

/**
 * Assigns current thread’s affinity to a given core.
 * 
 * \param _sCoreId The index of the core to which to set the current thread’s affinity.
 **/
inline void										SetThreadAffinity( size_t _sCoreId ) {
#ifdef _WIN32
	::SetThreadAffinity( ::GetCurrentThread(), _sCoreId );
#elif defined( __APPLE__ ) || defined( __linux__ )
	::SetThreadAffinity( ::pthread_self(), _sCoreId );
#endif	// #ifdef _WIN32
}


