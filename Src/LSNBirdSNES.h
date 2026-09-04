/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A SNES emulator with the goal of being "micro-cycle–accurate." Many emulators claim to be "cycle-accurate"
 *	but are optimized to wait X cycles and then pump out all the work or otherwise do not actually divide all the work across
 *	all the cycles. In contrast, in this emulator, the work is correctly divided across the individual cycles for each
 *	instruction.
 * This means that multi-byte writes are correctly partitioned across cycles and partial data updates are possible, allowing
 *	for the more esoteric features of the system to be accurately emulated.  This means we should be able to support interrupt
 *	hijacking and any other cases that rely heavily on the cycle timing of the system.
 *
 * Additional options/features to facilitate accurate emulation:
 *	Start-Up: Start from known state or from random state.  Helps the random seed in some games.
 *	Hardware bugs will be emulated in both their buggy and fixed states (OAMADDR bugs (writing fewer than 8 ytes on the 2C02G)
 *		are examples of this).
 *	Unofficial opcodes used by games will be supported.
 *	The bus will be open and correctly maintain the last floating read.
 *	Etc.
 *
 * The CPU should be completely cycle-accurate, as every individual cycle is documented there. The same should apply to the
 *	PPU (questions surround PAL differences at the cycle level) and probably only loosely applies to the APU.  In the case of
 *	the APU, while each individual cycle may not be doing exactly the correct work, the goal is for the output to be exactly
 *	correct. This means envelope counters and sweep units etc. get updated within the correct cycles and then perhaps only
 *	minor adjustments to match the output exactly to the real thing.
 *
 * Timing will not be based off audio as is done in many emulators. We will use a real clock (with at minimum microsecond
 *	accuracy) and try to match real timings to real time units, which we can speed up and slow down as options.
 *
 * Performance should be decent enough for real-time. We are adding work to frames by adding a dereference and pointer-
 *	function call for each cycle, but the functions never leave instruction cache. If performance becomes a problem, it may
 *	warrant the creation of the approximate loops used in other emulators, leading to the scenario in which the approximate
 *	loops are used by most for gameplay and the slower original version of the emulator is used as a reference.
 *
 *
 * Other features will include:
 *	A debugger.
 *	A disassembler.
 *	An assembler.
 *	1-877-Tools-4-TAS.
 *		- Stepping and keylogging.
 *		- Movie-making.
 */


#pragma once

#include "Errors/LSNErrors.h"
#include "OS/LSNOs.h"

#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>

#ifndef LSN_TO_A
#define LSN_TO_A																true
#endif	// #ifndef LSN_TO_A
#ifndef LSN_TO_P
#define LSN_TO_P																false
#endif	// #ifndef LSN_TO_P
#ifndef LSN_FROM_A
#define LSN_FROM_A																true
#endif	// #ifndef LSN_FROM_A
#ifndef LSN_FROM_P
#define LSN_FROM_P																false
#endif	// #ifndef LSN_FROM_P


namespace lsn {

	// == Enumerations.
	/** Clock speeds. */
	enum LSN_CLOCK_SPEEDS : uint64_t {
		LSN_CS_NTSC_MASTER					= 236250000ULL,						/**< The master clock speed (236.25 MHz) without the 11 divisor. */
		LSN_CS_NTSC_MASTER_DIVISOR			= 11ULL,							/**< The master clock speed divisor. 236.25 MHz / 11 = 21477272.727272727272727272727273. */

		LSN_CS_PAL_MASTER					= 21281370ULL,						/**< The master clock speed (21.281370 MHz). */
		LSN_CS_PAL_MASTER_DIVISOR			= 1ULL,								/**< The master clock speed divisor. 21.281370 MHz / 1 = 21281370. */

		LSN_CS_NTSC_CPU_DIVISOR_PHI1		= 3ULL,								/**< 236.25 MHz / 11 / 3 = 7159090.9090909090909090909090909. */
		LSN_CS_PAL_CPU_DIVISOR_PHI1			= 3ULL,								/**< 236.25 MHz / 11 / 3 = 7159090.9090909090909090909090909. */

		LSN_CS_NTSC_CPU_DIVISOR_FAST		= 3ULL,								/**< 236.25 MHz / 11 / (3+3) = 3579545.4545454545454545454545455. */
		LSN_CS_PAL_CPU_DIVISOR_FAST			= 3ULL,								/**< 21281370 / 1 / (3+3) = 3546895. */

		LSN_CS_NTSC_CPU_DIVISOR_SLOW		= 5ULL,								/**< 236.25 MHz / 11 / (3+5) = 2684659.0909090909090909090909091. */
		LSN_CS_PAL_CPU_DIVISOR_SLOW			= 5ULL,								/**< 21281370 / 1 / (3+5) = 2660171.25. */

