/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: An SPC700 processor.
 */


#pragma once

#include "../LSNBirdSNES.h"
#include "../Bus/LSNBusB.h"
#include "../Foundation/LSNBits.h"
#include "../System/LSNTickable.h"

#ifdef LSN_CPU_VERIFY
#include <LSONJson.h>
#endif	// #ifdef LSN_CPU_VERIFY

#define LSN_SPC700_INSTR_START_PHI1( ISREAD )									/*m_fsState.bIsReadCycle = (ISREAD)*/
#define LSN_SPC700_INSTR_END_PHI1
#define LSN_SPC700_INSTR_START_PHI2_READ_BUSA( ADDR, BANK, RESULT, SPEED )		RESULT = m_baBusA.Read( uint16_t( ADDR ), uint8_t( BANK ), (SPEED) )
#define LSN_SPC700_INSTR_START_PHI2_WRITE_BUSA( ADDR, BANK, VAL, SPEED )		m_baBusA.Write( uint16_t( ADDR ), uint8_t( BANK ), uint8_t( VAL ), (SPEED) )
#define LSN_SPC700_INSTR_START_PHI2_READ0_BUSA( ADDR, RESULT, SPEED )			RESULT = m_baBusA.ReadBank0( uint16_t( ADDR ), (SPEED) )
#define LSN_SPC700_INSTR_START_PHI2_WRITE0_BUSA( ADDR, VAL, SPEED )				m_baBusA.WriteBank0( uint16_t( ADDR ), uint8_t( VAL ), (SPEED) )
#define LSN_SPC700_INSTR_END_PHI2

#define LSN_SPC700_NEXT_FUNCTION_BY( AMT )										m_fsState.ui8FuncIndex += AMT
#define LSN_SPC700_NEXT_FUNCTION												LSN_NEXT_FUNCTION_BY( 1 )
#define LSN_SPC700_FINISH_INST( CHECK_INTERRUPTS )								if constexpr ( CHECK_INTERRUPTS ) { LSN_CHECK_INTERRUPTS; } LSN_NEXT_FUNCTION

#define LSN_SPC700_CHECK_INTERRUPTS												if ( !(m_fsState.rRegs.ui8Status & I()) ) { m_bHandleIrq = m_bIrqStatusPhi1Flag; } m_bHandleNmi |= m_bDetectedNmi

#define LSN_SPC700_PUSH( VAL, SPEED )											LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), (VAL), (SPEED) ); m_fsState.ui16SModify = uint16_t( int16_t( -1 + _i8SOff ) )
#define LSN_SPC700_POP( RESULT, SPEED )											LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), (RESULT), (SPEED) ); m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) )

#define LSN_SPC700_PUSH_SPECIAL( VAL, SPEED )									LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.bEmulationMode ? ((0x100 | m_fsState.rRegs.ui8S[0]) + _i8SOff) : (m_fsState.rRegs.ui16S + _i8SOff), (VAL), (SPEED) ); m_fsState.ui16SModify = uint16_t( int16_t( -1 + _i8SOff ) )
#define LSN_SPC700_POP_SPECIAL( RESULT, SPEED )									LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? ((0x100 | m_fsState.rRegs.ui8S[0]) + _i8SOff) : (m_fsState.rRegs.ui16S + _i8SOff), (RESULT), (SPEED) ); m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) )

#define LSN_SPC700_UPDATE_PC													if LSN_LIKELY( m_fsState.bAllowWritingToPc ) { m_fsState.rRegs.ui16Pc += m_fsState.ui16PcModify; } m_fsState.ui16PcModify = 0
#define LSN_SPC700_UPDATE_S														m_fsState.rRegs.ui16S += m_fsState.ui16SModify; m_fsState.ui16SModify = 0; if LSN_UNLIKELY( m_fsState.bEmulationMode ) { m_fsState.rRegs.ui8S[1] = 1; }

#define LSN_SPC700_R															CSpc700::LSN_CT_READ
#define LSN_SPC700_W															CSpc700::LSN_CT_WRITE
#define LSN_SPC700_N															CSpc700::LSN_CT_NULL

