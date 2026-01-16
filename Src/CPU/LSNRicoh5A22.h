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
#include "../Foundation/LSNBits.h"
#include "../System/LSNTickable.h"
#include "LSNRicoh5A22Base.h"

#ifdef LSN_CPU_VERIFY
#include <LSONJson.h>
#endif	// #ifdef LSN_CPU_VERIFY

#define LSN_INSTR_START_PHI1( ISREAD )									/*m_fsState.bIsReadCycle = (ISREAD)*/
#define LSN_INSTR_END_PHI1
#define LSN_INSTR_START_PHI2_READ_BUSA( ADDR, BANK, RESULT, SPEED )		RESULT = m_baBusA.Read( uint16_t( ADDR ), uint8_t( BANK ), (SPEED) )
#define LSN_INSTR_START_PHI2_WRITE_BUSA( ADDR, BANK, VAL, SPEED )		m_baBusA.Write( uint16_t( ADDR ), uint8_t( BANK ), uint8_t( VAL ), (SPEED) )
#define LSN_INSTR_START_PHI2_READ0_BUSA( ADDR, RESULT, SPEED )			RESULT = m_baBusA.ReadBank0( uint16_t( ADDR ), (SPEED) )
#define LSN_INSTR_START_PHI2_WRITE0_BUSA( ADDR, VAL, SPEED )			m_baBusA.WriteBank0( uint16_t( ADDR ), uint8_t( VAL ), (SPEED) )
#define LSN_INSTR_END_PHI2

#define LSN_NEXT_FUNCTION_BY( AMT )										m_fsState.ui8FuncIndex += AMT
#define LSN_NEXT_FUNCTION												LSN_NEXT_FUNCTION_BY( 1 )
#define LSN_FINISH_INST( CHECK_INTERRUPTS )								if constexpr ( CHECK_INTERRUPTS ) { LSN_CHECK_INTERRUPTS; } LSN_NEXT_FUNCTION

#define LSN_CHECK_INTERRUPTS											if ( !(m_fsState.rRegs.ui8Status & I()) ) { m_bHandleIrq = m_bIrqStatusPhi1Flag; } m_bHandleNmi |= m_bDetectedNmi

#define LSN_PUSH( VAL, SPEED )											LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), (VAL), (SPEED) ); m_fsState.ui16SModify = uint16_t( -1 + _i8SOff )
#define LSN_POP( RESULT, SPEED )										LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), (RESULT), (SPEED) ); m_fsState.ui16SModify = uint16_t( 1 + _i8SOff )

#define LSN_PUSH_SPECIAL( VAL, SPEED )									LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.bEmulationMode ? ((0x100 | m_fsState.rRegs.ui8S[0]) + _i8SOff) : (m_fsState.rRegs.ui16S + _i8SOff), (VAL), (SPEED) ); m_fsState.ui16SModify = uint16_t( -1 + _i8SOff )
#define LSN_POP_SPECIAL( RESULT, SPEED )								LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? ((0x100 | m_fsState.rRegs.ui8S[0]) + _i8SOff) : (m_fsState.rRegs.ui16S + _i8SOff), (RESULT), (SPEED) ); m_fsState.ui16SModify = uint16_t( 1 + _i8SOff )

#define LSN_UPDATE_PC													if LSN_LIKELY( m_fsState.bAllowWritingToPc ) { m_fsState.rRegs.ui16Pc += m_fsState.ui16PcModify; } m_fsState.ui16PcModify = 0
#define LSN_UPDATE_S													m_fsState.rRegs.ui16S += m_fsState.ui16SModify; m_fsState.ui16SModify = 0

#define LSN_R															CRicoh5A22::LSN_CT_READ
#define LSN_W															CRicoh5A22::LSN_CT_WRITE
#define LSN_N															CRicoh5A22::LSN_CT_NULL

#define LSN_TO_A														true
#define LSN_TO_P														false
#define LSN_FROM_A														true
#define LSN_FROM_P														false

#ifdef LSN_CPU_VERIFY
#define LSN_CYCLES_DOC													1
#endif	// #ifdef LSN_CPU_VERIFY


namespace lsn {

#pragma warning( push )
#pragma warning( disable : 4324 )	// warning C4324: 'lsn::CRicoh5A22::LSN_FULL_STATE': structure was padded due to alignment specifier

	/**
	 * Class CRicoh5A22
	 * \brief A Ricoh 5A22 processor.
	 *
	 * Description: A Ricoh 5A22 processor.
	 */
	class CRicoh5A22 : public CRicoh5A22Base, CTickable {
		typedef CRicoh5A22Base											Parent;
	public :
		// == Various constructors.
		CRicoh5A22( CBusA &_bBusA );
		~CRicoh5A22();


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

		/** Cycle type (read, write, null. */
		enum LSN_CYCLE_TYPE {
			LSN_CT_NULL													= 0,																			/**< Neither read nor write. */
			LSN_CT_READ													= 1,																			/**< A read cycle. */
			LSN_CT_WRITE												= 2,																			/**< A write cycle. */
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

		typedef void (CRicoh5A22:: *									PfCycle)();																		/**< A function pointer for the functions that handle each cycle. */
		typedef void (CRicoh5A22:: *									PfTicks)();																		/**< A function pointer for the tick handlers. */

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
			const char *												pcName;																			/**< The name of the instruction. */
			const char *												pcTypeString;																	/**< The type string of the instruction. */
		};


		// == Functions.
		/**
		 * Resets the CPU to a known state.
		 * 
		 * \tparam _bToKnown If true, the CPU is reset to a known state..
		 */
		template <bool _bToKnown = true>
		void															Reset() {
			m_pfTickFunc = m_pfTickFuncCopy = &CRicoh5A22::Tick_NextInstructionStd;
			m_fsState.bBoundaryCrossed = false;
			m_fsState.ui16PcModify = 0;
			m_fsState.ui16SModify = 0;
			m_fsState.ui16OpCode = 0;
			m_fsState.bEmulationMode = true;
			m_fsStateBackup.bCopiedState = false;
			
#ifdef LSN_CPU_VERIFY
			m_fsState.bAllowWritingToPc = true;
			m_bIsReset = m_bBrkIsReset = false;
#else
			m_fsState.bAllowWritingToPc = false;
			m_bIsReset = m_bBrkIsReset = true;
#endif	// #ifdef LSN_CPU_VERIFY

			m_fsState.pfCurInstruction = m_iInstructionSet[m_fsState.ui16OpCode].pfHandler[m_fsState.bEmulationMode];

			//if ( m_pmbMapper ) { m_pmbMapper->Reset(); }

			if constexpr ( _bToKnown ) {
				std::memset( &m_fsState.rRegs, 0, sizeof( m_fsState.rRegs ) );
				m_ui64CycleCount = 0ULL;
				
				m_fsState.ui16Operand = 0;

				//m_ui16DmaCounter = 0;
				//m_ui16DmaAddress = 0;

				//m_ui8DmaPos = m_ui8DmaValue = 0;
				m_bNmiStatusLine = false;
				m_bLastNmiStatusLine = false;
				m_bDetectedNmi = false;
				m_bHandleNmi = false;
				m_ui8IrqStatusLine = 0;
				m_bIrqSeenLowPhi2 = false;
				m_bIrqStatusPhi1Flag = false;
				m_bHandleIrq = false;
				m_bRdyLow = false;
				//m_ui8RdyOffCnt = 0;

				/*std::memset( m_ui8Inputs, 0, sizeof( m_ui8Inputs ) );
				std::memset( m_ui8InputsState, 0, sizeof( m_ui8InputsState ) );
				std::memset( m_ui8InputsPoll, 0, sizeof( m_ui8InputsPoll ) );*/
			}
		}