		LSN_CS_NTSC_CPU_DIVISOR_XSLOW		= 9ULL,								/**< 236.25 MHz / 11 / (3+9) = 1789772.7272727272727272727272727. */
		LSN_CS_PAL_CPU_DIVISOR_XSLOW		= 9ULL,								/**< 21281370 / 1 / (3+9) = 1773447.5. */

		LSN_CS_NTSC_CPU_DIVISOR_DMA_PHI1	= 4ULL,								/**< 236.25 MHz / 11 / (4+4) = 2684659.0909090909090909090909091. */
		LSN_CS_PAL_CPU_DIVISOR_DMA_PHI1		= 4ULL,								/**< 21281370 / 1 / (4+4) = 2660171.25. */

		LSN_CS_NTSC_CPU_DIVISOR_DMA_PHI2	= 4ULL,								/**< 236.25 MHz / 11 / (4+4) = 2684659.0909090909090909090909091. */
		LSN_CS_PAL_CPU_DIVISOR_DMA_PHI2		= 4ULL,								/**< 21281370 / 1 / (4+4) = 2660171.25. */

		LSN_CS_NTSC_PPU_DIVISOR				= 4ULL,								/**< 236.25 MHz / 11 / 4 = 5369318.1818181818181818181818182. */
		LSN_CS_PAL_PPU_DIVISOR				= 4ULL,								/**< 21281370 / 1 / 4 = 5320342.5. */


		LSN_CS_SPC700_MASTER				= 24576000ULL,						/**< The master clock speed (24576000 Hz). */
		LSN_CS_SPC700_MASTER_DIVISOR		= 1ULL,								/**< The master clock speed divisor. 24576000 Hz / 1 = 24576000. */

		LSN_CS_SPC700_DSP_DIVISOR			= (24ULL*32ULL),					/**< 24576000 / (24 * 32) = 32000. */
		LSN_CS_SPC700_CPU_DIVISOR			= 24ULL,							/**< 24576000 / 24 = 1024000. */
		LSN_CS_SPC700_TIMER_0_1_DIVISOR		= (24ULL*128ULL),					/**< 24576000 / (24 * 128) = 8000. */
		LSN_CS_SPC700_TIMER_2_DIVISOR		= (24ULL*16ULL),					/**< 24576000 / (24 * 16) = 64000. */
		LSN_CS_SPC700_CIC_DIVISOR			= 8ULL,								/**< 24576000 / 8 = 3072000. */
		LSN_CS_SPC700_EXP_DIVISOR			= 3ULL,								/**< 24576000 / 3 = 8192000. */


		LSN_CS_EXTERN_DSPn					= 7600000ULL,						/**< DSPn Plastic Type "[M]7600A". */
		LSN_CS_EXTERN_DSPn_DIVISOR			= 1ULL,								/**< 7600000 / 1 = 7600000. */

		LSN_CS_EXTERN_ST010					= 22000000ULL,						/**< Plastic Type "[M]22000C". */
		LSN_CS_EXTERN_ST010_DIVISOR			= 2ULL,								/**< 22000000 / 2 = 11000000. */

		LSN_CS_EXTERN_ST011					= 15000000ULL,						/**< Ceramic Type "15.00X". */
		LSN_CS_EXTERN_ST011_DIVISOR			= 1ULL,								/**< 15000000 / 1 = 15000000. */

		LSN_CS_EXTERN_ST018					= 24440000ULL,						/**< Plastic Type "[M]21440C". */
		LSN_CS_EXTERN_ST018_DIVISOR			= 1ULL,								/**< 24440000 / 1 = 24440000. */

		LSN_CS_EXTERN_CX4					= 20000000ULL,						/**< 20.000MHz   Plastic Type "[M]20000C" or "20.0MC/TDKY". */
		LSN_CS_EXTERN_CX4_DIVISOR			= 1ULL,								/**< 20000000 / 1 = 20000000. */

		LSN_CS_EXTERN_GSU1					= 21400000ULL,						/**< 21.4MHz     Plastic Type "21.4MC/TDKT". */
		LSN_CS_EXTERN_GSU1_DIVISOR			= 1ULL,								/**< 21400000 / 1 = 21400000. */

		LSN_CS_EXTERN_GSU2					= 21440000ULL,						/**< 21.44MHz    Plastic Type "[M]21440C". */
		LSN_CS_EXTERN_GSU2_DIVISOR			= 1ULL,								/**< 21440000 / 1 = 21440000. */

