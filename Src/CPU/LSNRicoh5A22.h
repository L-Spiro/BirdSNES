/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A Ricoh 5A22 processor.
 */


#pragma once

#include "../LSNBirdSNES.h"
#include "../Bus/LSNBusA.h"
#include "LSNRicoh5A22Base.h"

#ifdef LSN_CPU_VERIFY
#include "LSONJson.h"
#endif	// #ifdef LSN_CPU_VERIFY

#define LSN_INSTR_START_PHI1( ISREAD )									/*m_fsState.bIsReadCycle = (ISREAD)*/
#define LSN_INSTR_END_PHI1
#define LSN_INSTR_START_PHI2_READ_BUSA( ADDR, BANK, RESULT, SPEED )		RESULT = m_baBusA.Read( uint16_t( ADDR ), uint8_t( BANK ), SPEED )
#define LSN_INSTR_START_PHI2_WRITE_BUSA( ADDR, BANK, VAL, SPEED )		m_baBusA.Write( uint16_t( ADDR ), uint8_t( BANK ), uint8_t( VAL ), SPEED )
#define LSN_INSTR_START_PHI2_READ0_BUSA( ADDR, RESULT, SPEED )			RESULT = m_baBusA.ReadBank0( uint16_t( ADDR ), SPEED )
#define LSN_INSTR_START_PHI2_WRITE0_BUSA( ADDR, VAL, SPEED )			m_baBusA.WriteBank0( uint16_t( ADDR ), uint8_t( VAL ), SPEED )
#define LSN_INSTR_END_PHI2

#define LSN_NEXT_FUNCTION_BY( AMT )										m_fsState.ui8FuncIndex += AMT
#define LSN_NEXT_FUNCTION												LSN_NEXT_FUNCTION_BY( 1 )
#define LSN_FINISH_INST( CHECK_INTERRUPTS )								/*if constexpr ( CHECK_INTERRUPTS ) { LSN_CHECK_INTERRUPTS; }*/ m_pfTickFunc = m_pfTickFuncCopy = &Ricoh5A22::Tick_NextInstructionStd

#define LSN_PUSH( VAL, SPEED )											LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.bEmulationMode ? (0x100 | m_fsState.rRegs.ui8S[0]) : m_fsState.rRegs.ui16S, (VAL), (SPEED) ); m_fsState.ui16SModify = -1
#define LSN_POP( RESULT, SPEED )										LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + 1 )) : (m_rRegs.ui16S + 1), (RESULT), (SPEED) ); m_fsState.ui16SModify = 1

#define LSN_UPDATE_PC													if ( m_fsState.bAllowWritingToPc ) { m_fsState.rRegs.ui16Pc += m_fsState.ui16PcModify; } m_fsState.ui16PcModify = 0
#define LSN_UPDATE_S													m_fsState.rRegs.ui16S += m_fsState.ui16SModify; m_fsState.ui16SModify = 0

#define LSN_R															true
#define LSN_W															false

#define LSN_TO_A														true
#define LSN_TO_P														false
#define LSN_FROM_A														true
#define LSN_FROM_P														false


namespace lsn {

#pragma warning( push )
#pragma warning( disable : 4324 )	// warning C4324: 'lsn::Ricoh5A22::LSN_FULL_STATE': structure was padded due to alignment specifier

	/**
	 * Class Ricoh5A22
	 * \brief A Ricoh 5A22 processor.
	 *
	 * Description: A Ricoh 5A22 processor.
	 */
	class Ricoh5A22 : public Ricoh5A22Base {
		typedef Ricoh5A22Base											Parent;
	public :
		// == Various constructors.
		Ricoh5A22( BusA &_bBusA );
		~Ricoh5A22();