		/**
		 * Sets m_bIsReset to true.
		 **/
		void															SetIsReset() {
			m_bIsReset = m_bBrkIsReset = true;
		}

		/**
		 * Performs a single PHI1 update.
		 */
		void															Tick();

		/**
		 * Performs a single PHI2 update.
		 **/
		void															TickPhi2();

		/** Fetches the next opcode and begins the next instruction. */
		inline void														Tick_NextInstructionStd();

		/** Performs a cycle inside an instruction. */
		inline void														Tick_InstructionCycleStd();

#ifdef LSN_CPU_VERIFY
		/**
		 * Runs a test given a JSON's value representing the test to run.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \return Returns -1 on error, the number of cycles otherwise.
		 */
		int32_t															RunJsonTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest );

		/**
		 * Gets the instruction table.
		 * 
		 * \return Returns a constant pointer to the instruction table (256 entries).
		 **/
		static inline const LSN_INSTR *									InstrTable() { return m_iInstructionSet; }
#endif	// #ifdef LSN_CPU_VERIFY

	protected :
		// == Types.
		/** The full state structure for instructions. */
		LSN_ALIGN_STRUCT( 64 )
		struct LSN_FULL_STATE {
			const PfCycle *												pfCurInstruction = nullptr;															/**< The current instruction being executed. */
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

			bool														bCopiedState = false;																/**< If m_bRdyLow triggers a state copy, this is set in PHI1 after the copy and used in PHI2 to know that a copy was made and to abord PHI2 as soon as the read address has been finalized. */
		} LSN_ALIGN_STRUCT_END( 64 );


		// == Members.
		PfTicks															m_pfTickFunc = nullptr;																/**< The current tick function (called by Tick()). */
		PfTicks															m_pfTickFuncCopy = nullptr;															/**< A copy of the current tick, used to restore the intended original tick when control flow is changed by DMA transfers. */
		CBusA &															m_baBusA;																			/**< Bus A. */
		
		LSN_FULL_STATE													m_fsState;																			/**< Everything a standard instruction-cycle function can modify.  Backed up at the start of the first DMA read cycle and restored at the end after the read address for that cycle has been calculated. */
		LSN_FULL_STATE													m_fsStateBackup;																	/**< The backup of the state for the cycle that first gets interrupted by DMA and is then executed at the end of DMA. */
		static LSN_INSTR												m_iInstructionSet[256];																/**< The instruction set. */

		uint8_t															m_ui8IrqStatusLine = 0;																/**< The status line for IRQ. */
		bool															m_bIrqSeenLowPhi2 = false;															/**< Set if m_bIrqStatusLine is low on PHI2. */
		bool															m_bIrqStatusPhi1Flag = false;														/**< Set on Phi1 if m_bIrqSeenLowPhi2 was set. */
		bool															m_bNmiStatusLine = false;															/**< The status line for NMI. */
		bool															m_bLastNmiStatusLine = false;														/**< THe last status line for NMI. */
		bool															m_bDetectedNmi = false;																/**< The edge detector for the PHI2 part of the cycle. */
		bool															m_bHandleNmi = false;																/**< Once an NMI edge is detected, this is set to indicate that it needs to be handled on the PHI1 of the next cycle. */
		bool															m_bHandleIrq = false;																/**< Once the IRQ status line is detected as having triggered, this tells us to handle an IRQ on the next instruction. */
		bool															m_bIsReset = true;																	/**< Are we resetting? */
		bool															m_bBrkIsReset = true;																/**< Shadows m_bIsReset, but m_bIsReset gets unset in the middle of BRK, while this lasts the whole BRK. */

		bool															m_bRdyLow = false;																	/**< When RDY is pulled low, reads inside opcodes abort the CPU cycle. */


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
		 * Adds D and operand, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 */
		template <bool _bTo = LSN_TO_A, bool _bIncPc = false>
		void															Add_D_And_Operand_To_AddrOrPtr_IncPc();

		/**
		 * Adds S to m_fsState.ui16Pointer or m_fsState.ui16Address, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 */
		template <bool _bTo = LSN_TO_A>
		void															Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc();

		/**
		 * Adds X to m_fsState.ui16Pointer and D, stores to m_fsState.ui16Address.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 **/
		template <bool _bTo = LSN_TO_A>
		void															Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc();

		/**
		 * Performs Performs m_fsState.ui16Operand <<= 1.  Sets C, N, and V, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 **/
		template <bool _bIncPc = false>
		void															Asl();

		/**
		 * Performs Performs m_fsState.rRegs.ui8A[0] <<= 1 or m_fsState.rRegs.ui16A <<= 1.  Sets C, N, and V, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 **/
		template <bool _bIncPc = false>
		void															AslOnA();

		/** Final touches to BRK (copies m_fsState.ui16Address to m_fsState.rRegs.ui16Pc) and first cycle of the next instruction. */
		void															Brk_BeginInst();

		/**
		 * Copies from the vector to PC.h.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bEndInstr = false>
		void															CopyVectorToPc_H_Phi2();
			
		/** Copies from the vector to PC.l. **/
		void															CopyVectorToPc_L_Phi2();

		/** Fetches the current opcode and increments PC. **/
		void															Fetch_Opcode_IncPc_Phi2();