		LSN_CS_EXTERN_SGB2					= 20900000ULL,						/**< 20.9MHz     External oscillator (located on PCBs solder-side). */
		LSN_CS_EXTERN_SGB2_DIVISOR			= 1ULL,								/**< 20900000 / 1 = 20900000. */

		LSN_CS_EXTERN_BS_X					= 18432000ULL,						/**< 18.432MHz   Satellaview Receiver Unit (on expansion port). */
		LSN_CS_EXTERN_BS_X_DIVISOR			= 1ULL,								/**< 18432000 / 1 = 18432000. */

		LSN_CS_EXTERN_RTC_4513				= 32786000ULL,						/**< 32.768kHz   On-chip 32.768kHz quartz crystal in RTC chip. */
		LSN_CS_EXTERN_RTC_4513_DIVISOR		= 1ULL,								/**< 32786000 / 1 = 32786000. */

		LSN_CS_EXTERN_S_3520				= 32786000ULL,						/**< 32.768kHz   External 32.768kHz quartz crystal (SFC-Box). */
		LSN_CS_EXTERN_S_3520_DIVISOR		= 1ULL,								/**< 32786000 / 1 = 32786000. */

		/*
		 * To run clocks precisely, floating-point math must be avoided.  All inputs must be accumulated in integers.
		 * The formula to determine how many cycles go into a single tick is:
		 *	ELAPSED_TIME * MASTER / (ELAPSED_TIME_RESOLUTION * MASTER_DIVISOR * HW_DIVISOR).
		 * For example, if the system time resolution is 1000000 (microseconds), and the elapsed time is 2000000 (2 seconds), then the number of NTSC CPU cycles is:
		 *	2000000 * 236250000ULL / (1000000 * 11ULL * 12ULL) = 3579545 cycles.
		 * In PAL, that would be:
		 *	2000000 * 53203425ULL / (1000000 * 2ULL * 16ULL) = 3325214 cycles.
		 * 
		 * NTSC FPS:	60.098806265845099981531539094374.
		 *				29.991998324256388772517804775869.
		 * PAL FPS:		50.006978908188585607940446650124.
		 *				24.963425305747083291300196363176.
		 * 
		 * True NTSC SMPTE TV FPS:	59.94005994005994005994005994006.
		 *							29.97002997002997002997002997003.
		 *							23.976023976023976023976023976024.
		 *							47.952047952047952047952047952048.
		 */
	};

	/** Memory-access source. */
	enum LSN_ACCESS_SOURCE {
		LSN_AS_CPU,																/**< Memory is being accssed by the CPU. */
		LSN_AS_DMA,																/**< Memory is being accssed by DMA. */
	};

	/** Read/write/no-access. */
	enum LSN_CYCLE_TYPE {
		LSN_CT_READ,															/**< A read cycle. */
		LSN_CT_WRITE,															/**< A write cycle. */
		LSN_CT_NULL,															/**< A no-access cycle. */
	};

#ifdef __APPLE__
	/**
	 * \brief Writes a C-string to stderr (no newline).
	 *
	 * \param _pcStr The null-terminated string to output.
	 */
	static inline void						DebugA( const char * _pcStr ) {
		::fputs( _pcStr, stderr );
	}

	/**
	 * \brief Writes a wide C-string to stderr (no newline).
	 *
	 * \param _pwcStr The null-terminated wide string to output.
	 */
	static inline void						DebugW( const wchar_t * _pwcStr ) {
		::fputws( _pwcStr, stderr );
	}

	/**
	 * \brief Writes a line to stderr.
	 *
	 * \param _sStr The string to output.
	 */
	static inline void						DebugLine( const std::string &_sStr ) {
		::fwrite( _sStr.data(), 1, _sStr.size(), stderr );
		::fputc( '\n', stderr );
	}
#elif defined( _WIN32 )
	/**
	 * \brief Writes a C-string to the debugger (no newline).
	 *
	 * \param _pcStr The null-terminated string to output.
	 */
	static inline void						DebugA( const char * _pcStr ) {
		::OutputDebugStringA( _pcStr );
	}

	/**
	 * \brief Writes a wide C-string to the debugger (no newline).
	 *
	 * \param _pwcStr The null-terminated wide string to output.
	 */
	static inline void						DebugW( const wchar_t * _pwcStr ) {
		::OutputDebugStringW( _pwcStr );
	}

	/**
	 * \brief Writes a line to the debugger.
	 *
	 * \param _sStr The string to output.
	 */
	static inline void						DebugLine( const std::string &_sStr ) {
		::OutputDebugStringA( (_sStr + "\r\n").c_str() );
	}
#endif	// #ifdef __APPLE__

}	// namespace lsn