		// == Enumerations.
		/** Status flags. */
		static constexpr uint8_t										C() { return (1 << 0); }														/**< Carry         (0=No Carry, 1=Carry). */
		static constexpr uint8_t										Z() { return (1 << 1); }														/**< Zero          (0=Nonzero, 1=Zero). */
		static constexpr uint8_t										I() { return (1 << 2); }														/**< IRQ Disable   (0=IRQ Enable, 1=IRQ Disable). */
		static constexpr uint8_t										D() { return (1 << 3); }														/**< Decimal Mode  (0=Normal, 1=BCD Mode for ADC/SBC opcodes). */
		static constexpr uint8_t										X() { return (1 << 4); }														/**< Break Flag    (0=IRQ/NMI, 1=BRK/PHP opcode)  (0=16bit, 1=8bit). */
		static constexpr uint8_t										M() { return (1 << 5); }														/**< Unused        (Always 1)                     (0=16bit, 1=8bit). */
		static constexpr uint8_t										V() { return (1 << 6); }														/**< Overflow      (0=No Overflow, 1=Overflow). */
		static constexpr uint8_t										N() { return (1 << 7); }														/**< Negative/Sign (0=Positive, 1=Negative). */

		/** Special addresses. */
		enum LSN_VECTORS : uint16_t {
			LSN_V_RESERVED2_E											= 0xFFF0,																		/**< Reserved. */
			LSN_V_RESERVED1_E											= 0xFFF2,																		/**< Reserved. */
			LSN_V_COP_E													= 0xFFF4,																		/**< The address of execution during a COP Software interrupt. */
			LSN_V_RESERVED0_E											= 0xFFF6,																		/**< Reserved. */
			LSN_V_ABORT_E												= 0xFFF8,																		/**< The address of execution during an abort interrupt. */
			LSN_V_NMI_E													= 0xFFFA,																		/**< The address of execution during an NMI interrupt. */
			LSN_V_RESET_E												= 0xFFFC,																		/**< The address of execution during a reset. */
			LSN_V_IRQ_BRK_E												= 0xFFFE,																		/**< The address of execution during an IRQ or BRK interrupt. */

			LSN_V_IRQ													= 0xFFEE,																		/**< The address of execution during an IRQ interrupt. */
			LSN_V_RESERVED0												= 0xFFEC,																		/**< Reserved. */
			LSN_V_NMI													= 0xFFEA,																		/**< The address of execution during an NMI interrupt. */
			LSN_V_ABORT													= 0xFFE8,																		/**< The address of execution during an abort interrupt. */
			LSN_V_BRK													= 0xFFE6,																		/**< The address of execution during an BRK interrupt. */
			LSN_V_COP													= 0xFFE4,																		/**< The address of execution during a COP Software interrupt. */
			LSN_V_RESERVED1												= 0xFFE2,																		/**< Reserved. */
			LSN_V_RESERVED2												= 0xFFE0,																		/**< Reserved. */
		};


		// == Types.
		/** The processor registers. */
		struct LSN_REGISTERS {
			union {
				uint8_t													ui8A[2];																		/**< A     Accumulator. */
				uint16_t												ui16A;																			/**< A     Accumulator. */
			};
			union {
				uint8_t													ui8X[2];																		/**< X     Index Register X. */
				uint16_t												ui16X;																			/**< X     Index Register X. */
			};
			union {
				uint8_t													ui8Y[2];																		/**< Y     Index Register Y. */
				uint16_t												ui16Y;																			/**< Y     Index Register Y. */
			};
			union {
				uint8_t													ui8Pc[2];																		/**< PC    Program Counter. */
				uint16_t												ui16Pc;																			/**< PC    Program Counter. */
			};
			union {
				uint8_t													ui8S[2];																		/**< S     Stack Pointer. */
				uint16_t												ui16S;																			/**< S     Stack Pointer. */
			};
			uint8_t														ui8Status = 0;																	/**< The processor status register. */
			union {
				uint8_t													ui8D[2];																		/**< D     Zeropage Offset      ;expands 8bit  [nn]   to 16bit [00:nn+D]. */
				uint16_t												ui16D;																			/**< D     Zeropage Offset      ;expands 8bit  [nn]   to 16bit [00:nn+D]. */
			};
			uint8_t														ui8Db = 0;																		/**< DB    Data Bank            ;expands 16bit [nnnn] to 24bit [DB:nnnn]. */
			uint8_t														ui8Pb = 0;																		/**< PB    Program Counter Bank ;expands 16bit PC     to 24bit PB:PC. */
		};

		typedef void (Ricoh5A22:: *										PfCycle)();																		/**< A function pointer for the functions that handle each cycle. */
		typedef void (Ricoh5A22:: *										PfTicks)();																		/**< A function pointer for the tick handlers. */