		/**
		 * Fetches m_fsState.ui8Operand[1] and increments the PC.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bEndInstr = false>
		void															Fetch_Operand_High_IncPc();

		/**
		 * Fetches the next operand and discards without incrementing PC.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bEndInstr = false>
		void															Fetch_Operand_Discard_Phi2();

		/**
		 * Fetches the next operand and increments the PC.
		 * 
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bSkipIfM = false, bool _bEndInstr = false>
		void															Fetch_Operand_IncPc_SkipIfM_Phi2();

		/**
		 * Fetches the operand and increments PC.
		 * 
		 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
		 **/
		template <bool _bSkipOnDl = false>
		void															Fetch_Operand_IncPc_SkipOnDl_Phi2();

		/**
		 * Fetches to m_fsState.ui8Address[1] or m_fsState.ui8Pointer[1] and increments PC.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		void															Fetch_PtrOrAddr_High_IncPc_Phi2();

		/**
		 * Fetches to m_fsState.ui16Address or m_fsState.ui16Pointer and increments PC.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		void															Fetch_PtrOrAddr_Low_IncPc_Phi2();

		/**
		 * Fixes the high bit of m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 **/
		template <bool _bTo = LSN_TO_A>	
		void															Fix_PtrOrAddr_From_AddrOrPtr_High();

		/**
		 * Generic null operation.
		 * 
		 * \tparam _ctReadWriteNull The cycle read/write/neither type.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bBeginInstr If true, BeginInst() is called.
		 **/
		template <CRicoh5A22::LSN_CYCLE_TYPE _ctReadWriteNull = CRicoh5A22::LSN_CT_NULL, bool _bIncPc = false, bool _bAdjS = false, bool _bBeginInstr = false>
		void															Null();

		/**
		 * Generic null operation on PHI2.  Sets the bus access speed to Fast.
		 * 
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 **/
		 template <bool _bSkipIfM = false>
		void															Null_Phi2();

		/**
		 * Generic null operation for BRK that can be either a read or write, depending on RESET.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bBeginInstr If true, BeginInst() is called.
		 **/
		template <bool _bIncPc = false, bool _bAdjS = false, bool _bBeginInstr = false>
		void															Null_RorW();

		/**
		 * Performs ORA with m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 **/
		template <bool _bIncPc = false>
		void															Ora();

		/** Sets m_fsState.ui8Operand[0] to the status byte with Break (X) and Reserved (M) set. */
		void															Php();

		/**
		 * Pushes m_fsState.rRegs.ui8D[1].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 **/
		template <int8_t _i8SOff = 0>
		void															Push_D_High_Phi2();

		/**
		 * Pushes m_fsState.rRegs.ui8D[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <int8_t _i8SOff = -1, bool _bEndInstr = true>
		void															Push_D_Low_Phi2();

		/**
		 * Pushes m_fsState.ui8Operand[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = true>
		void															Push_Operand_Low_Phi2();

		/**
		 * Pushes m_fsState.rRegs.ui8Pb.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 **/
		template <int8_t _i8SOff = 0>
		void															Push_Pb_Phi2();

		/**
		 * Pushes m_fsState.rRegs.ui8Pc[1] with the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 **/
		template <int8_t _i8SOff = 0>
		void															Push_Pc_High_Phi2();

		/**
		 * Pushes m_fsState.rRegs.ui8Pc[0] with the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 **/
		template <int8_t _i8SOff = 0>
		void															Push_Pc_Low_Phi2();

		/**
		 * Pushes m_fsState.rRegs.ui8Status with or without B/X to the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bCop If this is the COP instruction, just do a normal push.
		 **/
		template <int8_t _i8SOff = 0, bool _bCop = false>
		void															Push_S_Phi2();

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		void															Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2();

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = true, bool _bEndInstr = false>
		void															Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2();

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		void															Read_PtrOrAddr_And_DB_To_Operand_High_Phi2();

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = true, bool _bEndInstr = false>
		void															Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2();

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 **/
		template <bool _bTo = LSN_TO_A>
		void															ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2();

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Pointer[0] or m_fsState.ui8Address[0].
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false>
		void															ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2();

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 **/
		template <bool _bFrom = LSN_FROM_A>
		void															ReadBank0_PtrOrAddr_To_Bank_Phi2();

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 **/
		template <bool _bFrom = LSN_FROM_A>
		void															ReadBank0_PtrOrAddr_To_Bank_LowByteWrap_Phi2();

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		void															ReadBank0_PtrOrAddr_To_Operand_High_Phi2();

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = false, bool _bEndInstr = false>
		void															ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2();

		/**
		 * Selects the BRK vector etc.
		 * 
		 * \tparam _bAdjS If true, S is updated.
		 **/
		template <bool _bAdjS>
		void															SelectBrkVectors();

		/**
		 * Selects the COP vector etc.
		 * 
		 * \tparam _bAdjS If true, S is updated.
		 **/
		template <bool _bAdjS>
		void															SelectCopVectors();

		/** Sets I and X. */
		void															SetBrkFlags();

		/** Skips the next instruction if the M status flag is set. */
		void															SkipIfM_Phi2();

		/** Skips the next instruction if the low byte of D is 0. */
		void															SkipOnDL_Phi2();

		/** Transfer 16 bit A to S.  Sets N and Z. */
		void															Tcs();

		/** Performs m_ui16Operand &= ~A.  Sets Z. */
		void															Trb();

		/** Performs m_ui16Operand |= A.  Sets Z. */
		void															Tsb();

		/**
		 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		void															Write_Operand_High_To_AddrOrPtr_Phi2();

		/**
		 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 **/
		template <bool _bTo = LSN_TO_A>
		void															Write_Operand_High_To_AddrOrPtr_And_DB_Phi2();

		/**
		 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false>
		void															Write_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2();

		/**
		 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
		 * 
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false>
		void															Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_Phi2();


		/**
		 * Prepares to enter a new instruction.
		 *
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
		 */
		template <bool _bIncPc = false, bool _bAdjS = false, bool _bCheckStartOfFunction = true>
		inline void														BeginInst();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Fuctions.
	/** Fetches the next opcode and begins the next instruction. */
	inline void CRicoh5A22::Tick_NextInstructionStd() {
		BeginInst();
	}

	/** Performs a cycle inside an instruction. */
	inline void CRicoh5A22::Tick_InstructionCycleStd() {
		//(this->*m_iInstructionSet[m_fsState.ui16OpCode].pfHandler[m_fsState.bEmulationMode][m_fsState.ui8FuncIndex])();
		(this->*m_fsState.pfCurInstruction[m_fsState.ui8FuncIndex])();
	}

