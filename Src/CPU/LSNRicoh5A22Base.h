/**
 * Copyright L. Spiro 2025
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for the Ricoh 5A22.
 */


#pragma once

#include "../LSNBirdSNES.h"

#include <cstdint>

namespace lsn {

	/**
	 * Class CRicoh5A22Base
	 * \brief The base class for the Ricoh 5A22.
	 *
	 * Description: The base class for the Ricoh 5A22.
	 */
	class CRicoh5A22Base {
	public :
		CRicoh5A22Base() {}


		// == Enumerations.
		/** Addressing modes. */
		enum LSN_ADDRESSING_MODES : uint8_t {
			LSN_AM_IMPLIED,																	/**< Implied addressing = 1 extra cycle. */
			LSN_AM_ACCUMULATOR,																/**< Accumulator = 1 extra cycle. */
			LSN_AM_IMMEDIATE,																/**< Immediate = 1 extra cycle. */
			LSN_AM_ZERO_PAGE,																/**< Zero-page = 2 extra cycles. */
			LSN_AM_ZERO_PAGE_X,																/**< Zero-page-X = 3 extra cycles. */
			LSN_AM_ZERO_PAGE_Y,																/**< Zero-page-Y = 3 extra cycles. */
			LSN_AM_DIRECT_PAGE,																/**< Direct page, up to 2 extra cycles. */
			LSN_AM_DIRECT_PAGE_INDEXED_X,													/**< Direct page indexed X. */
			LSN_AM_DIRECT_PAGE_INDIRECT,													/**< Direct page indirect. */
			LSN_AM_DIRECT_PAGE_INDIRECT_LONG,												/**< Direct page, up to 2 extra cycles. */
			LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y,											/**< DP Indirect Indexed, Y. */
			LSN_AM_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y,										/**< DP Indirect Long Indexed, Y. */
			LSN_AM_RELATIVE,																/**< Relative jumping = 2 extra cycles. */
			LSN_AM_STACK_RELATIVE,															/**< Relative jumping on stackr. */
			LSN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y,										/**< Stack relative indirect indexed Y. */
			LSN_AM_ABSOLUTE,																/**< Absolute addressing = 3 extra cycles. */
			LSN_AM_ABSOLUTE_INDIRECT,														/**< Absolute indirect. */
			LSN_AM_ABSOLUTE_INDEXED_INDIRECT,												/**< Absolute indexed indirect (Jump). */
			LSN_AM_ABSOLUTE_LONG,															/**< Absolute long, X. */
			LSN_AM_ABSOLUTE_LONG_X,															/**< Absolute long. */
			LSN_AM_ABSOLUTE_X,																/**< Absolute X addressing = 3 extra cycles + optional cycle. */
			LSN_AM_ABSOLUTE_Y,																/**< Absolute Y addressing = 3 extra cycles + optional cycle. */
			LSN_AM_ABSOLUTE_INDEXED_Y,														/**< Absolute Indexed, Y. */
			LSN_AM_INDIRECT_X,																/**< Indirect X addressing = 5 extra cycles. */
			LSN_AM_INDIRECT_Y,																/**< Indirect Y addressing = 4 extra cycles + optional cycle. */
			LSN_AM_INDIRECT,																/**< Absolute indirect addressing (JMP) = 4 extra cycles. */
			LSN_AM_BLOCK_MOVE,																/**< Block Move (xyc) addressing used by the Block Move instructions. */
		};

		/** Instructions. Numbers specified because these are used in look-up tables. */
		enum LSN_INSTRUCTIONS : uint8_t {
#define LSN_INST( NAME, DESC )				LSN_I_ ## NAME,
#include "LSNInstructions.inl"
#undef LSN_INST

			LSN_I_TOTAL
		};
		
		
		// == Functions.
		/**
		 * Gets the current CPU cycle count.
		 *
		 * \return Returns the current CPU cycle count.
		 */
		inline uint64_t						GetCycleCount() const { return m_ui64CycleCount; }

		/**
		 * Sets the clock divisors for bus access.
		 * 
		 * \param _ui8Phi1 The fast divisor (typically 3 or LSN_CS_*_CPU_DIVISOR_PHI1).
		 * \param _ui8Fast The fast divisor (typically 3 or LSN_CS_*_CPU_DIVISOR_FAST).
		 * \param _ui8Slow The slow divisor (typically 5 or LSN_CS_*_CPU_DIVISOR_SLOW).
		 * \param _ui8XSlow The extra-slow divisor (typically 9 or LSN_CS_*_CPU_DIVISOR_XSLOW).
		 **/
		inline void							SetBusDivisors( uint8_t _ui8Phi1, uint8_t _ui8Fast, uint8_t _ui8Slow, uint8_t _ui8XSlow ) {
			m_ui8Phi1Div = _ui8Phi1;
			m_ui8FastDiv = _ui8Fast;
			m_ui8SlowDiv = _ui8Slow;
			m_ui8XSlowDiv = _ui8XSlow;
		}

		/**
		 * Signals an IRQ to be handled before the next instruction.
		 */
		void								Irq() {}

	protected :
		// == Enumerations.
		/** Other parameters. */
		enum LSN_MISC {
			LSN_M_MAX_INSTR_CYCLE_COUNT		= 9,
		};


		// == Members.
		uint64_t							m_ui64CycleCount = 0ULL;						/**< The total CPU cycles that have ticked. */
		uint8_t								m_ui8Phi1Div = LSN_CS_NTSC_CPU_DIVISOR_FAST;	/**< The PHI1 divisor. */
		uint8_t								m_ui8FastDiv = LSN_CS_NTSC_CPU_DIVISOR_FAST;	/**< The fast divisor. */
		uint8_t								m_ui8SlowDiv = LSN_CS_NTSC_CPU_DIVISOR_SLOW;	/**< The slow divisor. */
		uint8_t								m_ui8XSlowDiv = LSN_CS_NTSC_CPU_DIVISOR_XSLOW;	/**< The extra-slow divisor. */
	};

}	// namespace lsn