		/** An instruction. The micro-functions (pfHandler) that make up each cycle of each instruction are programmed to know what to do and can correctly pass the cycles without
		 *	using ui8TotalCycles or amAddrMode. This means pcName, ui8TotalCycles, and amAddrMode are only used for debugging, verification, printing things, etc.
		 * Since we are adding work by increasing the number of functions calls per instruction, we get that time back by not checking for addressing modes or referencing any other
		 *	tables or data.  For the sake of performance, each micro-function just knows what to do and does so in the most efficient manner possible, free from any unnecessary
		 *	branching etc.
		 * pfHandler points to an array of functions that can handle all possible cycles for a given instruction, and we use a subtractive process for eliminating optional cycles
		 *	rather than using the additive approach most commonly found in emulators.
		 */
		struct LSN_INSTR {
			PfCycle														pfHandler[2][LSN_M_MAX_INSTR_CYCLE_COUNT*2];									/**< Indexed by LSN_CPU_CONTEXT::ui8FuncIdx, these functions handle each cycle of the instruction. */
			uint8_t														ui8TotalCyclesN;																/**< Total non-optional non-overlapping cycles in the instruction. Used only for debugging, disassembling, etc. */
			uint8_t														ui8TotalCyclesE;																/**< Total non-optional non-overlapping cycles in the instruction. Used only for debugging, disassembling, etc. */
			LSN_ADDRESSING_MODES										amAddrMode;																		/**< Addressing mode. Used only for debugging, disassembling, etc. */
			uint8_t														ui8SizeN;																		/**< Size in bytes of the instruction (native). Used only for debugging, disassembling, etc. */
			uint8_t														ui8SizeE;																		/**< Size in bytes of the instruction (emulation mode). Used only for debugging, disassembling, etc. */
			LSN_INSTRUCTIONS											iInstruction;																	/**< The instruction. */
		};


		// == Functions.
		/** Fetches the next opcode and begins the next instruction. */
		inline void														Tick_NextInstructionStd();

		/** Performs a cycle inside an instruction. */
		inline void														Tick_InstructionCycleStd();

		/**
		 * Resets the bus to a known state.
		 */
		void															ResetToKnown();

		/**
		 * Performs an "analog" reset, allowing previous data to remain.
		 */
		void															ResetAnalog();

#ifdef LSN_CPU_VERIFY
		/**
		 * Runs a test given a JSON's value representing the test to run.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \return Returns true if te test succeeds, false otherwise.
		 */
		bool															RunJsonTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest );
#endif	// #ifdef LSN_CPU_VERIFY

	protected :
		// == Types.
		/** The full state structure for instructions. */
		LSN_ALIGN_STRUCT( 64 )
		struct LSN_FULL_STATE {
			LSN_REGISTERS												rRegs;																				/**< Registers. */

			LSN_VECTORS													vBrkVector = LSN_V_BRK;																/**< The vector to use inside BRK and whether to push B with status. */
			union {
				uint8_t													ui8Operand[2];																		/**< The operand. */
				uint16_t												ui16Operand;																		/**< The operand. */
			};
			union {
				uint8_t													ui8Address[2];																		/**< An address loaded into memory before transfer to a register such as PC. */
				uint16_t												ui16Address;																		/**< An address loaded into memory before transfer to a register such as PC. */
			};
			union {
				uint8_t													ui8Pointer[2];																		/**< An address loaded into memory for indirect access. */
				uint16_t												ui16Pointer;																		/**< An address loaded into memory for indirect access. */
			};
			uint16_t													ui16OpCode = 0;																		/**< The current opcode. */
			uint16_t													ui16PcModify = 0;																	/**< The amount by which to modify PC during the next Phi1. */
			uint16_t													ui16SModify = 0;																	/**< The amount by which to modify S during the next Phi1. */
			uint8_t														ui8FuncIndex = 0;																	/**< The function index. */
			uint8_t														ui8Bank = 0;																		/**< Holds the bank for long reads/writes. */
		