	/**
	 * Adds D and operand, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 */
	template <bool _bTo, bool _bIncPc>
	void CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc() {
		LSN_INSTR_START_PHI1( true );

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tInc. PC if previous cycle was skipped. " );
#endif	// LSN_CYCLES_DOC
		}
		else {
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bTo == LSN_TO_A ) {
			m_fsState.ui16Address = m_fsState.ui16Operand + m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Set Address to Operand + D." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			m_fsState.ui16Pointer = m_fsState.ui16Operand + m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Set Pointer to Operand + D." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds S to m_fsState.ui16Pointer or m_fsState.ui16Address, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 */
	template <bool _bTo>
	void CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc() {
		LSN_INSTR_START_PHI1( false );

		LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		std::string sTmp = "\tInc. PC. ";
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bTo == LSN_TO_A ) {
			if ( m_fsState.bEmulationMode ) {
				m_fsState.ui16Address = m_fsState.ui16Pointer + (m_fsState.rRegs.ui8S[0] | 0x100);
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Address to Pointer + S.L + $100. ";
#endif	// LSN_CYCLES_DOC
			}
			else {
				m_fsState.ui16Address = m_fsState.ui16Pointer + m_fsState.rRegs.ui16S;
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Address to Pointer + S. ";
#endif	// LSN_CYCLES_DOC
			}
		}
		else {
			if ( m_fsState.bEmulationMode ) {
				m_fsState.ui16Pointer = m_fsState.ui16Address + (m_fsState.rRegs.ui8S[0] | 0x100);
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Pointer to Address + S.L + $100. ";
#endif	// LSN_CYCLES_DOC
			}
			else {
				m_fsState.ui16Pointer = m_fsState.ui16Address + m_fsState.rRegs.ui16S;
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Pointer to Address + S. ";
#endif	// LSN_CYCLES_DOC
			}
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sTmp.c_str() );
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds X to m_fsState.ui16Pointer and D, stores to m_fsState.ui16Address.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 **/
	template <bool _bTo>	
	void CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc() {
		LSN_INSTR_START_PHI1( false );

		LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		std::string sTmp = "\tInc. PC. ";
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bTo == LSN_TO_A ) {
			m_fsState.ui16Pointer = m_fsState.ui16Pointer + m_fsState.rRegs.ui16X + m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			sTmp += "Set Pointer to Pointer + X + D. ";
#endif	// LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				m_fsState.ui8Address[0] = m_fsState.ui8Pointer[0];
				m_fsState.ui8Address[1] = uint8_t( m_fsState.rRegs.ui8D[1] );
#ifdef LSN_CYCLES_DOC
				sTmp += "Address.L = Pointer.L.  Address.H = D.H. ";
#endif	// LSN_CYCLES_DOC
			}
			else {
				m_fsState.ui16Address = m_fsState.ui16Pointer;
#ifdef LSN_CYCLES_DOC
				sTmp += "Address = Pointer. ";
#endif	// LSN_CYCLES_DOC
			}
		}
		else {
			m_fsState.ui16Address = m_fsState.ui16Address + m_fsState.rRegs.ui16X + m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			sTmp += "Set Address to Address + X + D. ";
#endif	// LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				m_fsState.ui8Pointer[0] = m_fsState.ui8Address[0];
				m_fsState.ui8Pointer[1] = uint8_t( m_fsState.rRegs.ui8D[1] );
#ifdef LSN_CYCLES_DOC
				sTmp += "Pointer.L = Address.L.  Pointer.H = D.H. ";
#endif	// LSN_CYCLES_DOC
			}
			else {
				m_fsState.ui16Pointer = m_fsState.ui16Address;
#ifdef LSN_CYCLES_DOC
				sTmp += "Pointer = Address. ";
#endif	// LSN_CYCLES_DOC
			}
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sTmp.c_str() );
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs Performs m_fsState.ui16Operand <<= 1.  Sets C, N, and V, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Asl() {
		LSN_INSTR_START_PHI1( false );

		if ( (m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( m_fsState.rRegs.ui8Status, (m_fsState.ui8Operand[0] & 0x80) != 0 );

			m_fsState.ui16Operand <<= 1;

			SetBit<N()>( m_fsState.rRegs.ui8Status, (m_fsState.ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.ui8Operand[0] );
		}
		else {
			SetBit<C()>( m_fsState.rRegs.ui8Status, (m_fsState.ui8Operand[1] & 0x80) != 0 );

			m_fsState.ui16Operand <<= 1;

			SetBit<N()>( m_fsState.rRegs.ui8Status, (m_fsState.ui8Operand[1] & 0x80) != 0 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				lsn::DebugA( "\tSet C based off (Operand.L & $80). Perform Operand.L <<= 1. Set N based off (Operand.L & $80) and Z based off Operand.L." );
			}
			else {
				lsn::DebugA( "\tIf M flag is set, set C based off (Operand.L & $80), perform Operand.L <<= 1, and set N based off (Operand.L & $80) and Z based off Operand.L, otherwise set C based off (Operand.H & $80), perform Operand <<= 1, and set N based off (Operand.H & $80) and Z based off Operand." );
			}
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " Inc. PC." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs Performs m_fsState.rRegs.ui8A[0] <<= 1 or m_fsState.rRegs.ui16A <<= 1.  Sets C, N, and V, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 **/
	template <bool _bIncPc>
	void CRicoh5A22::AslOnA() {
		LSN_INSTR_START_PHI1( false );

		if ( (m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui8A[0] & 0x80) != 0 );

			m_fsState.rRegs.ui8A[0] <<= 1;

			SetBit<N()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<C()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui8A[1] & 0x80) != 0 );

			m_fsState.rRegs.ui16A <<= 1;

			SetBit<N()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui8A[1] & 0x80) != 0 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				lsn::DebugA( "\tSet C based off (A.L & $80). Perform A.L <<= 1. Set N based off (A.L & $80) and Z based off A.L." );
			}
			else {
				lsn::DebugA( "\tIf M flag is set, set C based off (A.L & $80), perform A.L <<= 1, and set N based off (A.L & $80) and Z based off A.L, otherwise set C based off (A.H & $80), perform A <<= 1, and set N based off (A.H & $80) and Z based off A." );
			}
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " Inc. PC." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/** Final touches to BRK (copies m_fsState.ui16Address to m_fsState.rRegs.ui16Pc) and first cycle of the next instruction. */
	inline void CRicoh5A22::Brk_BeginInst() {
		LSN_INSTR_START_PHI1( true );
		
		m_bBrkIsReset = false;
		m_fsState.rRegs.ui16Pc = m_fsState.ui16Address;
		m_fsState.rRegs.ui8Pb = 0;
		m_fsState.bAllowWritingToPc = true;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tEnable writes to PC (disabled by NMI/IRQ).  Copy Address to PC.  Set PB to 0." );
#endif	// LSN_CYCLES_DOC

		BeginInst<false, false, false>();
	}

	/**
	 * Copies from the vector to PC.h.
	 * 
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::CopyVectorToPc_H_Phi2() {
		LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.vBrkVector + 1, m_fsState.ui8Address[1], m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read Vector + 1\tStore to Address.H." );
#endif // #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}
			
	/** Copies from the vector to PC.l. **/
	inline void CRicoh5A22::CopyVectorToPc_L_Phi2() {
		LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.vBrkVector, m_fsState.ui8Address[0], m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read Vector\tStore to Address.L." );
#endif // #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/** Fetches the current opcode and increments PC. **/
	inline void CRicoh5A22::Fetch_Opcode_IncPc_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, ui8Op, ui8Speed );
		m_ui8Speed = ui8Speed;

#ifdef LSN_CPU_VERIFY
		m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Store as OpCode." );
#endif	// LSN_CYCLES_DOC
#else
		if ( m_bHandleNmi || m_bHandleIrq || m_bIsReset ) {
			ui8Op = 0;
			m_fsState.bPushB = false;
			m_fsState.ui16PcModify = 0;
			m_fsState.bAllowWritingToPc = false;
		}
		else {
			m_fsState.bPushB = true;
			m_fsState.ui16PcModify = 1;
		}
#endif	// #ifdef LSN_CPU_VERIFY
		m_fsState.ui16OpCode = ui8Op;
		m_fsState.pfCurInstruction = m_iInstructionSet[m_fsState.ui16OpCode].pfHandler[m_fsState.bEmulationMode];

#if 0
		char szBUffer[256];
		std::sprintf( szBUffer, "%s\t%.2X %lu %.4X", m_smdInstMetaData[m_iInstructionSet[m_fsState.ui16OpCode].iInstruction].pcName, m_fsState.ui16OpCode, m_ui64CycleCount, m_fsState.rRegs.ui16Pc );
		::OutputDebugStringA( szBUffer );
		if ( 0xB6FE == m_fsState.rRegs.ui16Pc ) {
			volatile int gjhgh =0;
		}
#endif	// #if 1}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches m_fsState.ui8Operand[1] and increments the PC.
	 * 
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Operand_High_IncPc() {
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, m_fsState.ui8Operand[1], m_ui8Speed );
		m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the next operand and discards without incrementing PC.
	 * 
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Operand_Discard_Phi2() {
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, m_fsState.ui8Operand[0], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tDiscard." );
#endif	// LSN_CYCLES_DOC
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the next operand and increments the PC.
	 * 
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2() {
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, m_fsState.ui16Operand, m_ui8Speed );
		m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Operand." );
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series.  Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If M flag is set, skip the next cycle." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			if constexpr ( _bEndInstr ) {
				LSN_FINISH_INST( true );
			}
			else {
				LSN_NEXT_FUNCTION;
			}
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the operand and increments PC.
	 * 
	 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
	 **/
	template <bool _bSkipOnDl>
	inline void CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2() {
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, m_fsState.ui16Operand, m_ui8Speed );
		m_fsState.ui16PcModify = 1;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Operand." );
#endif	// LSN_CYCLES_DOC


		if constexpr ( _bSkipOnDl ) {
			if ( !(m_fsState.rRegs.ui16D & 0xFF) ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If D.L is not 0, skip the next cycle." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches to m_fsState.ui8Address[1] or m_fsState.ui8Pointer[1] and increments PC.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bTo, bool _bEndInstr>
	void CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2() {
		uint8_t ui8Op;
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, ui8Op, m_ui8Speed );
		if constexpr ( _bTo == LSN_TO_A ) {
			m_fsState.ui8Address[1] = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB\tStore as Address.L." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			m_fsState.ui8Pointer[1] = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB.\tStore as Pointer.H." );
#endif	// LSN_CYCLES_DOC
		}
		m_fsState.ui16PcModify = 1;

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the operand and increments PC.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bTo, bool _bEndInstr>
	void CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2() {
		uint8_t ui8Op;
		LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pb, ui8Op, m_ui8Speed );
		if constexpr ( _bTo == LSN_TO_A ) {
			m_fsState.ui16Address = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB\tStore as Address." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			m_fsState.ui16Pointer = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB.\tStore as Pointer." );
#endif	// LSN_CYCLES_DOC
		}
		m_fsState.ui16PcModify = 1;

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fixes the high bit of m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 **/
	template <bool _bTo>	
	inline void CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High() {
		LSN_INSTR_START_PHI1( false );
		if constexpr ( _bTo == LSN_TO_A ) {
			m_fsState.ui8Address[1] = m_fsState.ui8Pointer[1];
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tAddress.H = Pointer.H (fixes high byte of address)." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			m_fsState.ui8Pointer[1] = m_fsState.ui8Address[1];
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tPointer.H = Address.H (fixes high byte of address)." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Generic null operation.
	 * 
	 * \tparam _ctReadWriteNull The cycle read/write/neither type.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bBeginInstr If true, BeginInst() is called.
	 **/
	template <CRicoh5A22::LSN_CYCLE_TYPE _ctReadWriteNull, bool _bIncPc, bool _bAdjS, bool _bBeginInstr>
	inline void CRicoh5A22::Null() {
		if constexpr ( _bBeginInstr ) {
			BeginInst<_bIncPc, _bAdjS>();
		}
		else {
#ifdef LSN_CYCLES_DOC
			std::string sDebug = "\t";
#endif	// LSN_CYCLES_DOC
			LSN_INSTR_START_PHI1( _ctReadWriteNull );

			if constexpr ( _bIncPc ) {
#ifdef LSN_CYCLES_DOC
				sDebug += "Inc. PC. ";
#endif	// LSN_CYCLES_DOC
				LSN_UPDATE_PC;
			}
			if constexpr ( _bAdjS ) {
#ifdef LSN_CYCLES_DOC
				if ( int16_t( m_fsState.ui16SModify ) < 0 ) {
					sDebug += "Dec. S by " + std::to_string( -int16_t( m_fsState.ui16SModify ) ) + ". ";
				}
				else if ( int16_t( m_fsState.ui16SModify ) > 0 ) {
					sDebug += "Inc. S by " + std::to_string( int16_t( m_fsState.ui16SModify ) ) + ". ";
				}
#endif	// LSN_CYCLES_DOC
				LSN_UPDATE_S;
			}

			LSN_NEXT_FUNCTION;

			LSN_INSTR_END_PHI1;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC
		}
	}

	/**
	 * Generic null operation on PHI2.  Sets the bus access speed to Fast.
	 * 
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 **/
	template <bool _bSkipIfM>
	inline void CRicoh5A22::Null_Phi2() {
		m_ui8Speed = m_ui8FastDiv;
		
		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				/*if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}*/
			}
			//else {
			//	// If the next cycle is skippable, it can't be the last PHI2 in the series.  Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
			//	LSN_NEXT_FUNCTION;
			//}
			LSN_NEXT_FUNCTION;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tIf M flag is set, skip the next cycle." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Generic null operation for BRK that can be either a read or write, depending on RESET.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bBeginInstr If true, BeginInst() is called.
	 **/
	template <bool _bIncPc, bool _bAdjS, bool _bBeginInstr>
	inline void CRicoh5A22::Null_RorW() {
		if constexpr ( _bBeginInstr ) {
			BeginInst<_bIncPc, _bAdjS>();
		}
		else {
#ifdef LSN_CYCLES_DOC
			std::string sDebug = "\t";
#endif	// LSN_CYCLES_DOC
			if LSN_UNLIKELY( m_bIsReset ) {
				LSN_INSTR_START_PHI1( true );
			}
			else {
				LSN_INSTR_START_PHI1( false );
			}

			if constexpr ( _bIncPc ) {
				LSN_UPDATE_PC;
#ifdef LSN_CYCLES_DOC
				sDebug += "Inc. PC. ";
#endif	// LSN_CYCLES_DOC
			}
			if constexpr ( _bAdjS ) {
				LSN_UPDATE_S;
#ifdef LSN_CYCLES_DOC
				if ( m_fsState.ui16SModify < 0 ) {
					sDebug += "Dec. S by " + std::to_string( -m_fsState.ui16SModify ) + ". ";
				}
				else if ( m_fsState.ui16SModify > 0 ) {
					sDebug += "Inc. S by " + std::to_string( m_fsState.ui16SModify ) + ". ";
				}
#endif	// LSN_CYCLES_DOC
			}

			LSN_NEXT_FUNCTION;

			LSN_INSTR_END_PHI1;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC
		}
	}

	/**
	 * Performs ORA with m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Ora() {
		LSN_INSTR_START_PHI1( false );

		m_fsState.rRegs.ui16A |= m_fsState.ui16Operand;

		if ( (m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<N()>( m_fsState.rRegs.ui8Status, m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<N()>( m_fsState.rRegs.ui8Status, m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				lsn::DebugA( "\tPerform A |= Operand. Set N based off (A.L & $80) and Z based off A.L." );
			}
			else {
				lsn::DebugA( "\tPerform A |= Operand. If M flag is set, set N based off (A.L & $80) and Z based off A.L, otherwise set N based off (A.H & $80) and Z based off A." );
			}

			if constexpr ( _bIncPc ) {
				lsn::DebugA( " Inc. PC." );
			}
#endif	// LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>();
	}

	/** Sets m_fsState.ui8Operand[0] to the status byte with Break (X) and Reserved (M) set. */
	inline void CRicoh5A22::Php() {
		LSN_INSTR_START_PHI1( true );

		m_fsState.ui8Operand[0] = m_fsState.rRegs.ui8Status;
		if ( m_fsState.bEmulationMode ) {
			SetBit<X() | M(), true>( m_fsState.ui8Operand[0] );
		}

#ifdef LSN_CYCLES_DOC
		if ( !m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSets Operand.L to P." );
		}
		else {
			lsn::DebugA( "\tSets Operand.L to (P | X | M)." );
		}
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8D[1].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_D_High_Phi2() {
		LSN_PUSH( m_fsState.rRegs.ui8D[1], m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush D.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush D.H onto stack.").c_str() );
		}
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8D[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_D_Low_Phi2() {
		LSN_PUSH_SPECIAL( m_fsState.rRegs.ui8D[0], m_ui8Speed );

		// Needs to use
		//	((0x100 | m_fsState.rRegs.ui8S[0]) + _i8SOff)
		//	for the stack address??

#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( ("*** Write to ((S | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush D.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush D.L onto stack.").c_str() );
		}
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.ui8Operand[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_Operand_Low_Phi2() {
		LSN_PUSH( m_fsState.ui8Operand[0], m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush Operand.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush Operand.L onto stack.").c_str() );
		}
#endif	// LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pb.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_Pb_Phi2() {
		if LSN_UNLIKELY( m_bBrkIsReset ) {
			uint8_t ui8Tmp;
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, m_ui8Speed );
			m_fsState.ui16SModify = uint16_t( -1 + _i8SOff );
		}
		else {
			LSN_PUSH( m_fsState.rRegs.ui8Pb, m_ui8Speed );
		}
#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PB onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PB onto stack.").c_str() );
		}
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pc[1] with the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_Pc_High_Phi2() {
		if LSN_UNLIKELY( m_bBrkIsReset ) {
			uint8_t ui8Tmp;
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, m_ui8Speed );
			m_fsState.ui16SModify = uint16_t( -1 + _i8SOff );
		}
		else {
			LSN_PUSH( m_fsState.rRegs.ui8Pc[1], m_ui8Speed );
		}
#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PC.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
		}
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pc[0] with the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_Pc_Low_Phi2() {
		if LSN_UNLIKELY( m_bBrkIsReset ) {
			uint8_t ui8Tmp;
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, m_ui8Speed );
			m_fsState.ui16SModify = uint16_t( -1 + _i8SOff );
		}
		else {
			LSN_PUSH( m_fsState.rRegs.ui8Pc[0], m_ui8Speed );
		}
#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PC.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
		}
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Status with or without B/X to the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bCop If this is the COP instruction, just do a normal push.
	 **/
	template <int8_t _i8SOff, bool _bCop>
	inline void CRicoh5A22::Push_S_Phi2() {
		if constexpr( _bCop ) {
			LSN_PUSH( m_fsState.rRegs.ui8Status, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				lsn::DebugA( ("** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush P onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush P onto stack.").c_str() );
			}
#endif	// LSN_CYCLES_DOC
		}
		else {
			if LSN_UNLIKELY( m_bBrkIsReset ) {
				uint8_t ui8Tmp;
				LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.bEmulationMode ? (0x100 | uint8_t( m_fsState.rRegs.ui8S[0] + _i8SOff )) : (m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, m_ui8Speed );
				m_fsState.ui16SModify = uint16_t( -1L + _i8SOff );
			}
			else {
				if ( m_fsState.bPushB ) {
					LSN_PUSH( m_fsState.rRegs.ui8Status | X(), m_ui8Speed );
				}
				else {
					LSN_PUSH( m_fsState.rRegs.ui8Status, m_ui8Speed );
				}
			}
#ifdef LSN_CYCLES_DOC
			if ( m_fsState.bEmulationMode ) {
				lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush P onto stack with B flag if software BRK.").c_str() );
			}
			else {
				lsn::DebugA( ("*** Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush P onto stack with B flag if software BRK.").c_str() );
			}
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2() {
		if constexpr ( _bFrom == LSN_FROM_A ) {
			uint32_t ui32Offset = m_fsState.ui16Address + 1;
			LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, m_fsState.ui8Bank + (ui32Offset >> 16), m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "* Read Address + 1:Bank\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			uint32_t ui32Offset = m_fsState.ui16Pointer + 1;
			LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, m_fsState.ui8Bank + (ui32Offset >> 16), m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "* Read Pointer + 1:Bank\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2() {
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// LSN_CYCLES_DOC
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Address, m_fsState.ui8Bank, m_fsState.ui16Operand, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address:Bank\tStore as Operand.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Pointer, m_fsState.ui8Bank, m_fsState.ui16Operand, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer:Bank\tStore as Operand.";
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series.  Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			if constexpr ( _bEndInstr ) {
				LSN_FINISH_INST( true );
			}
			else {
				LSN_NEXT_FUNCTION;
			}
		}
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2() {
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Address + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Address + 1:DB\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Pointer + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Pointer + 1:DB\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2() {
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// LSN_CYCLES_DOC
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Address, m_fsState.rRegs.ui8Db, m_fsState.ui16Operand, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address:DB\tStore as Operand.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Pointer, m_fsState.rRegs.ui8Db, m_fsState.ui16Operand, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer:DB\tStore as Operand.";
#endif	// LSN_CYCLES_DOC
		}

		
		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series.  Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			if constexpr ( _bEndInstr ) {
				LSN_FINISH_INST( true );
			}
			else {
				LSN_NEXT_FUNCTION;
			}
		}
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 **/
	template <bool _bTo>	
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2() {
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// LSN_CYCLES_DOC
		if constexpr( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Pointer + 1, m_fsState.ui8Address[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer + 1\tStore as Address.H.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Address + 1, m_fsState.ui8Pointer[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address + 1\tStore as Pointer.H.";
#endif	// LSN_CYCLES_DOC
		}
		
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Pointer[0] or m_fsState.ui8Address[0].
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 **/
	template <bool _bTo, bool _bSkipIfM>	
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2() {
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// LSN_CYCLES_DOC
		if constexpr( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Pointer, m_fsState.ui16Address, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer\tStore as Address.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Address, m_fsState.ui16Pointer, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address\tStore as Pointer.";
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC
		
		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 **/
	template <bool _bFrom>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2() {
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Address + 2, m_fsState.ui8Bank, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Address + 2\tStore as Bank." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Pointer + 2, m_fsState.ui8Bank, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Pointer + 2\tStore as Bank." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 **/
	template <bool _bFrom>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_LowByteWrap_Phi2() {
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if ( !(m_fsState.rRegs.ui16D & 0xFF) ) {
				LSN_INSTR_START_PHI2_READ0_BUSA( uint8_t( m_fsState.ui8Address[0] + 2 ) | (m_fsState.ui8Address[1] << 8), m_fsState.ui8Bank, m_ui8Speed );
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Address + 2, m_fsState.ui8Bank, m_ui8Speed );
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If D.L is 0, Read (((Address.L + 2) & $FF) | (Address.H << 8)), otherwise read Address + 2\tStore as Bank." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			if ( !(m_fsState.rRegs.ui16D & 0xFF) ) {
				LSN_INSTR_START_PHI2_READ0_BUSA( uint8_t( m_fsState.ui8Pointer[0] + 2 ) | (m_fsState.ui8Pointer[1] << 8), m_fsState.ui8Bank, m_ui8Speed );
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Pointer + 2, m_fsState.ui8Bank, m_ui8Speed );
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If D.L is 0, Read (((Pointer.L + 2) & $FF) | (Pointer.H << 8)), otherwise read Pointer + 2\tStore as Bank." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2() {
		if constexpr( _bFrom == LSN_FROM_P ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Pointer + 1, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Pointer + 1\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Address + 1, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Address + 1\tStore as Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2() {
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr( _bFrom == LSN_FROM_P ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Pointer, m_fsState.ui16Operand, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer\tStore as Operand.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( m_fsState.ui16Address, m_fsState.ui16Operand, m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address\tStore as Operand.";
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// LSN_CYCLES_DOC
		}
		else {
			if constexpr ( _bEndInstr ) {
				LSN_FINISH_INST( true );
			}
			else {
				LSN_NEXT_FUNCTION;
			}
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sDebug.c_str() );
#endif	// LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Selects the BRK vector etc.
	 * 
	 * \tparam _bAdjS If true, S is updated.
	 **/
	template <bool _bAdjS>
	inline void CRicoh5A22::SelectBrkVectors() {
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
		std::string sDebug = "\t";
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bAdjS ) {
			LSN_UPDATE_S;
#ifdef LSN_CYCLES_DOC
			if ( m_fsState.ui16SModify < 0 ) {
				sDebug += "Dec. S by " + std::to_string( -m_fsState.ui16SModify ) + ". ";
			}
			else if ( m_fsState.ui16SModify > 0 ) {
				sDebug += "Inc. S by " + std::to_string( m_fsState.ui16SModify ) + ". ";
			}
#endif	// LSN_CYCLES_DOC
		}

#ifdef LSN_CPU_VERIFY
		m_fsState.vBrkVector = m_fsState.bEmulationMode ? LSN_V_IRQ_BRK_E : LSN_V_BRK;
		m_fsState.bPushB = m_fsState.bEmulationMode;

#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			sDebug += "Use Interrupt flags to decide which vector to use. RESET = $FFFC. NMI = $FFFA. IRQ/BRK = $FFFE.";
		}
		else {
			sDebug += "Use Interrupt flags to decide which vector to use. RESET = $FFFC. NMI = $FFEA. IRQ = $FFEE. BRK = $FFE6.";
		}
		lsn::DebugA( sDebug.c_str() );
#endif // #ifdef LSN_CYCLES_DOC
#else

		// Select vector to use.
		if ( m_bIsReset ) {
			m_fsState.vBrkVector = m_fsState.bEmulationMode ? LSN_V_RESET_E : LSN_V_RESET_E;
			m_bIsReset = false;
		}
		else if ( m_bDetectedNmi ) {
			m_fsState.vBrkVector = m_fsState.bEmulationMode ? LSN_V_NMI_E : LSN_V_NMI;
		}
		else if ( m_bHandleIrq ) {
			m_fsState.vBrkVector = m_fsState.bEmulationMode ? LSN_V_IRQ_BRK_E : LSN_V_IRQ;
		}
		else {
			m_fsState.vBrkVector = m_fsState.bEmulationMode ? LSN_V_IRQ_BRK_E : LSN_V_BRK;
		}

		if LSN_LIKELY( !m_bRdyLow ) {
			if ( m_bDetectedNmi ) {
				m_bHandleNmi = m_bDetectedNmi = false;
				m_bNmiStatusLine = false;
			}
			m_bHandleIrq = false;
		}
#endif	// #ifdef LSN_CPU_VERIFY

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Selects the COP vector etc.
	 * 
	 * \tparam _bAdjS If true, S is updated.
	 **/
	template <bool _bAdjS>
	inline void CRicoh5A22::SelectCopVectors() {
		LSN_INSTR_START_PHI1( true );
		
		if constexpr ( _bAdjS ) {	
			LSN_UPDATE_S;
		}

		// Select vector to use.
		if ( m_fsState.bEmulationMode ) {
			m_fsState.vBrkVector = LSN_V_COP_E;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet Vector to $FFF4." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			m_fsState.vBrkVector = LSN_V_COP;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet Vector to $FFE4." );
#endif	// LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Prepares to enter a new instruction.
	 *
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
	 */
	template <bool _bIncPc, bool _bAdjS, bool _bCheckStartOfFunction>
	inline void CRicoh5A22::BeginInst() {
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
		m_pfTickFunc = m_pfTickFuncCopy = &CRicoh5A22::Tick_InstructionCycleStd;
		m_fsState.bBoundaryCrossed = false;
		//m_ui8RdyOffCnt = 0;
		LSN_INSTR_END_PHI1;
	}

	/** Sets I and X. */
	inline void CRicoh5A22::SetBrkFlags() {
		LSN_INSTR_START_PHI1( true );

		SetBit<I(), true>( m_fsState.rRegs.ui8Status );
		SetBit<D(), false>( m_fsState.rRegs.ui8Status );
		
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet I, unset D." );
#endif // #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/** Skips the next instruction if the M status flag is set. */
	inline void CRicoh5A22::SkipIfM_Phi2() {
		LSN_NEXT_FUNCTION;

		m_ui8Speed = m_ui8FastDiv;

		if ( (m_fsState.rRegs.ui8Status & M()) ) {
			LSN_NEXT_FUNCTION_BY( 2 );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tIf M is set, skip the next cycle." );
#endif	// LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/** Skips the next instruction if the low byte of D is 0. */
	inline void CRicoh5A22::SkipOnDL_Phi2() {
		LSN_NEXT_FUNCTION;

		m_ui8Speed = m_ui8FastDiv;

		if ( !(m_fsState.rRegs.ui16D & 0xFF) ) {
			LSN_NEXT_FUNCTION_BY( 2 );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tIf D.L is not 0, skip the next cycle." );
#endif	// LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/** Transfer 16 bit A to S.  Sets N and Z. */
	inline void CRicoh5A22::Tcs() {
		LSN_INSTR_START_PHI1( false );

		if ( m_fsState.bEmulationMode ) {
			m_fsState.rRegs.ui16S = m_fsState.rRegs.ui8A[0];
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSets S to A.L." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			m_fsState.rRegs.ui16S = m_fsState.rRegs.ui16A;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSets S to A." );
#endif	// LSN_CYCLES_DOC
		}

		/*if ( (m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<N()>( m_fsState.rRegs.ui8Status, m_fsState.rRegs.ui8S[0] & 0x80 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.rRegs.ui8S[0] );
		}
		else {
			SetBit<N()>( m_fsState.rRegs.ui8Status, m_fsState.rRegs.ui8S[1] & 0x80 );
			SetBit<Z()>( m_fsState.rRegs.ui8Status, !m_fsState.rRegs.ui16S );
		}*/

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/** Performs m_ui16Operand &= ~A.  Sets Z. */
	inline void CRicoh5A22::Trb() {
		LSN_INSTR_START_PHI1( false );

		if ( (m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<Z()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui8A[0] & m_fsState.ui8Operand[0]) == 0 );
		}
		else {
			SetBit<Z()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui16A & m_fsState.ui16Operand) == 0 );
		}

#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tZ based off (A.L & Operand.L)." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, Z based off (A.L & Operand.L), otherwise set Z based off (A & Operand)." );
		}
		lsn::DebugA( " Perform Operand &= ~A." );
#endif	// LSN_CYCLES_DOC
		
		m_fsState.ui16Operand &= ~m_fsState.rRegs.ui16A;


		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/** Performs m_ui16Operand |= A.  Sets Z. */
	inline void CRicoh5A22::Tsb() {
		LSN_INSTR_START_PHI1( false );

		if ( (m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<Z()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui8A[0] & m_fsState.ui8Operand[0]) == 0 );
		}
		else {
			SetBit<Z()>( m_fsState.rRegs.ui8Status, (m_fsState.rRegs.ui16A & m_fsState.ui16Operand) == 0 );
		}
		
#ifdef LSN_CYCLES_DOC
		if ( m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet Z based off (A.L & Operand.L)." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, set Z based off (A.L & Operand.L), otherwise set Z based off (A & Operand)." );
		}
		lsn::DebugA( " Perform Operand |= A." );
#endif	// LSN_CYCLES_DOC

		m_fsState.ui16Operand |= m_fsState.rRegs.ui16A;


		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::Write_Operand_High_To_AddrOrPtr_Phi2() {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.ui16Address + 1, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1\tWrite Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.ui16Pointer + 1, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1\tWrite Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 **/
	template <bool _bTo>
	inline void CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2() {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( m_fsState.ui16Address + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1:DB\tWrite Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( m_fsState.ui16Pointer + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1:DB\tWrite Operand.H." );
#endif	// LSN_CYCLES_DOC
		}
		
		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2() {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.ui16Address, m_fsState.ui8Operand[0], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address\tWrite Operand.L." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( m_fsState.ui16Pointer, m_fsState.ui8Operand[0], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer\tWrite Operand.L." );
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If M flag is set, skip the next cycle." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			if constexpr ( _bEndInstr ) {
				LSN_FINISH_INST( true );
			}
			else {
				LSN_NEXT_FUNCTION;
			}
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
	 * 
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_Phi2() {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( m_fsState.ui16Address, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[0], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address:DB\tWrite Operand.L." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( m_fsState.ui16Pointer, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[0], m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer:DB\tWrite Operand.L." );
#endif	// LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If M flag is set, skip the next cycle." );
#endif	// LSN_CYCLES_DOC
		}
		else {
			if constexpr ( _bEndInstr ) {
				LSN_FINISH_INST( true );
			}
			else {
				LSN_NEXT_FUNCTION;
			}
		}

		LSN_INSTR_END_PHI2;
	}

#pragma warning( pop )

}	// namespace lsn