#define LSN_SPC700_TO_A															true
#define LSN_SPC700_TO_P															false
#define LSN_SPC700_FROM_A														true
#define LSN_SPC700_FROM_P														false

#ifdef LSN_SPC700_CPU_VERIFY
//#define LSN_SPC700_CYCLES_DOC													1
#endif	// #ifdef LSN_SPC700_CPU_VERIFY


namespace lsn {

	/**
	 * Class CSpc700
	 * \brief An SPC700 processor.
	 *
	 * Description: An SPC700 processor.
	 */
	class CSpc700 : public CTickable {
	public :
		CSpc700( CBusB &_bBusB );
		~CSpc700();


		// == Enumerations.
		/** Other parameters. */
		enum LSN_MISC {
			LSN_M_MAX_INSTR_CYCLE_COUNT											= 9,
		};

		/** Status flags. */
		static constexpr uint8_t												C() { return (1 << 0); }														/**< Carry         (0=No Carry, 1=Carry). */
		static constexpr uint8_t												Z() { return (1 << 1); }														/**< Zero          (0=Nonzero, 1=Zero). */
		static constexpr uint8_t												I() { return (1 << 2); }														/**< IRQ Disable   (0=IRQ Enable, 1=IRQ Disable). */
		static constexpr uint8_t												H() { return (1 << 3); }														/**< Half-Carry. */
		static constexpr uint8_t												X() { return (1 << 4); }														/**< Break Flag    (0=IRQ/NMI, 1=BRK/PHP opcode)  (0=16bit, 1=8bit). */
		static constexpr uint8_t												P() { return (1 << 5); }														/**< Direct Page.  (0=High Byte Set to 0, 1 = High Byte set to 1). */
		static constexpr uint8_t												V() { return (1 << 6); }														/**< Overflow      (0=No Overflow, 1=Overflow). */
		static constexpr uint8_t												N() { return (1 << 7); }														/**< Negative/Sign (0=Positive, 1=Negative). */

		/** Addressing modes. */
		enum LSN_ADDRESSING_MODES : uint8_t {
			LSN_AM_IMPLIED,														/**< Implied addressing (also covers Implied Accumulator). */
			LSN_AM_ACCUMULATOR,													/**< Accumulator addressing. */
			LSN_AM_IMMEDIATE,													/**< Immediate addressing (#imm). */
			LSN_AM_DIRECT_PAGE,													/**< Direct page (dp). */
			LSN_AM_DIRECT_PAGE_INDEXED_X,										/**< Direct page indexed X (dp+X). */
			LSN_AM_DIRECT_PAGE_INDEXED_Y,										/**< Direct page indexed Y (dp+Y). */
			LSN_AM_ABSOLUTE,													/**< Absolute addressing (!abs). */
			LSN_AM_ABSOLUTE_X,													/**< Absolute X addressing (!abs+X). */
			LSN_AM_ABSOLUTE_Y,													/**< Absolute Y addressing (!abs+Y). */
			LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X,								/**< Direct page indexed indirect X ([dp+X]). */
			LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y,								/**< Direct page indirect indexed Y ([dp]+Y). */
			LSN_AM_ABSOLUTE_INDEXED_INDIRECT_X,									/**< Absolute indexed indirect X ([!abs+X] for JMP). */
			LSN_AM_RELATIVE,													/**< Relative jumping (rel). */
			LSN_AM_DIRECT_PAGE_RELATIVE,										/**< Direct page relative (dp, rel). */
			LSN_AM_DIRECT_PAGE_INDEXED_X_RELATIVE,								/**< Direct page indexed X relative (dp+X, rel). */
			LSN_AM_INDIRECT_X,													/**< Indirect X addressing ((X)). */
			LSN_AM_INDIRECT_X_AUTO_INC,											/**< Indirect X auto-increment ((X)+). */
			LSN_AM_INDIRECT_X_INDIRECT_Y,										/**< Indirect page to indirect page ((X), (Y)). */
			LSN_AM_DIRECT_PAGE_DIRECT_PAGE,										/**< Direct page to direct page (dp, dp). */
			LSN_AM_DIRECT_PAGE_IMMEDIATE,										/**< Immediate to direct page (dp, #imm). */
			LSN_AM_DIRECT_PAGE_BIT,												/**< Direct page bit (dp.bit). */
			LSN_AM_DIRECT_PAGE_BIT_RELATIVE,									/**< Direct page bit relative jumping (dp.bit, rel). */
			LSN_AM_ABSOLUTE_BIT,												/**< Absolute boolean bit (mem.bit). */
			LSN_AM_UPAGE,														/**< U-Page / PCALL (upage). */
			LSN_AM_TCALL,														/**< Table vector / TCALL. */
		};

