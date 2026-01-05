/**
 * Copyright L. Spiro 2025
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for the Ricoh 5A22.
 */


#pragma once



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
			LSN_AM_ABSOLUTE_LONG,															/**< Absolute long. */
			LSN_AM_ABSOLUTE_X,																/**< Absolute X addressing = 3 extra cycles + optional cycle. */
			LSN_AM_ABSOLUTE_Y,																/**< Absolute Y addressing = 3 extra cycles + optional cycle. */
			LSN_AM_ABSOLUTE_INDEXED_Y,														/**< Absolute Indexed, Y. */
			LSN_AM_INDIRECT_X,																/**< Indirect X addressing = 5 extra cycles. */
			LSN_AM_INDIRECT_Y,																/**< Indirect Y addressing = 4 extra cycles + optional cycle. */
			LSN_AM_INDIRECT,																/**< Absolute indirect addressing (JMP) = 4 extra cycles. */
		};

		/** Instructions. Numbers specified because these are used in look-up tables. */
		enum LSN_INSTRUCTIONS : uint8_t {
			LSN_I_ADC,																		/**< Add with carry. */
			LSN_I_AND,																		/**< AND with accumulator. */
			LSN_I_ASL,																		/**< Arithmetic shift left. */
			LSN_I_BCC,																		/**< Branch on carry clear. */
			LSN_I_BCS,																		/**< Branch on carry set. */
			LSN_I_BEQ,																		/**< Branch on equal (zero set). */
			LSN_I_BIT,																		/**< Bit test. */
			LSN_I_BMI,																		/**< Branch on minus (negative set). */
			LSN_I_BNE,																		/**< Branch on not equal (zero clear). */
			LSN_I_BPL,																		/**< Branch on plus (negative clear). */
			LSN_I_BRK,																		/**< Break/interrupt. */
			LSN_I_BVC,																		/**< Branch on overflow clear. */
			LSN_I_BVS,																		/**< Branch on overflow set. */
			LSN_I_CLC,																		/**< Clear carry. */
			LSN_I_CLD,																		/**< Clear decimal. */
			LSN_I_CLI,																		/**< Clear interrupt-disable. */
			LSN_I_CLV,																		/**< Clear overflow. */
			LSN_I_CMP,																		/**< Compare (with accumulator). */

			LSN_I_COP,																		/**< Coprocessor routine. */

			LSN_I_CPX,																		/**< Compare with X. */
			LSN_I_CPY,																		/**< Compare with Y. */
			LSN_I_DEC,																		/**< Decrement. */
			LSN_I_DEX,																		/**< Decrement X. */
			LSN_I_DEY,																		/**< Decrement Y. */
			LSN_I_EOR,																		/**< XOR with accumulator. */
			LSN_I_INC,																		/**< Increment. */
			LSN_I_INX,																		/**< Increment X. */
			LSN_I_INY,																		/**< Increment Y. */
			LSN_I_JMP,																		/**< Jump. */
			LSN_I_JSR,																		/**< Jump subroutine. */
			LSN_I_LDA,																		/**< Load accumulator. */
			LSN_I_LDX,																		/**< Load X. */
			LSN_I_LDY,																		/**< Load Y. */
			LSN_I_LSR,																		/**< Logical shift right. */
			LSN_I_NOP,																		/**< No operation. */
			LSN_I_ORA,																		/**< OR with accumulator. */
			LSN_I_PHA,																		/**< Push accumulator. */
			LSN_I_PHD,																		/**< Push direct page register. */
			LSN_I_PHP,																		/**< Push processor status (SR). */
			LSN_I_PLA,																		/**< Pull accumulator. */
			LSN_I_PLP,																		/**< Pull processor status (SR). */
			LSN_I_ROL,																		/**< Rotate left. */
			LSN_I_ROR,																		/**< Rotate right. */
			LSN_I_RTI,																		/**< Return from interrupt. */
			LSN_I_RTS,																		/**< Return from subroutine. */
			LSN_I_SBC,																		/**< Subtract with carry. */
			LSN_I_SEC,																		/**< Set carry. */
			LSN_I_SED,																		/**< Set decimal. */
			LSN_I_SEI,																		/**< Set interrupt-disable. */
			LSN_I_STA,																		/**< Store accumulator. */
			LSN_I_STX,																		/**< Store X. */
			LSN_I_STY,																		/**< Store Y. */
			LSN_I_TAX,																		/**< Transfer accumulator to X. */
			LSN_I_TAY,																		/**< Transfer accumulator to Y. */
			LSN_I_TCS,																		/**< Transfer 16 bit A to S. */
			LSN_I_TRB,																		/**< Test and reset memory bits against accumulator. */
			LSN_I_TSB,																		/**< Test and set memory bits against accumulator. */
			LSN_I_TSX,																		/**< Transfer stack pointer to X. */
			LSN_I_TXA,																		/**< Transfer X to accumulator. */
			LSN_I_TXS,																		/**< Transfer X to stack pointer. */
			LSN_I_TYA,																		/**< Transfer Y to accumulator. */

			LSN_I_ALR,																		/**< Illegal. Performs A & OP; LSR. */
			LSN_I_ASR,																		/**< Same as LSN_I_ALR. */
			LSN_I_ANC,																		/**< Illegal. Bitwise AND with carry. C flag is set using ASL rules. */
			LSN_I_ANC2,																		/**< Illegal. Bitwise AND with carry. C flag is set using ROL rules. */
			LSN_I_ANE,																		/**< Illegal and highly unstable. Performs A = (A | CONST) & X & OP, where CONST is effectively random. */
			LSN_I_ARR,																		/**< Illegal. Performs A = A & OP; A = (A >> 1) | (C << 7). */
			LSN_I_DCP,																		/**< Illegal. Performs OP--; CMP(A, OP). */
			LSN_I_ISC,																		/**< Illegal. Performs INC; SBC. */
			LSN_I_ISB,																		/**< Same as LSN_I_ISC. */
			LSN_I_LAS,																		/**< Illegal. Performs A = X = S = (OP & S). */
			LSN_I_LAX,																		/**< Illegal. Performs A = X = OP. */
			LSN_I_LXA,																		/**< Illegal and highly unstable. Performs X = A = ((A | CONST) & OP), where CONST is effectively random. */
			LSN_I_RLA,																		/**< Illegal. ROL OP, A &= OP. */
			LSN_I_RRA,																		/**< Illegal. ROR OP, A += OP + C. */
			LSN_I_SAX,																		/**< Illegal. Performs OP = A & X. */
			LSN_I_SBX,																		/**< Illegal. Performs X = (A & X) - OP, setting flags as with CMP. */
			LSN_I_SHA,																		/**< Illegal. Stores A & X & (high-byte of address + 1) at the address. */
			LSN_I_SHX,																		/**< Illegal. Stores X & (high-byte of address + 1) at the address. */
			LSN_I_SHY,																		/**< Illegal. Stores Y & (high-byte of address + 1) at the address. */
			LSN_I_SLO,																		/**< Illegal. OP <<= 1, A &= OP. */
			LSN_I_SRE,																		/**< Illegal. OP >>= 1, A ^= OP. */
			LSN_I_TAS,																		/**< Illegal. Performs S = A & X; Stores A & X & (high-byte of address + 1) at the address. */
			LSN_I_SHS,																		/**< Same as LSN_I_TAS. */
			LSN_I_USBC,																		/**< Illegal. Performs SBC + NOP. */
			LSN_I_DOP,																		/**< No operation. */
			LSN_I_TOP,																		/**< No operation. */
			LSN_I_JAM,																		/**< Illegal. Jams the machine repeatedly putting 0xFF on the bus. */

			LSN_I_NMI,																		/**< Non-opcode: NMI. */
			LSN_I_IRQ,																		/**< Non-opcode: IRQ. */

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
		 * Signals an IRQ to be handled before the next instruction.
		 */
		virtual void						Irq() {}

	protected :
		// == Enumerations.
		/** Other parameters. */
		enum LSN_MISC {
			LSN_M_MAX_INSTR_CYCLE_COUNT		= 9,
		};


		// == Members.
		uint64_t							m_ui64CycleCount = 0ULL;						/**< The total CPU cycles that have ticked. */
	};

}	// namespace lsn