			bool														bIsReadCycle = true;																/**< Is the current cycle a read? */
			bool														bBoundaryCrossed = false;															/**< Did we cross a page boundary? */
			bool														bPushB = false;																		/**< Push the B flag with the status byte? */
			bool														bAllowWritingToPc = true;															/**< Allow writing to PC? */
			bool														bTakeJump;																			/**< Determines if a branch is taken. */
		
			bool														bEmulationMode = true;																/**< Emulation Mode flag. */
		} LSN_ALIGN_STRUCT_END( 64 );


		// == Members.
		PfTicks															m_pfTickFunc = nullptr;																/**< The current tick function (called by Tick()). */
		PfTicks															m_pfTickFuncCopy = nullptr;															/**< A copy of the current tick, used to restore the intended original tick when control flow is changed by DMA transfers. */
		BusA &															m_baBusA;																			/**< Bus A. */
		
		LSN_FULL_STATE													m_fsState;																			/**< Everything a standard instruction-cycle function can modify.  Backed up at the start of the first DMA read cycle and restored at the end after the read address for that cycle has been calculated. */
		LSN_FULL_STATE													m_fsStateBackup;																	/**< The backup of the state for the cycle that first gets interrupted by DMA and is then executed at the end of DMA. */
		static LSN_INSTR												m_iInstructionSet[256];																/**< The instruction set. */


#ifdef LSN_CPU_VERIFY
		// == Types.
		struct LSN_CPU_VERIFY_RAM {
			uint32_t													ui32Addr;
			uint8_t														ui8Value;
		};

		struct LSN_CPU_VERIFY_STATE {
			LSN_REGISTERS												cvrRegisters;
			std::vector<LSN_CPU_VERIFY_RAM>								vRam;
			bool														bEmulationMode;
		};

		struct LSN_CPU_VERIFY_CYCLE {
			uint32_t													ui32Addr;
			uint8_t														ui8Value;
			std::string													sStatus;
			bool														bNoReadOrWrite;
		};

		struct LSN_CPU_VERIFY_OBJ {
			std::string													sName;
			LSN_CPU_VERIFY_STATE										cvsStart;
			LSN_CPU_VERIFY_STATE										cvsEnd;
			std::vector<LSN_CPU_VERIFY_CYCLE>							vCycles;
		};


		// == Functions.
		/**
		 * Given a JSON object and the value for the test to run, this loads the test and fills a LSN_CPU_VERIFY structure.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \param _cvoTest The test structure to fill out.
		 * \return Returns true if the JSON data was successfully extracted and the test created.
		 */
		bool															GetTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest, LSN_CPU_VERIFY_OBJ &_cvoTest );

		/**
		 * Fills out a LSN_CPU_VERIFY_STATE structure given a JSON "initial" or "final" member.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvState The bject member representing the state to load.
		 * \param _cvsState The state structure to fill.
		 * \return Returns true if the state was loaded.
		 */
		bool															LoadState( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvState, LSN_CPU_VERIFY_STATE &_cvsState );
#endif	// #ifdef LSN_CPU_VERIFY


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// CYCLES
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		/**
		 * Prepares to enter a new instruction.
		 */
		template <bool _bIncPc = false, bool _bAdjS = false, bool _bCheckStartOfFunction = true>
		inline void														BeginInst();
	};


	/**
	 * Prepares to enter a new instruction.
	 *
	 * \tparam _bIncPc If true, PC is updatd.
	 * \tparam _bAdjS If true, S is updatd.
	 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
	 */
	template <bool _bIncPc, bool _bAdjS, bool _bCheckStartOfFunction>
	inline void Ricoh5A22::BeginInst() {
		if constexpr( _bCheckStartOfFunction ) {
			LSN_INSTR_START_PHI1( true );
		}

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;
		}

		if constexpr ( _bAdjS ) {
			LSN_UPDATE_S;
		}
		// Enter normal instruction context.
		m_fsState.ui8FuncIndex = 0;
		m_pfTickFunc = m_pfTickFuncCopy = &Ricoh5A22::Tick_InstructionCycleStd;
		m_fsState.bBoundaryCrossed = false;
		//m_ui8RdyOffCnt = 0;
		LSN_INSTR_END_PHI1;
	}

#pragma warning( pop )

}	// namespace lsn