		/** Instructions. */
		enum LSN_INSTRUCTIONS : uint8_t {
#define LSN_INST( NAME, DESC )													LSN_I_ ## NAME,
#include "LSNSpc700Instructions.inl"
#undef LSN_INST

			LSN_I_TOTAL
		};


		// == Types.
		/** The processor registers. */
#pragma warning( push )
#pragma warning( disable : 4201 )	// warning C4201: nonstandard extension used: nameless struct/union
		struct LSN_REGISTERS {
			union {
				struct {
					uint8_t														ui8A;																			/**< A     Accumulator. */
					uint8_t														ui8Y;																			/**< Y     Index Register Y. */
				};
				uint16_t														ui16Ya;																			/**< YA    16-bit Index Register Y. */
			};
			uint8_t																ui8X;																			/**< X     Index Register X. */
			uint8_t																ui8Sp;																			/**< SP    Stack Pointer. */
			union {
				uint8_t															ui8Pc[2];																		/**< PC    Program Counter. */
				uint16_t														ui16Pc;																			/**< PC    Program Counter. */
			};
			uint8_t																ui8Status = 0;																	/**< The processor status register. */
		};
#pragma warning( pop )

		typedef void (CSpc700:: *												PfCycle)();																		/**< A function pointer for the functions that handle each cycle. */
		typedef void (CSpc700:: *												PfTicks)();																		/**< A function pointer for the tick handlers. */

		/** An instruction. The micro-functions (pfHandler) that make up each cycle of each instruction are programmed to know what to do and can correctly pass the cycles without
		 *	using ui8TotalCycles or amAddrMode. This means pcName, ui8TotalCycles, and amAddrMode are only used for debugging, verification, printing things, etc.
		 * Since we are adding work by increasing the number of functions calls per instruction, we get that time back by not checking for addressing modes or referencing any other
		 *	tables or data.  For the sake of performance, each micro-function just knows what to do and does so in the most efficient manner possible, free from any unnecessary
		 *	branching etc.
		 * pfHandler points to an array of functions that can handle all possible cycles for a given instruction, and we use a subtractive process for eliminating optional cycles
		 *	rather than using the additive approach most commonly found in emulators.
		 */
		struct LSN_INSTR {
			PfCycle																pfHandler[LSN_M_MAX_INSTR_CYCLE_COUNT*2];										/**< Indexed by LSN_CPU_CONTEXT::ui8FuncIdx, these functions handle each cycle of the instruction. */
			uint8_t																ui8TotalCycles;																	/**< Total non-optional non-overlapping cycles in the instruction. Used only for debugging, disassembling, etc. */
			LSN_ADDRESSING_MODES												amAddrMode;																		/**< Addressing mode. Used only for debugging, disassembling, etc. */
			uint8_t																ui8Size;																		/**< Size in bytes of the instruction (native). Used only for debugging, disassembling, etc. */
			LSN_INSTRUCTIONS													iInstruction;																	/**< The instruction. */
			const char *														pcName;																			/**< The name of the instruction. */
			const char *														pcTypeString;																	/**< The type string of the instruction. */
			const char *														pc65816Name;																	/**< The 65816-style name of the instruction. */
			const char *														pc65816TypeString;																/**< The 65816-style type string of the instruction. */
		};

		/** Cycle type (read, write, null. */
		enum LSN_CYCLE_TYPE {
			LSN_CT_NULL															= 0,																			/**< Neither read nor write. */
			LSN_CT_READ															= 1,																			/**< A read cycle. */
			LSN_CT_WRITE														= 2,																			/**< A write cycle. */
		};


	protected :
		// == Members.
		CBusB &																	m_bbBusB;																		/**< A reference to the bus. */
	};

}	// namespace lsn
