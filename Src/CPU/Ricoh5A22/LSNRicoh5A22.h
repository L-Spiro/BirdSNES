/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A Ricoh 5A22 processor.
 */


#pragma once

#include "../../LSNBirdSNES.h"
#include "../../Bus/LSNBusA.h"
#include "../../Foundation/LSNBits.h"
#include "../../System/LSNTickable.h"
#include "LSNRicoh5A22Base.h"

#ifdef LSN_CPU_VERIFY
#include <LSONJson.h>
#endif	// #ifdef LSN_CPU_VERIFY

#define LSN_INSTR_START_PHI1( ISREAD )									/*_prCpu->m_fsState.bIsReadCycle = (ISREAD)*/
#define LSN_INSTR_END_PHI1
#define LSN_INSTR_START_PHI2_READ_BUSA( ADDR, BANK, RESULT, SPEED )		RESULT = _prCpu->m_baBusA.Read( uint16_t( ADDR ), uint8_t( BANK ), (SPEED) )
#define LSN_INSTR_START_PHI2_WRITE_BUSA( ADDR, BANK, VAL, SPEED )		_prCpu->m_baBusA.Write( uint16_t( ADDR ), uint8_t( BANK ), uint8_t( VAL ), (SPEED) )
#define LSN_INSTR_START_PHI2_READ0_BUSA( ADDR, RESULT, SPEED )			RESULT = _prCpu->m_baBusA.ReadBank0( uint16_t( ADDR ), (SPEED) )
#define LSN_INSTR_START_PHI2_WRITE0_BUSA( ADDR, VAL, SPEED )			_prCpu->m_baBusA.WriteBank0( uint16_t( ADDR ), uint8_t( VAL ), (SPEED) )
#define LSN_INSTR_END_PHI2

#define LSN_NEXT_FUNCTION_BY( AMT )										_prCpu->m_fsState.ui8FuncIndex += AMT
#define LSN_NEXT_FUNCTION												LSN_NEXT_FUNCTION_BY( 1 )
#define LSN_FINISH_INST( CHECK_INTERRUPTS )								if constexpr ( CHECK_INTERRUPTS ) { LSN_CHECK_INTERRUPTS; } LSN_NEXT_FUNCTION

#define LSN_CHECK_INTERRUPTS											if ( !(_prCpu->m_fsState.rRegs.ui8Status & I()) ) { _prCpu->m_bHandleIrq = _prCpu->m_bIrqStatusPhi1Flag; } _prCpu->m_bHandleNmi |= _prCpu->m_bDetectedNmi

#define LSN_PUSH( VAL, SPEED )											LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.bEmulationMode ? (0x100 | uint8_t( _prCpu->m_fsState.rRegs.ui8S[0] + _i8SOff )) : (_prCpu->m_fsState.rRegs.ui16S + _i8SOff), (VAL), (SPEED) ); _prCpu->m_fsState.ui16SModify = uint16_t( int16_t( -1 + _i8SOff ) )
#define LSN_POP( RESULT, SPEED )										LSN_INSTR_START_PHI2_READ0_BUSA( _prCpu->m_fsState.bEmulationMode ? (0x100 | uint8_t( _prCpu->m_fsState.rRegs.ui8S[0] + _i8SOff )) : (_prCpu->m_fsState.rRegs.ui16S + _i8SOff), (RESULT), (SPEED) ); _prCpu->m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) )

#define LSN_PUSH_SPECIAL( VAL, SPEED )									LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.bEmulationMode ? ((0x100 | _prCpu->m_fsState.rRegs.ui8S[0]) + _i8SOff) : (_prCpu->m_fsState.rRegs.ui16S + _i8SOff), (VAL), (SPEED) ); _prCpu->m_fsState.ui16SModify = uint16_t( int16_t( -1 + _i8SOff ) )
#define LSN_POP_SPECIAL( RESULT, SPEED )								LSN_INSTR_START_PHI2_READ0_BUSA( _prCpu->m_fsState.bEmulationMode ? ((0x100 | _prCpu->m_fsState.rRegs.ui8S[0]) + _i8SOff) : (_prCpu->m_fsState.rRegs.ui16S + _i8SOff), (RESULT), (SPEED) ); _prCpu->m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) )

#define LSN_UPDATE_PC													if LSN_LIKELY( _prCpu->m_fsState.bAllowWritingToPc ) { _prCpu->m_fsState.rRegs.ui16Pc += _prCpu->m_fsState.ui16PcModify; } _prCpu->m_fsState.ui16PcModify = 0
#define LSN_UPDATE_S													_prCpu->m_fsState.rRegs.ui16S += _prCpu->m_fsState.ui16SModify; _prCpu->m_fsState.ui16SModify = 0; if LSN_UNLIKELY( _prCpu->m_fsState.bEmulationMode ) { _prCpu->m_fsState.rRegs.ui8S[1] = 1; }

#ifdef LSN_CPU_VERIFY
//#define LSN_CYCLES_DOC													1
#endif	// #ifdef LSN_CPU_VERIFY


namespace lsn {

#pragma warning( push )
#pragma warning( disable : 4324 )	// warning C4324: 'lsn::CRicoh5A22::LSN_FULL_STATE': structure was padded due to alignment specifier
#pragma warning( disable : 26495 )	// warning C26495: Variable 'lsn::CRicoh5A22::LSN_REGISTERS::<unnamed-tag>::ui16A' is uninitialized. Always initialize a member variable (type.6).

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

		typedef void (*													PfCycle)( CRicoh5A22 * );														/**< A function pointer for the functions that handle each cycle. */
		typedef void (*													PfTicks)( CRicoh5A22 * );														/**< A function pointer for the tick handlers. */

		/** An instruction. The micro-functions (pfHandler) that make up each cycle of each instruction are programmed to know what to do and can correctly pass the cycles without
		 *	using ui8TotalCycles or amAddrMode. This means pcName, ui8TotalCycles, and amAddrMode are only used for debugging, verification, printing things, etc.
		 * Since we are adding work by increasing the number of functions calls per instruction, we get that time back by not checking for addressing modes or referencing any other
		 *	tables or data. For the sake of performance, each micro-function just knows what to do and does so in the most efficient manner possible, free from any unnecessary
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

		/**
		 * Fetches the next opcode and begins the next instruction.
		 * 
		 * \param _prCpu The CPU object.
		 */
		static inline void												Tick_NextInstructionStd( CRicoh5A22 * _prCpu );

		/**
		 * Performs a cycle inside an instruction.
		 * 
		 * \param _prCpu The CPU object.
		 */
		static inline void												Tick_InstructionCycleStd( CRicoh5A22 * _prCpu );

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
		
		LSN_FULL_STATE													m_fsState;																			/**< Everything a standard instruction-cycle function can modify. Backed up at the start of the first DMA read cycle and restored at the end after the read address for that cycle has been calculated. */
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
		 * Performs an add-with-carry with an operand, setting flags C, N, V, and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Adc_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Adds D and operand, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		template <bool _bTo = LSN_TO_A, bool _bIncPc = false>
		static void														Add_D_And_Operand_To_AddrOrPtr_IncPc( CRicoh5A22 * _prCpu );

		/**
		 * Adds S to m_fsState.ui16Pointer or m_fsState.ui16Address, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		template <bool _bTo = LSN_TO_A>
		static void														Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc( CRicoh5A22 * _prCpu );

		/**
		 * Adds X to m_fsState.ui16Operand and D, stores to m_fsState.ui16Address.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bIncPc = false, bool _bSkipOnDl = false>
		static void														Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl( CRicoh5A22 * _prCpu );

		/**
		 * Adds X to m_fsState.ui16Pointer and D, stores to m_fsState.ui16Address.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A>
		static void														Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc( CRicoh5A22 * _prCpu );

		/**
		 * Adds X to m_fsState.ui16Pointer or m_fsState.ui16Address, sets m_fsState.ui8Bank with optional overflow.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Address and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bBankOverflow If true, m_fsState.ui8Bank accepts the carry from the X+? operation.
		 * \tparam _bPageSkip If true, if a page boundary has not been crossed then the next cycle (assumed to be a fix-up) is skipped.
		 * \tparam _bCopyDbToBank If true, m_fsState.ui8Bank is copied from m_fsState.rRegs.ui8Db, otherwise m_fsState.ui8Bank is unmodified except in the case that overflow is applied to it.
		 * \tparam _bUsePbInsteadOfDb If true, all copies of m_fsState.rRegs.ui8Db are replaced with copies of m_fsState.rRegs.ui8Pb.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bIncPc = true, bool _bBankOverflow = true, bool _bPageSkip = true, bool _bCopyDbToBank = true, bool _bUsePbInsteadOfDb = false>
		static void														Add_X_PtrOrAddr_BankOverflow_PageSkip( CRicoh5A22 * _prCpu );

		/**
		 * Adds Y to m_fsState.ui16Operand and D, stores to m_fsState.ui16Address.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bIncPc = false, bool _bSkipOnDl = false>
		static void														Add_Y_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl( CRicoh5A22 * _prCpu );

		/**
		 * Adds Y to m_fsState.ui16Pointer or m_fsState.ui16Address, sets m_fsState.ui8Bank with optional overflow.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Address and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bBankOverflow If true, m_fsState.ui8Bank accepts the carry from the Y+? operation.
		 * \tparam _bPageSkip If true, if a page boundary has not been crossed then the next cycle (assumed to be a fix-up) is skipped.
		 * \tparam _bCopyDbToBank If true, m_fsState.ui8Bank is copied from m_fsState.rRegs.ui8Db, otherwise m_fsState.ui8Bank is unmodified except in the case that overflow is applied to it.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bIncPc = true, bool _bBankOverflow = true, bool _bPageSkip = true, bool _bCopyDbToBank = true>
		static void														Add_Y_PtrOrAddr_BankOverflow_PageSkip( CRicoh5A22 * _prCpu );

		/**
		 * Performs AND with m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														And( CRicoh5A22 * _prCpu );

		/**
		 * Performs Performs m_fsState.ui16Operand <<= 1. Sets C, N, and V, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Asl( CRicoh5A22 * _prCpu );

		/**
		 * Performs Performs m_fsState.rRegs.ui8A[0] <<= 1 or m_fsState.rRegs.ui16A <<= 1. Sets C, N, and V, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														AslOnA_BeginInst( CRicoh5A22 * _prCpu );

		/** 
		 * Performs BIT between A and Operand. Sets Z, N, and V.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Bit_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * 1st cycle of branch instructions. Decides whether branch condition is met.
		 * 
		 * \tparam _uBit The bit to check.
		 * \tparam _uVal The value the bit needs to be to for a jump to take place.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <uint8_t _uBit, uint8_t _uVal>
		static void														Branch_Cycle1( CRicoh5A22 * _prCpu );

		/**
		 * 2nd cycle of branch instructions. Fetches opcode of next instruction and performs the check to decide which cycle comes next (or to end the instruction).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle1_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * 3rd cycle of branch instructions. Increases PC and skips to end if not branching.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle2( CRicoh5A22 * _prCpu );

		/**
		 * 2nd cycle of branch instructions. Calculates target address if not branching.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle2_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle3( CRicoh5A22 * _prCpu );

		/**
		 * 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle3_Native( CRicoh5A22 * _prCpu );

		/**
		 * 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle3_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * 4th cycle of branch instructions. Page boundary was crossed.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Branch_Cycle4( CRicoh5A22 * _prCpu );

		/**
		 * Final touches to BRK (copies m_fsState.ui16Address to m_fsState.rRegs.ui16Pc) and first cycle of the next instruction.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Brk_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs BRL (Branch Long). Adds 16-bit m_fsState.ui16Operand to m_fsState.rRegs.ui16Pc.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Brl_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Clears the carry bit.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Clc_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Clears the decimal flag (D).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Cld_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Clears the IRQ flag.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Cli_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Clears the overflow flag (V).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Clv_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs A - Operand (comparison). Sets C, N, and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Cmp_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Copies m_fsState.ui8Operand[0] to m_fsState.rRegs.ui8Db.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Copy_Operand_To_Db( CRicoh5A22 * _prCpu );

		/**
		 * Copies m_fsState.ui8Operand[0] to Status with a mask.
		 * 
		 * \tparam _ui8Mask The mask to apply.
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		template <uint8_t _ui8Mask = 0xFF>
		static void														Copy_Operand_To_Status_Mask( CRicoh5A22 * _prCpu );

		/**
		 * Copies from the vector to PC.h.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bEndInstr = false>
		static void														Copy_Vector_To_Pc_H_Phi2( CRicoh5A22 * _prCpu );
			
		/**
		 * Copies from the vector to PC.l.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Copy_Vector_To_Pc_L_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Performs X - Operand (comparison). Sets C, N, and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Cpx_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Y - Operand (comparison). Sets C, N, and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Cpy_BeginInst( CRicoh5A22 * _prCpu );
		
		/**
		 * Performs A--. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														DecOnA_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Operand--. Sets N and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Dec( CRicoh5A22 * _prCpu );

		/**
		 * Performs X--. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Dex_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Y--. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Dey_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs EOR with m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Eor_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Fetches m_fsState.ui8Bank and increments PC.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bEndInstr = false>
		static void														Fetch_Bank_IncPc_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches the current opcode and increments PC.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Fetch_Opcode_IncPc_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches m_fsState.ui8Operand[1] and increments the PC.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bEndInstr = false>
		static void														Fetch_Operand_High_IncPc( CRicoh5A22 * _prCpu );

		/**
		 * Fetches the next operand and discards without incrementing PC, then schedules PC -= 1
		 * for the next PHI1 (so following pushes see PC-1).
		 *
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bEndInstr = false>
		static void														Fetch_Operand_Discard_DecPc_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches the next operand and discards without incrementing PC.
		 * 
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bEndInstr = false>
		static void														Fetch_Operand_Discard_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches the next operand and increments the PC.
		 * 
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bSkipIfM = false, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches the operand and increments PC.
		 * 
		 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bSkipOnDl = false>
		static void														Fetch_Operand_IncPc_SkipOnDl_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches to m_fsState.ui8Address[1] or m_fsState.ui8Pointer[1] and increments PC.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														Fetch_PtrOrAddr_High_IncPc_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches to m_fsState.ui16Address or m_fsState.ui16Pointer and increments PC.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														Fetch_PtrOrAddr_Low_IncPc_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fetches the source bank byte for MVP/MVN and sets DB to the destination bank.
		 *
		 * Destination bank is already in m_fsState.ui8Pointer[0] (Pointer.L).
		 * Source bank is stored into m_fsState.ui8Pointer[1] (Pointer.H).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Fetch_SrcBank_SetDb_IncPc_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Fixes the high bit of m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A>	
		static void														Fix_PtrOrAddr_From_AddrOrPtr_High( CRicoh5A22 * _prCpu );

		/**
		 * Performs Operand++. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Inc( CRicoh5A22 * _prCpu );

		/**
		 * Performs A++. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														IncOnA_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs X++. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Inx_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Y++. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Iny_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs JML [abs] (Indirect Long). Sets PC and PB.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Jml_Absolute_Indirect_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs PC = Address (Absolute JMP).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Jmp_Absolute_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Final touches to JSL (applies pending PC/S updates, then loads PB:PC from Address+Bank)
		 * and begins the next instruction.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Jsl_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Finalizes JSR abs: applies the accumulated S modification, sets PC to the fetched absolute target,
		 * and begins the next instruction.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Jsr_Absolute_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Operand >>= 1. Sets C, N, and Z, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Lsr( CRicoh5A22 * _prCpu );

		/**
		 * Performs A = Operand. Sets N and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Lda_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs X = Operand. Sets N and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Ldx_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Y = Operand. Sets N and Z.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Ldy_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs A >>= 1. Sets C, N, and Z, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														LsrOnA_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Adjusts A/X/Y for MVP and adjusts m_fsState.rRegs.ui16Pc by either 0 (done) or -3 (repeat).
		 *
		 * Notes:
		 * - A is treated as 16-bit counter for block moves.
		 * - If X flag is set, X/Y are adjusted as 8-bit (stay within page 0).
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		template <int16_t _i16AddrAdj = -1>
		static void														MvX_Adjust_And_SetRepeat( CRicoh5A22 * _prCpu );

		/**
		 * Performs NOP.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Nop_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Generic null operation.
		 * 
		 * \tparam _ctReadWriteNull The cycle read/write/neither type.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bBeginInstr If true, BeginInst() is called.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <CRicoh5A22::LSN_CYCLE_TYPE _ctReadWriteNull = CRicoh5A22::LSN_CT_NULL, bool _bIncPc = false, bool _bAdjS = false, bool _bBeginInstr = false>
		static void														Null( CRicoh5A22 * _prCpu );

		/**
		 * Generic null operation on PHI2. Sets the bus access speed to Fast.
		 * 
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _i8SOff If not INT8_MIN, S is scheduled to be adjusted by the given amount on the next PHI1.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bSkipIfM = false, int8_t _i8SOff = INT8_MIN, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Null_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Generic null operation for BRK that can be either a read or write, depending on RESET.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bBeginInstr If true, BeginInst() is called.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false, bool _bAdjS = false, bool _bBeginInstr = false>
		static void														Null_RorW( CRicoh5A22 * _prCpu );

		/**
		 * Performs ORA with m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Ora_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Increases m_fsState.rRegs.ui16Pc and then sets m_fsState.ui16Operand to m_fsState.ui16Operand + m_fsState.rRegs.ui16Pc.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Per_IncPc( CRicoh5A22 * _prCpu );

		/**
		 * Sets m_fsState.ui8Operand[0] to the status byte with Break (X) and Reserved (M) set.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Php( CRicoh5A22 * _prCpu );

		/**
		 * Pull to A. Sets N and Z based on A.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Pla_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Pull to DB, updates N and Z based on DB.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Plb_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Pull to D. Sets N and Z based on D.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Pld_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs PLP and begins the next instruction.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Plp_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Pulls X from the stack. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Plx_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Pulls Y from the stack.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Ply_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8A[1].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_A_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8A[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = -1, bool _bEndInstr = true>
		static void														Push_A_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8D[1].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_D_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8D[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = -1, bool _bEndInstr = true>
		static void														Push_D_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Db.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = true, bool _bSpecial = true>
		static void														Push_Db_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.ui8Operand[1].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_Operand_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.ui8Operand[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = true>
		static void														Push_Operand_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Pb.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = -1, bool _bEndInstr = true, bool _bSpecial = true>
		static void														Push_Pb_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Pb.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_Pb_Brk_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Pc[1] with the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bSpecial = false>
		static void														Push_Pc_High_Brk_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Pc[1] with the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bSpecial = false>
		static void														Push_Pc_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Pc[0] with the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = false, bool _bSpecial = false>
		static void														Push_Pc_Low_Brk_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Pc[0] with the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = false, bool _bSpecial = false>
		static void														Push_Pc_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Status with or without B/X to the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bCop If this is the COP instruction, just do a normal push.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bCop = false>
		static void														Push_S_Brk_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Status with or without B/X to the given S offset.
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_S_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8X[1].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_X_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8X[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = -1, bool _bEndInstr = true>
		static void														Push_X_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Y[1].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Push_Y_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Pushes m_fsState.rRegs.ui8Y[0].
		 * 
		 * \tparam _i8SOff The offset from S to which to write the pushed value.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = -1, bool _bEndInstr = true>
		static void														Push_Y_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Address[1] or m_fsState.ui8Pointer[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bBankWrap If true, the bank wraps (instead of carries) on addresses where + 1 crosses into a new bank.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false, bool _bBankWrap = false>
		static void														Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Address[0] or m_fsState.ui8Pointer[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = true, bool _bEndInstr = false>
		static void														Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		static void														Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = true, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bBankWrap If true, the bank wraps (instead of carries) on addresses where + 1 crosses into a new bank.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false, bool _bBankWrap = true>
		static void														Read_PtrOrAddr_And_DB_To_Operand_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = true, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads (and discards) a byte from the stack.
		 * 
		 * \tparam _i8SOff Offset from S to read.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0>
		static void														Read_Stack_Discard_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads the stack, stores in m_fsState.ui8Bank.
		 * 
		 * \tparam _i8SOff Offset from S to read.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_POP_SPECIAL is used instead of LSN_POP.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = false, bool _bSpecial = true>
		static void														Read_Stack_To_Bank_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads the stack with offset, stores in m_fsState.ui8Operand[1].
		 * 
		 * \tparam _i8SOff Offset from S to read.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = false, bool _bSpecial = false>
		static void														Read_Stack_To_Operand_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads the stack, stores in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _i8SOff Offset from S to read.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSpecial If true, LSN_POP_SPECIAL is used instead of LSN_POP.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <int8_t _i8SOff = 0, bool _bEndInstr = false, bool _bSpecial = false, bool _bSkipIfM = false, bool _bSkipIfX = false>
		static void														Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from [m_fsState.rRegs.ui16X:m_fsState.ui8Bank] into m_fsState.ui8Operand[0] for MVP.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Read_X_And_Bank_To_Operand_Low_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \tparam _bLowByteWrap If true, when adding 1 to the target address causes overflow, the high bits are unaffected (the low byte wraps only).
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bLowByteWrap = false, bool _bEndInstr = false>
		static void														ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Pointer[0] or m_fsState.ui8Address[0].
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bLowByteWrap If true, when adding 1 to the target address causes overflow, the high bits are unaffected (the low byte wraps only).
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bLowByteWrap = false>
		static void														ReadBank0_PtrOrAddr_To_Bank_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		static void														ReadBank0_PtrOrAddr_To_Bank_LowByteWrap_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		static void														ReadBank0_PtrOrAddr_To_Operand_High_LowByteWrap_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bEndInstr = false>
		static void														ReadBank0_PtrOrAddr_To_Operand_High_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Operand[0].
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bFrom = LSN_FROM_A, bool _bSkipIfM = false, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Resets Status bits based on Operand. Handles X/M flag sizing updates.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Rep_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Operand = (Operand << 1) | C. Sets C, N, and Z, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Rol( CRicoh5A22 * _prCpu );
		
		/**
		 * Performs A = (A << 1) | C. Sets C, N, and Z, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														RolOnA_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Operand = (Operand >> 1) | (C << 7/15). Sets C, N, and Z, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Ror( CRicoh5A22 * _prCpu );

		/**
		 * Performs A = (A >> 1) | (C << 7/15). Sets C, N, and Z, optionally increases PC.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														RorOnA_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs RTI (sets PC/PB from pulled bytes) and begins the next instruction.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Rti_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Pulls the PBR and PC from the stack for RTL.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Rtl_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Returns from subroutine. Pulls PC from stack, adds 1, begins next instruction.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Rts_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs a subtract-with-borrow with an operand, setting flags C, N, V, and Z.
		 *
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Sbc_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Sets the carry bit.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Sec_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Sets the decimal flag (D).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Sed_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Sets the IRQ flag.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Sei_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Selects the BRK vector etc.
		 * 
		 * \tparam _bAdjS If true, S is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bAdjS>
		static void														Select_Brk_Vectors( CRicoh5A22 * _prCpu );

		/**
		 * Selects the COP vector etc.
		 * 
		 * \tparam _bAdjS If true, S is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bAdjS>
		static void														Select_Cop_Vectors( CRicoh5A22 * _prCpu );

		/**
		 * Sets Status bits based on Operand. Handles X/M flag sizing updates.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		static void														Sep_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Sets I and X.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Set_Brk_Flags( CRicoh5A22 * _prCpu );

		/**
		 * Skips the next instruction if the M status flag is set.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														SkipIfM_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Skips the next instruction if the low byte of D is 0.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														SkipOnDL_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Copies A to m_fsState.ui16Operand.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Sta( CRicoh5A22 * _prCpu );

		/**
		 * Stops the processor (STP).
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Stp_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Copies X to m_fsState.ui16Operand.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Stx( CRicoh5A22 * _prCpu );

		/**
		 * Copies Y to m_fsState.ui16Operand.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Sty( CRicoh5A22 * _prCpu );

		/**
		 * Sets m_fsState.ui16Operand to 0.
		 * 
		 * \tparam _bIncPc If true, PC is updated.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bIncPc = false>
		static void														Stz( CRicoh5A22 * _prCpu );

		/**
		 * Performs X = A. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tax_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Y = A. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tay_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Transfer 16 bit A to D. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tcd_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Transfer 16 bit A to S. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tcs_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Transfer 16-bit D to A. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tdc_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs m_ui16Operand &= ~A. Sets Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Trb( CRicoh5A22 * _prCpu );

		/**
		 * Performs m_ui16Operand |= A. Sets Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tsb( CRicoh5A22 * _prCpu );

		/**
		 * Transfer 16-bit S to A. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tsc_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs X = S. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tsx_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs A = X. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Txa_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs S = X. Does not set flags.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Txs_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs Y = X. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Txy_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs A = Y. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tya_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs X = Y. Sets N and Z.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Tyx_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Puts the CPU into a waiting state.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Wai_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Executes WDM (reserved). Consumes the immediate byte; no architecturally visible effects.
		 * 
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		static void														Wdm_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Writes A to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														WriteBank0_A_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes A to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false>
		static void														WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														WriteBank0_Operand_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false>
		static void														WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes X to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														WriteBank0_X_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes X to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CRicoh5A22 instance.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfX = false, bool _bEndInstr = false>
		static void														WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes Y to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														WriteBank0_Y_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes Y to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfX = false, bool _bEndInstr = false>
		static void														WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes 0 to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														WriteBank0_Zero_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes 0 to m_fsState.ui16Address or m_fsState.ui16Pointer.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false>
		static void														WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.rRegs.ui8A[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														Write_A_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.rRegs.ui8A[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = true, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Write_A_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bBankWrap If true, the bank wraps (instead of carries) on addresses where + 1 crosses into a new bank.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false, bool _bBankWrap = true>
		static void														Write_Operand_High_To_AddrOrPtr_And_DB_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.rRegs.ui8X[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														Write_X_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.rRegs.ui8X[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false, bool _bSkipIfX = true>
		static void														Write_X_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.rRegs.ui8Y[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														Write_Y_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.rRegs.ui8Y[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = false, bool _bEndInstr = false, bool _bSkipIfX = true>
		static void														Write_Y_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bEndInstr = false>
		static void														Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
		 * 
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
		 * \param _prCpu The CPU object.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bSkipIfM = true, bool _bEndInstr = false, bool _bSkipIfX = false>
		static void														Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Writes m_fsState.ui8Operand[0] to [m_fsState.rRegs.ui16Y:m_fsState.ui8Pointer[0]] for MVP.
		 * 
		 * \param _prCpu The CPU object.
		 **/
		static void														Write_Operand_Low_To_Y_And_DB_Phi2( CRicoh5A22 * _prCpu );

		/**
		 * Exchanges the low and high bytes of the Accumulator. Sets N and Z based on the new low byte.
		 * 
		 * \param _prCpu The CPU object.
		 **/
		static void														Xba_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Exchanges the carry (C) and emulation (E) flags.
		 * 
		 * \param _prCpu The CPU object.
		 **/
		static void														Xce_BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Prepares to enter a new instruction.
		 *
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
		 * \param _prCpu The CRicoh5A22 instance.
		 */
		template <bool _bIncPc = false, bool _bAdjS = false, bool _bCheckStartOfFunction = true>
		static inline void												BeginInst( CRicoh5A22 * _prCpu );

		/**
		 * Performs an 8-bit add-with-carry with an operand, setting flags C, N, V, and Z.
		 *
		 * \param _prCpu The CRicoh5A22 instance.
		 * \param _ui8RegVal The register value used in the comparison.
		 * \param _ui8OpVal The operand value used in the comparison.
		 */
		static inline void												Adc_8( CRicoh5A22 * _prCpu, uint8_t &_ui8RegVal, uint8_t _ui8OpVal );

		/**
		 * Performs a 16-bit add-with-carry with an operand, setting flags C, N, V, and Z.
		 * Respects Decimal Mode (D) when enabled.
		 *
		 * \param _prCpu The CRicoh5A22 instance.
		 * \param _ui16RegVal The register value used in the operation.
		 * \param _ui16OpVal The operand value used in the operation.
		 */
		static void														Adc_16( CRicoh5A22 * _prCpu, uint16_t &_ui16RegVal, uint16_t _ui16OpVal );

		/**
		 * Performs a compare against a register and an operand by setting flags.
		 *
		 * \param _prCpu The CRicoh5A22 instance.
		 * \param _ui8RegVal The register value used in the comparison.
		 * \param _ui8OpVal The operand value used in the comparison.
		 */
		static inline void												Cmp( CRicoh5A22 * _prCpu, uint8_t _ui8RegVal, uint8_t _ui8OpVal );

		/**
		 * Performs a compare against a register and an operand by setting flags.
		 *
		 * \param _prCpu The CRicoh5A22 instance.
		 * \param _ui16RegVal The register value used in the comparison.
		 * \param _ui16OpVal The operand value used in the comparison.
		 */
		static inline void												Cmp( CRicoh5A22 * _prCpu, uint16_t _ui16RegVal, uint16_t _ui16OpVal );

		/**
		 * Performs an 8-bit subtract-with-carry with an operand, setting flags C, N, V, and Z.
		 *
		 * \param _prCpu The CRicoh5A22 instance.
		 * \param _ui8RegVal The register value used in the comparison.
		 * \param _ui8OpVal The operand value used in the comparison.
		 */
		static inline void												Sbc_8( CRicoh5A22 * _prCpu, uint8_t &_ui8RegVal, uint8_t _ui8OpVal );

		/**
		 * Performs a 16-bit subtract-with-carry with an operand, setting flags C, N, V, and Z.
		 * Respects Decimal Mode (D) when enabled.
		 *
		 * \param _prCpu The CRicoh5A22 instance.
		 * \param _ui16RegVal The register value used in the operation.
		 * \param _ui16OpVal The operand value used in the operation.
		 */
		static void														Sbc_16( CRicoh5A22 * _prCpu, uint16_t &_ui16RegVal, uint16_t _ui16OpVal );
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Fuctions.
	/**
	 * Fetches the next opcode and begins the next instruction.
	 * 
	 * \param _prCpu The CPU object.
	 */
	inline void CRicoh5A22::Tick_NextInstructionStd( CRicoh5A22 * _prCpu ) {
		BeginInst( _prCpu );
	}

	/**
	 * Performs a cycle inside an instruction.
	 * 
	 * \param _prCpu The CPU object.
	 */
	inline void CRicoh5A22::Tick_InstructionCycleStd( CRicoh5A22 * _prCpu ) {
		//(this->*m_iInstructionSet[m_fsState.ui16OpCode].pfHandler[m_fsState.bEmulationMode][m_fsState.ui8FuncIndex])();
		(*_prCpu->m_fsState.pfCurInstruction[_prCpu->m_fsState.ui8FuncIndex])( _prCpu );
	}

	/**
	 * Performs an add-with-carry with an operand, setting flags C, N, V, and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Adc_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		BeginInst<_bIncPc>( _prCpu );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			Adc_8( _prCpu, rCpu.m_fsState.rRegs.ui8A[0], rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			Adc_16( _prCpu, rCpu.m_fsState.rRegs.ui16A, rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA(
				"\tIf D flag == 0:\r\n"
				"\t\t  Result = ui16(A.L) + ui16(Operand) + C flag.\r\n"
				"\t\t  V flag = (~(ui16(A.L) ^ ui16(Operand)) & (ui16(A.L) ^ ui8(Result)) & $80) != 0.\r\n"
				"\t\t  C flag = Result > $FF.\r\n"
				"\t\t  Result = ui8(Result). Z flag = Result == $00. N flag = (Result & $80) != 0.\r\n"
				"\t\tIf D flag == 1:\r\n"
				"\t\t  Lo = ui16(A.L & 0x0F) + ui16(Operand & 0x0F) + C flag.\r\n"
				"\t\t  if (Lo > 9) Lo += 6.\r\n"
				"\t\t  CarryToHi = Lo > $0F ? 1 : 0.\r\n"
				"\t\t  HiSum = ui16(A.L >> 4) + ui16(Operand >> 4) + CarryToHi.\r\n"
				"\t\t  V flag = (~((A.L >> 4) ^ (Operand >> 4)) & ((A.L >> 4) ^ HiSum) & $08) != 0.\r\n"
				"\t\t  if (HiSum > 9) HiSum += 6.\r\n"
				"\t\t  C flag = HiSum > $0F.\r\n"
				"\t\t  Result = ui8(((HiSum & 0x0F) << 4) | (Lo & $0F)).\r\n"
				"\t\t  Z flag = Result == $00. N flag = (Result & $80) != 0." );
		}
		else {
			lsn::DebugA( 
				"\tIf M flag == 0 (8-bit):\r\n"
				"\t\t  If D flag == 0:\r\n"
				"\t\t    Result = ui16(A.L) + ui16(Operand) + C flag.\r\n"
				"\t\t    V flag = (~(ui16(A.L) ^ ui16(Operand)) & (ui16(A.L) ^ ui8(Result)) & $80) != 0.\r\n"
				"\t\t    C flag = Result > $FF.\r\n"
				"\t\t    Result = ui8(Result). Z flag = Result == $00. N flag = (Result & $80) != 0.\r\n"
				"\t\t  If D flag == 1:\r\n"
				"\t\t    Lo = ui16(A.L & 0x0F) + ui16(Operand & 0x0F) + C flag.\r\n"
				"\t\t    if (Lo > 9) Lo += 6.\r\n"
				"\t\t    CarryToHi = Lo > $0F ? 1 : 0.\r\n"
				"\t\t    HiSum = ui16(A.L >> 4) + ui16(Operand >> 4) + CarryToHi.\r\n"
				"\t\t    V flag = (~((A.L >> 4) ^ (Operand >> 4)) & ((A.L >> 4) ^ HiSum) & $08) != 0.\r\n"
				"\t\t    if (HiSum > 9) HiSum += 6.\r\n"
				"\t\t    C flag = HiSum > $0F.\r\n"
				"\t\t    Result = ui8(((HiSum & 0x0F) << 4) | (Lo & $0F)).\r\n"
				"\t\t    Z flag = Result == $00. N flag = (Result & $80) != 0.\r\n"
				"\t\tIf M flag == 0 (16-bit):\r\n"
				"\t\t  If D flag == 0:\r\n"
				"\t\t    Result = ui32(A) + ui32(Operand) + C flag.\r\n"
				"\t\t    V flag = (~(ui32(A) ^ ui32(Operand)) & (ui32(A) ^ ui16(Result)) & $8000) != 0 ).\r\n"
				"\t\t    C flag = Result > $FFFF.\r\n"
				"\t\t    Result = ui16(Result).\r\n"
				"\t\t    Z flag = Result == $0000. N flag = (Result & $8000) != 0.\r\n"
				"\t\t  If D flag == 1:\r\n"
				"\t\t    Result = ui16(0). Carry = ui16(C flag).\r\n"
				"\t\t    for i = 0, 4, 8, 12:\r\n"
				"\t\t      DigitSum = ui16((A >> i) & $0F) + ui16((Operand >> i) & $0F) + Carry.\r\n"
				"\t\t      if (i == 12) V flag = (~((A >> 12) ^ (Operand >> 12)) & ((A >> 12) ^ DigitSum) & $08) != 0.\r\n"
				"\t\t      if (DigitSum > 9) DigitSum += 6.\r\n"
				"\t\t      Carry = (DigitSum > $0F) ? 1 : 0.\r\n"
				"\t\t      Result |= ui16((DigitSum & $0F) << i).\r\n"
				"\t\t    C flag = Carry != 0. Z flag = Result != $0000. N flag = (Result & $8000) != 0." );
		}
#endif // #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Adds D and operand, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	template <bool _bTo, bool _bIncPc>
	inline void CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tInc. PC if previous cycle was skipped. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bTo == LSN_TO_A ) {
			rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Set Address to Operand + D." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Set Pointer to Operand + D." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds S to m_fsState.ui16Pointer or m_fsState.ui16Address, stores in m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	template <bool _bTo>
	inline void CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		std::string sTmp = "\tInc. PC. ";
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bTo == LSN_TO_A ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Pointer + (rCpu.m_fsState.rRegs.ui8S[0] | 0x100);
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Address to Pointer + (S.L | $0100).";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Pointer + rCpu.m_fsState.rRegs.ui16S;
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Address to Pointer + S.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Address + (rCpu.m_fsState.rRegs.ui8S[0] | 0x100);
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Pointer to Address + S.L | $0100.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Address + rCpu.m_fsState.rRegs.ui16S;
#ifdef LSN_CYCLES_DOC
				sTmp += "Set Pointer to Address + S.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sTmp.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds X to m_fsState.ui16Operand and D, stores to m_fsState.ui16Address.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bIncPc, bool _bSkipOnDl>
	inline void CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

#ifdef LSN_CYCLES_DOC
		std::string sTmp = "\t";
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		sTmp += "Inc. PC. ";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bTo == LSN_TO_A ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode && rCpu.m_fsState.rRegs.ui8D[0] == 0x00 ) {
				rCpu.m_fsState.ui8Address[0] = uint8_t( rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui8X[0] + rCpu.m_fsState.rRegs.ui16D );
				rCpu.m_fsState.ui8Address[1] = rCpu.m_fsState.rRegs.ui8D[1];
			}
			else {
				rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui16X + rCpu.m_fsState.rRegs.ui16D;
			}
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				sTmp += "If D.L is 0, Address.L = Operand + X.L + D.L, Address.H = D.H, otherwise Address = Operand + X + D. ";
			}
			else {
				sTmp += "Address = Operand + X + D. ";
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode && rCpu.m_fsState.rRegs.ui8D[0] == 0x00 ) {
				rCpu.m_fsState.ui8Pointer[0] = uint8_t( rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui8X[0] + rCpu.m_fsState.rRegs.ui16D );
				rCpu.m_fsState.ui8Pointer[1] = rCpu.m_fsState.rRegs.ui8D[1];
			}
			else {
				rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui16X + rCpu.m_fsState.rRegs.ui16D;
			}
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				sTmp += "If D.L is 0, Pointer.L = Operand + X.L + D.L, Pointer.H = D.H, otherwise Pointer = Operand + X + D. ";
			}
			else {
				sTmp += "Pointer = Operand + X + D. ";
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipOnDl ) {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}

#ifdef LSN_CYCLES_DOC
			sTmp += "If D.L is 0, skip 2 half-cycles.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sTmp.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds X to m_fsState.ui16Pointer and D, stores to m_fsState.ui16Address.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo>	
	inline void CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		std::string sTmp = "\tInc. PC. ";
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bTo == LSN_TO_A ) {
			rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Pointer + rCpu.m_fsState.rRegs.ui16X + rCpu.m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			sTmp += "Set Pointer to Pointer + X + D.";
#endif	// #ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				rCpu.m_fsState.ui8Address[0] = rCpu.m_fsState.ui8Pointer[0];
				rCpu.m_fsState.ui8Address[1] = uint8_t( rCpu.m_fsState.rRegs.ui8D[1] );
#ifdef LSN_CYCLES_DOC
				sTmp += "\r\n\t\tAddress.L = Pointer.L.\r\n\t\tAddress.H = D.H.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Pointer;
#ifdef LSN_CYCLES_DOC
				sTmp += "\r\n\t\tAddress = Pointer.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Address + rCpu.m_fsState.rRegs.ui16X + rCpu.m_fsState.rRegs.ui16D;
#ifdef LSN_CYCLES_DOC
			sTmp += "Set Address to Address + X + D.";
#endif	// #ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				rCpu.m_fsState.ui8Pointer[0] = rCpu.m_fsState.ui8Address[0];
				rCpu.m_fsState.ui8Pointer[1] = uint8_t( rCpu.m_fsState.rRegs.ui8D[1] );
#ifdef LSN_CYCLES_DOC
				sTmp += "\r\n\t\tPointer.L = Address.L.\r\n\t\tPointer.H = D.H.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Address;
#ifdef LSN_CYCLES_DOC
				sTmp += "\r\n\t\tPointer = Address.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sTmp.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds X to m_fsState.ui16Pointer or m_fsState.ui16Address, sets m_fsState.ui8Bank with optional overflow.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Address and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bBankOverflow If true, m_fsState.ui8Bank accepts the carry from the X+? operation.
	 * \tparam _bPageSkip If true, if a page boundary has not been crossed then the next cycle (assumed to be a fix-up) is skipped.
	 * \tparam _bCopyDbToBank If true, m_fsState.ui8Bank is copied from m_fsState.rRegs.ui8Db, otherwise m_fsState.ui8Bank is unmodified except in the case that overflow is applied to it.
	 * \tparam _bUsePbInsteadOfDb If true, all copies of m_fsState.rRegs.ui8Db are replaced with copies of m_fsState.rRegs.ui8Pb.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bIncPc, bool _bBankOverflow, bool _bPageSkip, bool _bCopyDbToBank, bool _bUsePbInsteadOfDb>
	inline void CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		uint32_t ui32Orig, ui32Tmp;
		if constexpr ( _bTo == LSN_TO_A ) {
			ui32Orig = rCpu.m_fsState.ui16Address;
			ui32Tmp = ui32Orig + rCpu.m_fsState.rRegs.ui16X;
			rCpu.m_fsState.ui16Address = uint16_t( ui32Tmp );
#ifdef LSN_CYCLES_DOC
			if constexpr ( _bBankOverflow ) {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Address.\r\n\t\tTmp = ui32(Address + X).\r\n\t\tAddress = ui16(Tmp)." );
				}
				else {
					lsn::DebugA( "Perform Tmp = ui32(Address + X).\r\n\t\tAddress = ui16(Tmp)." );
				}
			}
			else {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Address.\r\n\t\tAddress += X." );
				}
				else {
					lsn::DebugA( "Perform Address += X." );
				}
			}
#endif	// #ifdef LSN_CYCLES_DOC
			if constexpr ( _bPageSkip ) {
				// Page-skip fix: compare against Address.H when updating Address.
				if ( uint8_t( ui32Orig >> 8 ) == rCpu.m_fsState.ui8Address[1] && (rCpu.m_fsState.bEmulationMode || (!rCpu.m_fsState.bEmulationMode && (rCpu.m_fsState.rRegs.ui8Status & X()))) ) {
					LSN_NEXT_FUNCTION_BY( 2 );
				}
#ifdef LSN_CYCLES_DOC
				if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Address.H, skip the next cycle." );
				}
				else {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Address.H and the X flag is set, skip the next cycle." );
				}
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			ui32Orig = rCpu.m_fsState.ui16Pointer;
			ui32Tmp = ui32Orig + rCpu.m_fsState.rRegs.ui16X;
			rCpu.m_fsState.ui16Pointer = uint16_t( ui32Tmp );
#ifdef LSN_CYCLES_DOC
			if constexpr ( _bBankOverflow ) {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Pointer.\r\n\t\tTmp = ui32(Pointer + X).\r\n\t\tPointer = ui16(Tmp)." );
				}
				else {
					lsn::DebugA( "Perform Tmp = ui32(Pointer + X).\r\n\t\tPointer = ui16(Tmp)." );
				}
			}
			else {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Pointer.\r\n\t\tPointer += X." );
				}
				else {
					lsn::DebugA( "Perform Pointer += X." );
				}
			}
#endif	// #ifdef LSN_CYCLES_DOC
			if constexpr ( _bPageSkip ) {
				if ( uint8_t( ui32Orig >> 8 ) == rCpu.m_fsState.ui8Pointer[1] && (rCpu.m_fsState.bEmulationMode || (!rCpu.m_fsState.bEmulationMode && (rCpu.m_fsState.rRegs.ui8Status & X()))) ) {
					LSN_NEXT_FUNCTION_BY( 2 );
				}
#ifdef LSN_CYCLES_DOC
				if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Pointer.H, skip 2 half-cycles." );
				}
				else {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Pointer.H and the X flag is set, skip 2 half-cycles." );
				}
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

		if constexpr ( _bCopyDbToBank ) {
			if constexpr ( _bBankOverflow ) {
				if constexpr ( _bUsePbInsteadOfDb ) {
					rCpu.m_fsState.ui8Bank = uint8_t( rCpu.m_fsState.rRegs.ui8Pb + (ui32Tmp >> 16) );
#ifdef LSN_CYCLES_DOC
					lsn::DebugA( "\r\n\t\tBank = PB + (Tmp >> 16)." );
#endif	// #ifdef LSN_CYCLES_DOC
				}
				else {
					rCpu.m_fsState.ui8Bank = uint8_t( rCpu.m_fsState.rRegs.ui8Db + (ui32Tmp >> 16) );
#ifdef LSN_CYCLES_DOC
					lsn::DebugA( "\r\n\t\tBank = DB + (Tmp >> 16)." );
#endif	// #ifdef LSN_CYCLES_DOC
				}
			}
			else {
				if constexpr ( _bUsePbInsteadOfDb ) {
					rCpu.m_fsState.ui8Bank = rCpu.m_fsState.rRegs.ui8Pb;
#ifdef LSN_CYCLES_DOC
					lsn::DebugA( "\r\n\t\tBank = PB." );
#endif	// #ifdef LSN_CYCLES_DOC
				}
				else {
					rCpu.m_fsState.ui8Bank = rCpu.m_fsState.rRegs.ui8Db;
#ifdef LSN_CYCLES_DOC
					lsn::DebugA( "\r\n\t\tBank = DB." );
#endif	// #ifdef LSN_CYCLES_DOC
				}
			}
		}
		else {
			if constexpr ( _bBankOverflow ) {
				rCpu.m_fsState.ui8Bank += uint8_t( ui32Tmp >> 16 );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "\r\n\t\tBank += (Tmp >> 16)." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds Y to m_fsState.ui16Operand and D, stores to m_fsState.ui16Address.
	 * 
		 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bSkipOnDl If true, the next cycle is skipped if D.L is 0.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bIncPc, bool _bSkipOnDl>
	inline void CRicoh5A22::Add_Y_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

#ifdef LSN_CYCLES_DOC
		std::string sTmp = "\t";
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		sTmp += "Inc. PC. ";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bTo == LSN_TO_A ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode && rCpu.m_fsState.rRegs.ui8D[0] == 0x00 ) {
				rCpu.m_fsState.ui8Address[0] = uint8_t( rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui8Y[0] + rCpu.m_fsState.rRegs.ui16D );
				rCpu.m_fsState.ui8Address[1] = rCpu.m_fsState.rRegs.ui8D[1];
			}
			else {
				rCpu.m_fsState.ui16Address = rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui16Y + rCpu.m_fsState.rRegs.ui16D;
			}
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				sTmp += "If D.L is 0, Address.L = Operand + Y.L + D.L, Address.H = D.H, otherwise Address = Operand + Y + D. ";
			}
			else {
				sTmp += "Address = Operand + Y + D. ";
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode && rCpu.m_fsState.rRegs.ui8D[0] == 0x00 ) {
				rCpu.m_fsState.ui8Pointer[0] = uint8_t( rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui8Y[0] + rCpu.m_fsState.rRegs.ui16D );
				rCpu.m_fsState.ui8Pointer[1] = rCpu.m_fsState.rRegs.ui8D[1];
			}
			else {
				rCpu.m_fsState.ui16Pointer = rCpu.m_fsState.ui16Operand + rCpu.m_fsState.rRegs.ui16Y + rCpu.m_fsState.rRegs.ui16D;
			}
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				sTmp += "If D.L is 0, Pointer.L = Operand + Y.L + D.L, Pointer.H = D.H, otherwise Pointer = Operand + Y + D. ";
			}
			else {
				sTmp += "Pointer = Operand + Y + D. ";
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipOnDl ) {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}

#ifdef LSN_CYCLES_DOC
			sTmp += "If D.L is 0, skip 2 half-cycles.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sTmp.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Adds Y to m_fsState.ui16Pointer or m_fsState.ui16Address, sets m_fsState.ui8Bank with optional overflow.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Address and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bBankOverflow If true, m_fsState.ui8Bank accepts the carry from the Y+? operation.
	 * \tparam _bPageSkip If true, if a page boundary has not been crossed then the next cycle (assumed to be a fix-up) is skipped.
	 * \tparam _bCopyDbToBank If true, m_fsState.ui8Bank is copied from m_fsState.rRegs.ui8Db, otherwise m_fsState.ui8Bank is unmodified except in the case that overflow is applied to it.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bIncPc, bool _bBankOverflow, bool _bPageSkip, bool _bCopyDbToBank>
	inline void CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		uint32_t ui32Orig, ui32Tmp;
		if constexpr ( _bTo == LSN_TO_A ) {
			ui32Orig = rCpu.m_fsState.ui16Address;
			ui32Tmp = ui32Orig + rCpu.m_fsState.rRegs.ui16Y;
			rCpu.m_fsState.ui16Address = uint16_t( ui32Tmp );
#ifdef LSN_CYCLES_DOC
			if constexpr ( _bBankOverflow ) {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Address.\r\n\t\tTmp = ui32(Address + Y).\r\n\t\tAddress = ui16(Tmp)." );
				}
				else {
					lsn::DebugA( "Perform Tmp = ui32(Address + Y).\r\n\t\tAddress = ui16(Tmp)." );
				}
			}
			else {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Address.\r\n\t\tAddress += Y." );
				}
				else {
					lsn::DebugA( "Perform Address += Y." );
				}
			}
#endif	// #ifdef LSN_CYCLES_DOC
			if constexpr ( _bPageSkip ) {
				if ( uint8_t( ui32Orig >> 8 ) == rCpu.m_fsState.ui8Address[1] && (rCpu.m_fsState.bEmulationMode || (!rCpu.m_fsState.bEmulationMode && (rCpu.m_fsState.rRegs.ui8Status & X()))) ) {
					LSN_NEXT_FUNCTION_BY( 2 );
				}
#ifdef LSN_CYCLES_DOC
				if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Address.H, skip 2 half-cycles." );
				}
				else {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Address.H and the X flag is set, skip 2 half-cycles." );
				}
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			ui32Orig = rCpu.m_fsState.ui16Pointer;
			ui32Tmp = ui32Orig + rCpu.m_fsState.rRegs.ui16Y;
			rCpu.m_fsState.ui16Pointer = uint16_t( ui32Tmp );
#ifdef LSN_CYCLES_DOC
			if constexpr ( _bBankOverflow ) {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Pointer.\r\n\t\tTmp = ui32(Pointer + Y).\r\n\t\tPointer = ui16(Tmp)." );
				}
				else {
					lsn::DebugA( "Perform Tmp = ui32(Pointer + Y).\r\n\t\tPointer = ui16(Tmp)." );
				}
			}
			else {
				if constexpr ( _bPageSkip ) {
					lsn::DebugA( "Perform Orig = Pointer.\r\n\t\tPointer += Y." );
				}
				else {
					lsn::DebugA( "Perform Pointer += Y." );
				}
			}
#endif	// #ifdef LSN_CYCLES_DOC
			if constexpr ( _bPageSkip ) {
				if ( uint8_t( ui32Orig >> 8 ) == rCpu.m_fsState.ui8Pointer[1] && (rCpu.m_fsState.bEmulationMode || (!rCpu.m_fsState.bEmulationMode && (rCpu.m_fsState.rRegs.ui8Status & X()))) ) {
					LSN_NEXT_FUNCTION_BY( 2 );
				}
#ifdef LSN_CYCLES_DOC
				if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Pointer.H, skip 2 half-cycles." );
				}
				else {
					lsn::DebugA( "\r\n\t\tIf Orig.H == Pointer.H and the X flag is set, skip 2 half-cycles." );
				}
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

		if constexpr ( _bCopyDbToBank ) {
			if constexpr ( _bBankOverflow ) {
				rCpu.m_fsState.ui8Bank = uint8_t( rCpu.m_fsState.rRegs.ui8Db + (ui32Tmp >> 16) );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "\r\n\t\tBank = DB + (Tmp >> 16)." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				rCpu.m_fsState.ui8Bank = rCpu.m_fsState.rRegs.ui8Db;
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "\r\n\t\tBank = DB." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if constexpr ( _bBankOverflow ) {
				rCpu.m_fsState.ui8Bank += uint8_t( ui32Tmp >> 16 );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "\r\n\t\tBank += (Tmp >> 16)." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs AND with m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::And( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			rCpu.m_fsState.rRegs.ui8A[0] &= rCpu.m_fsState.ui8Operand[0];
		}
		else {
			rCpu.m_fsState.rRegs.ui16A &= rCpu.m_fsState.ui16Operand;
		}

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
		if constexpr ( _bIncPc ) {
			lsn::DebugA( "Inc. PC. " );
		}

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Perform A &= Operand. Set N based off (A.L & $80) and Z based off A.L." );
		}
		else {
			lsn::DebugA( "Perform A &= Operand. If M flag is set, set N based off (A.L & $80) and Z based off A.L, otherwise set N based off (A.H & $80) and Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * Performs Performs m_fsState.ui16Operand <<= 1. Sets C, N, and V, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Asl( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );

			rCpu.m_fsState.ui16Operand <<= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[1] & 0x80) != 0 );

			rCpu.m_fsState.ui16Operand <<= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[1] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui16Operand );
		}


#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( "Set C based off (Operand.L & $80). Perform Operand.L <<= 1. Set N based off (Operand.L & $80) and Z based off Operand.L." );
			}
			else {
				lsn::DebugA( "If M flag is set, set C based off (Operand.L & $80), perform Operand.L <<= 1, and set N based off (Operand.L & $80) and Z based off Operand.L, otherwise set C based off (Operand.H & $80), perform Operand <<= 1, and set N based off (Operand.H & $80) and Z based off Operand." );
			}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs Performs m_fsState.rRegs.ui8A[0] <<= 1 or m_fsState.rRegs.ui16A <<= 1. Sets C, N, and V, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::AslOnA_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );

			rCpu.m_fsState.rRegs.ui8A[0] <<= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[1] & 0x80) != 0 );

			rCpu.m_fsState.rRegs.ui16A <<= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[1] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( "Set C based off (A.L & $80). Perform A.L <<= 1. Set N based off (A.L & $80) and Z based off A.L." );
			}
			else {
				lsn::DebugA( "If M flag is set, set C based off (A.L & $80), perform A.L <<= 1, and set N based off (A.L & $80) and Z based off A.L, otherwise set C based off (A.H & $80), perform A <<= 1, and set N based off (A.H & $80) and Z based off A." );
			}
#endif	// #ifdef LSN_CYCLES_DOC


		BeginInst<false, false, false>( _prCpu );
	}

	/** 
	 * Performs BIT between A and Operand. Sets Z, N, and V.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Bit_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & rCpu.m_fsState.ui8Operand[0]) == 0 );
			if constexpr ( !_bIncPc ) {
				SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );
				SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x40) != 0 );
			}
		}
		else {
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & rCpu.m_fsState.ui16Operand) == 0 );
			if constexpr ( !_bIncPc ) {
				SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[1] & 0x80) != 0 );
				SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[1] & 0x40) != 0 );
			}
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );

		if constexpr ( _bIncPc ) {
			lsn::DebugA( "Inc. PC. " );
		}
#endif	// #ifdef LSN_CYCLES_DOC
		
#ifdef LSN_CYCLES_DOC
		if constexpr ( _bIncPc ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( "Set Z based off (A.L & Operand.L)." );
			}
			else {
				lsn::DebugA( "If M flag is set, set Z based off (A.L & Operand.L), otherwise set Z based off (A & Operand)." );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( "Set Z based off (A.L & Operand.L), set N based off (Operand.L & $80), and set V based off (Operand.L & $40)." );
			}
			else {
				lsn::DebugA( "If M flag is set, set Z based off (A.L & Operand.L), set N based off (Operand.L & $80), and set V based off (Operand.L & $40), otherwise set Z based off (A & Operand), set N based off (Operand.H & $80), and set V based off (Operand.H & $40)." );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * 1st cycle of branch instructions. Decides whether branch condition is met.
	 * 
	 * \tparam _uBit The bit to check.
	 * \tparam _uVal The value the bit needs to be to for a jump to take place.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <uint8_t _uBit, uint8_t _uVal>
	inline void CRicoh5A22::Branch_Cycle1( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.bTakeJump = (rCpu.m_fsState.rRegs.ui8Status & _uBit) == (_uVal * _uBit);


#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tInc. PC." );

		switch ( _uBit ) {
			case C() : {
				lsn::DebugA( std::format( " Decide to branch if C is {}.", _uVal ).c_str() );
				break;
			}
			case Z() : {
				lsn::DebugA( std::format( " Decide to branch if Z is {}.", _uVal ).c_str() );
				break;
			}
			case I() : {
				lsn::DebugA( std::format( " Decide to branch if I is {}.", _uVal ).c_str() );
				break;
			}
			case D() : {
				lsn::DebugA( std::format( " Decide to branch if D is {}.", _uVal ).c_str() );
				break;
			}
			case X() : {
				lsn::DebugA( std::format( " Decide to branch if X is {}.", _uVal ).c_str() );
				break;
			}
			case M() : {
				lsn::DebugA( std::format( " Decide to branch if M is {}.", _uVal ).c_str() );
				break;
			}
			case V() : {
				lsn::DebugA( std::format( " Decide to branch if V is {}.", _uVal ).c_str() );
				break;
			}
			case N() : {
				lsn::DebugA( std::format( " Decide to branch if N is {}.", _uVal ).c_str() );
				break;
			}
			case 0 : {
				if constexpr ( _uVal == 0 ) {
					lsn::DebugA( " Decide to branch always." );
				}
				else {
					lsn::DebugA( " Decide to branch never." );
				}
				break;
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_UPDATE_PC;

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * 2nd cycle of branch instructions. Fetches opcode of next instruction and performs the check to decide which cycle comes next (or to end the instruction).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle1_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
		rCpu.m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Read PC:PB\tStore as Operand. Address = i16(i8(Operand.L)) + PC, BoundaryCrossed = Address.H != PC.H. If not branching or not BoundaryCrossed, poll interrupts." );
		}
		else {
			lsn::DebugA( "Read PC:PB\tStore as Operand. Address = i16(i8(Operand.L)) + PC. If not branching, poll interrupts." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		rCpu.m_fsState.ui16PcModify = 1;

		if ( !rCpu.m_fsState.bTakeJump ) {
			LSN_FINISH_INST( true );
		}
		else {
			rCpu.m_fsState.rRegs.ui16Pc += rCpu.m_fsState.ui16PcModify;
			rCpu.m_fsState.ui16PcModify = 0;
			rCpu.m_fsState.ui16Address = static_cast<int16_t>(static_cast<int8_t>(rCpu.m_fsState.ui8Operand[0])) + rCpu.m_fsState.rRegs.ui16Pc;

			rCpu.m_fsState.bBoundaryCrossed = rCpu.m_fsState.ui8Address[1] != rCpu.m_fsState.rRegs.ui8Pc[1];
			if ( !rCpu.m_fsState.bBoundaryCrossed && rCpu.m_fsState.bEmulationMode ) {
				LSN_CHECK_INTERRUPTS;
			}

			LSN_NEXT_FUNCTION;
		}

		//LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * 3rd cycle of branch instructions. Increases PC and skips to end if not branching.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tInc. PC. If not branching, end (next half-cycle is 4.2)." );
		}
		else {
			lsn::DebugA( "\tInc. PC. If not branching, end (next half-cycle is 3.2)." );
		}
#endif	// #ifdef LSN_CYCLES_DOC
		LSN_UPDATE_PC;

		if ( !rCpu.m_fsState.bTakeJump ) {
			BeginInst<true, false, false>( _prCpu );
		}
		else {
			LSN_NEXT_FUNCTION;

			LSN_INSTR_END_PHI2;
		}
	}

	/**
	 * 2nd cycle of branch instructions. Calculates target address if not branching.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle2_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if ( !rCpu.m_fsState.bEmulationMode ) {
			LSN_CHECK_INTERRUPTS;
		}

#ifdef LSN_CYCLES_DOC
		if ( !rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPoll interrupts." );
		}
#endif	// #ifdef LSN_CYCLES_DOC
	
		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle3( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui8Pc[0] = rCpu.m_fsState.ui8Address[0];

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet PC.L to Address.L. If not BoundaryCrossed, end (next half-cycle is 4.2)." );
#endif	// #ifdef LSN_CYCLES_DOC

		if ( !rCpu.m_fsState.bBoundaryCrossed ) {
			BeginInst<true, false, false>( _prCpu );
		}
		else {
			LSN_NEXT_FUNCTION;

			LSN_INSTR_END_PHI1;
		}
	}

	/**
	 * 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle3_Native( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet PC to Address." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
		if ( rCpu.m_fsState.bTakeJump ) {
			rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Address;
		}

		/*LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;*/
	}

	/**
	 * 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle3_Phi2( CRicoh5A22 * _prCpu ) {
		LSN_FINISH_INST( true );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tPoll interrupts." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * 4th cycle of branch instructions. Page boundary was crossed.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Branch_Cycle4( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet PC.H to Address.H" );
#endif	// #ifdef LSN_CYCLES_DOC
		
		BeginInst<false, false, false>( _prCpu );
		//if ( rCpu.m_fsState.bTakeJump ) {
			rCpu.m_fsState.rRegs.ui8Pc[1] = rCpu.m_fsState.ui8Address[1];
		//}

		/*LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;*/
	}

	/**
	 * Final touches to BRK (copies m_fsState.ui16Address to m_fsState.rRegs.ui16Pc) and first cycle of the next instruction.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Brk_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		rCpu.m_bBrkIsReset = false;
		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Address;
		rCpu.m_fsState.rRegs.ui8Pb = 0;
		rCpu.m_fsState.bAllowWritingToPc = true;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tEnable writes to PC (disabled by NMI/IRQ). Copy Address to PC. Set PB to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs BRL (Branch Long). Adds 16-bit m_fsState.ui16Operand to m_fsState.rRegs.ui16Pc.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Brl_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui16Pc += rCpu.m_fsState.ui16Operand;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tPerform PC += Operand." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Clears the carry bit.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Clc_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<C(), false>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the C flag to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Clears the decimal flag (D).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Cld_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<D(), false>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the D flag to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Clears the IRQ flag.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Cli_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<I(), false>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the I flag to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Clears the overflow flag (V).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Clv_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<V(), false>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the V flag to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs A - Operand (comparison). Sets C, N, and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Cmp_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			Cmp( _prCpu, rCpu.m_fsState.rRegs.ui8A[0], rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			Cmp( _prCpu, rCpu.m_fsState.rRegs.ui16A, rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );

		if constexpr ( _bIncPc ) {
			lsn::DebugA( "Inc. PC. " );
		}
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C flag based off (A.L >= Operand.L), set Z flag based off (A.L == Operand.L), and set N flag based off ((A.L - Operand.L) & $80) != 0." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C flag based off (A.L >= Operand.L), set Z flag based off (A.L == Operand.L), and set N flag based off ((A.L - Operand.L) & $80) != 0, otherwise "
				"set C flag based off (A >= Operand), set Z flag based off (A == Operand), and set N flag based off ((A - Operand) & $8000) != 0." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * Copies m_fsState.ui8Operand[0] to m_fsState.rRegs.ui8Db.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Copy_Operand_To_Db( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui8Db = rCpu.m_fsState.ui8Operand[0];

		LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tInc. PC. Set DB to Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Copies m_fsState.ui8Operand[0] to Status with a mask.
	 * 
	 * \tparam _ui8Mask The mask to apply.
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	template <uint8_t _ui8Mask>
	inline void CRicoh5A22::Copy_Operand_To_Status_Mask( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui8Status = (rCpu.m_fsState.ui8Operand[0] & ~_ui8Mask) | (rCpu.m_fsState.rRegs.ui8Status & _ui8Mask);

#ifdef LSN_CYCLES_DOC
		if constexpr ( _ui8Mask != 0x00 ) {
			lsn::DebugA( std::format( "\tSet P to ((Operand.L & ~${:02X} ) | (P & ${:02X})).", _ui8Mask, _ui8Mask ).c_str() );
		}
		else {
			lsn::DebugA( "\tSet P to Operand." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Copies from the vector to PC.h.
	 * 
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Copy_Vector_To_Pc_H_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.vBrkVector + 1, rCpu.m_fsState.ui8Address[1], rCpu.m_ui8Speed );

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
			
	/**
	 * Copies from the vector to PC.l.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Copy_Vector_To_Pc_L_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.vBrkVector, rCpu.m_fsState.ui8Address[0], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read Vector\tStore to Address.L." );
#endif // #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}
	
	/**
	 * Performs X - Operand (comparison). Sets C, N, and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Cpx_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			Cmp( _prCpu, rCpu.m_fsState.rRegs.ui8X[0], rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			Cmp( _prCpu, rCpu.m_fsState.rRegs.ui16X, rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );

		if constexpr ( _bIncPc ) {
			lsn::DebugA( "Inc. PC. " );
		}

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C flag based off (X.L >= Operand.L), set Z flag based off (X.L == Operand.L), and set N flag based off ((X.L - Operand.L) & $80) != 0." );
		}
		else {
			lsn::DebugA( "If X flag is set, set C flag based off (X.L >= Operand.L), set Z flag based off (X.L == Operand.L), and set N flag based off ((X.L - Operand.L) & $80) != 0, otherwise "
				"set C flag based off (X >= Operand), set Z flag based off (X == Operand), and set N flag based off ((X - Operand) & $8000) != 0." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * Performs Y - Operand (comparison). Sets C, N, and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Cpy_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			Cmp( _prCpu, rCpu.m_fsState.rRegs.ui8Y[0], rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			Cmp( _prCpu, rCpu.m_fsState.rRegs.ui16Y, rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );

		if constexpr ( _bIncPc ) {
			lsn::DebugA( "Inc. PC. " );
		}

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C flag based off (Y.L >= Operand.L), set Z flag based off (Y.L == Operand.L), and set N flag based off ((Y.L - Operand.L) & $80) != 0." );
		}
		else {
			lsn::DebugA( "If X flag is set, set C flag based off (Y.L >= Operand.L), set Z flag based off (Y.L == Operand.L), and set N flag based off ((Y.L - Operand.L) & $80) != 0, otherwise "
				"set C flag based off (Y >= Operand), set Z flag based off (Y == Operand), and set N flag based off ((Y - Operand) & $8000) != 0." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * Performs A--. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::DecOnA_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			--rCpu.m_fsState.rRegs.ui8A[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			--rCpu.m_fsState.rRegs.ui16A;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform A.L -= 1, set N based off (A.L & $80), set Z based off A.L." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, perform A.L -= 1, set N based off (A.L & $80), and set Z based off A.L, otherwise perform A -= 1, set N based off (A.H & $80), and set Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Operand--. Sets N and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Dec( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			--rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.ui8Operand[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			--rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.ui8Operand[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Perform Operand.L -= 1, set N based off (Operand.L & $80), and Z based off Operand.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, perform Operand.L -= 1, set N based off (Operand.L & $80), and set Z based off Operand.L, otherwise perform Operand - 1, set N based off (Operand.H & $80), and set Z based off Operand." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs X--. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Dex_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			--rCpu.m_fsState.rRegs.ui8X[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8X[0] );
		}
		else {
			--rCpu.m_fsState.rRegs.ui16X;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16X );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform X.L -= 1, set N based off (X.L & $80), set Z based off X.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform X.L -= 1, set N based off (X.L & $80), and set Z based off X.L, otherwise perform X -= 1, set N based off (X.H & $80), and set Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Y--. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Dey_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			--rCpu.m_fsState.rRegs.ui8Y[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8Y[0] );
		}
		else {
			--rCpu.m_fsState.rRegs.ui16Y;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16Y );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform Y.L -= 1, set N based off (Y.L & $80), set Z based off Y.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform Y.L -= 1, set N based off (Y.L & $80), and set Z based off Y.L, otherwise perform Y -= 1, set N based off (Y.H & $80), and set Z based off Y." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs EOR with m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Eor_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			rCpu.m_fsState.rRegs.ui8A[0] ^= rCpu.m_fsState.ui8Operand[0];
		}
		else {
			rCpu.m_fsState.rRegs.ui16A ^= rCpu.m_fsState.ui16Operand;
		}

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
		if constexpr ( _bIncPc ) {
			lsn::DebugA( "Inc. PC. " );
		}

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Perform A ^= Operand. Set N based off (A.L & $80) and Z based off A.L." );
		}
		else {
			lsn::DebugA( "Perform A ^= Operand. If M flag is set, set N based off (A.L & $80) and Z based off A.L, otherwise set N based off (A.H & $80) and Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * Fetches m_fsState.ui8Bank and increments PC.
	 * 
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Bank_IncPc_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
		rCpu.m_fsState.ui16PcModify = 1;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStores as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the current opcode and increments PC.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Fetch_Opcode_IncPc_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		uint8_t ui8Op;
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, ui8Op, rCpu.m_ui8Speed );

#ifdef LSN_CPU_VERIFY
		rCpu.m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Store as OpCode." );
#endif	// #ifdef LSN_CYCLES_DOC
#else
		if LSN_UNLIKELY( rCpu.m_bHandleNmi || rCpu.m_bHandleIrq || rCpu.m_bIsReset ) {
			ui8Op = 0;
			rCpu.m_fsState.bPushB = false;
			rCpu.m_fsState.ui16PcModify = 0;
			rCpu.m_fsState.bAllowWritingToPc = false;
		}
		else {
			rCpu.m_fsState.bPushB = true;
			rCpu.m_fsState.ui16PcModify = 1;
		}
#endif	// #ifdef LSN_CPU_VERIFY
		rCpu.m_fsState.ui16OpCode = ui8Op;
		rCpu.m_fsState.pfCurInstruction = rCpu.m_iInstructionSet[rCpu.m_fsState.ui16OpCode].pfHandler[rCpu.m_fsState.bEmulationMode];

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches m_fsState.ui8Operand[1] and increments the PC.
	 * 
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Operand_High_IncPc( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
		rCpu.m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the next operand and discards without incrementing PC, then schedules PC -= 1
	 * for the next PHI1 (so following pushes see PC-1).
	 *
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Operand_Discard_DecPc_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );

		// Back PC up by 1 on the next PHI1.
		rCpu.m_fsState.ui16PcModify = uint16_t( -1 );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tDiscard." );
#endif	// #ifdef LSN_CYCLES_DOC

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
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bEndInstr>
	inline void CRicoh5A22::Fetch_Operand_Discard_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tDiscard." );
#endif	// #ifdef LSN_CYCLES_DOC
		
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
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
		rCpu.m_fsState.ui16PcModify = 1;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Operand." );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If M flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bSkipOnDl>
	inline void CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
		rCpu.m_fsState.ui16PcModify = 1;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Operand." );
#endif	// #ifdef LSN_CYCLES_DOC


		if constexpr ( _bSkipOnDl ) {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If D.L is 0, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches to m_fsState.ui8Address[1] or m_fsState.ui8Pointer[1] and increments PC.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bEndInstr>
	void CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		uint8_t ui8Op;
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, ui8Op, rCpu.m_ui8Speed );
		if constexpr ( _bTo == LSN_TO_A ) {
			rCpu.m_fsState.ui8Address[1] = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB\tStore as Address.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.ui8Pointer[1] = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB\tStore as Pointer.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		rCpu.m_fsState.ui16PcModify = 1;

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
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bEndInstr>
	void CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		uint8_t ui8Op;
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, ui8Op, rCpu.m_ui8Speed );
		if constexpr ( _bTo == LSN_TO_A ) {
			rCpu.m_fsState.ui16Address = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB\tStore as Address." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.ui16Pointer = ui8Op;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read PC:PB\tStore as Pointer." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		rCpu.m_fsState.ui16PcModify = 1;

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fetches the source bank byte for MVP/MVN and sets DB to the destination bank.
	 *
	 * Destination bank is already in m_fsState.ui8Pointer[0] (Pointer.L).
	 * Source bank is stored into m_fsState.ui8Pointer[1] (Pointer.H).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Fetch_SrcBank_SetDb_IncPc_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16Pc, rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_fsState.ui8Pointer[1], rCpu.m_ui8Speed );
		rCpu.m_fsState.rRegs.ui8Db = rCpu.m_fsState.ui8Pointer[0];
		rCpu.m_fsState.ui16PcModify = 1;

	#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read PC:PB\tStore as Pointer.H. Set DB to Pointer.L." );
	#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Fixes the high bit of m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo>	
	inline void CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );
		if constexpr ( _bTo == LSN_TO_A ) {
			rCpu.m_fsState.ui8Address[1] = rCpu.m_fsState.ui8Pointer[1];
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tAddress.H = Pointer.H (fixes high byte of address)." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.ui8Pointer[1] = rCpu.m_fsState.ui8Address[1];
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tPointer.H = Address.H (fixes high byte of address)." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs Operand++. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Inc( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			rCpu.m_fsState.ui8Operand[0]++;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.ui8Operand[0] == 0 );
		}
		else {
			rCpu.m_fsState.ui16Operand++;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui16Operand & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.ui16Operand == 0 );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform Operand.L += 1, set N based off (Operand.L & $80), set Z based off Operand.L." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, perform Operand.L += 1, set N based off (Operand.L & $80), and set Z based off Operand.L, otherwise perform Operand += 1, set N based off (Operand.H & $80), and set Z based off Operand." );
		}
#endif  // #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs A++. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::IncOnA_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			++rCpu.m_fsState.rRegs.ui8A[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			++rCpu.m_fsState.rRegs.ui16A;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform A.L += 1, set N based off (A.L & $80), set Z based off A.L." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, perform A.L += 1, set N based off (A.L & $80), and set Z based off A.L, otherwise perform A += 1, set N based off (A.H & $80), and set Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs X++. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Inx_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			++rCpu.m_fsState.rRegs.ui8X[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8X[0] );
		}
		else {
			++rCpu.m_fsState.rRegs.ui16X;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16X );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform X.L += 1, set N based off (X.L & $80), set Z based off X.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform X.L += 1, set N based off (X.L & $80), and set Z based off X.L, otherwise perform X += 1, set N based off (X.H & $80), and set Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Y++. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Iny_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			++rCpu.m_fsState.rRegs.ui8Y[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8Y[0] );
		}
		else {
			++rCpu.m_fsState.rRegs.ui16Y;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16Y );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform Y.L += 1, set N based off (Y.L & $80), set Z based off Y.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform Y.L += 1, set N based off (Y.L & $80), and set Z based off Y.L, otherwise perform Y += 1, set N based off (Y.H & $80), and set Z based off Y." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs JML [abs] (Indirect Long). Sets PC and PB.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Jml_Absolute_Indirect_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Operand;
		rCpu.m_fsState.rRegs.ui8Pb = rCpu.m_fsState.ui8Bank;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet PC to Operand. Set PB to Bank." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs PC = Address (Absolute JMP).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Jmp_Absolute_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		rCpu.m_fsState.ui16PcModify = 0;

		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Address;

	#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet PC to Address." );
	#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Final touches to JSL (applies pending PC/S updates, then loads PB:PC from Address+Bank)
	 * and begins the next instruction.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Jsl_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			if ( int16_t( rCpu.m_fsState.ui16SModify ) < 0 ) {
				lsn::DebugA( (" Dec. S.L by " + std::to_string( -int16_t( rCpu.m_fsState.ui16SModify ) ) + " and set S.H to 1. ").c_str() );
			}
			else if ( int16_t( rCpu.m_fsState.ui16SModify ) > 0 ) {
				lsn::DebugA( (" Inc. S.L by " + std::to_string( int16_t( rCpu.m_fsState.ui16SModify ) ) + " and set S.H to 1. ").c_str() );
			}
		}
		else {
			if ( int16_t( rCpu.m_fsState.ui16SModify ) < 0 ) {
				lsn::DebugA( (" Dec. S by " + std::to_string( -int16_t( rCpu.m_fsState.ui16SModify ) ) + ". ").c_str() );
			}
			else if ( int16_t( rCpu.m_fsState.ui16SModify ) > 0 ) {
				lsn::DebugA( (" Inc. S by " + std::to_string( int16_t( rCpu.m_fsState.ui16SModify ) ) + ". ").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC
		LSN_UPDATE_S;

		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Address;
		rCpu.m_fsState.rRegs.ui8Pb = rCpu.m_fsState.ui8Bank;
		rCpu.m_fsState.ui16PcModify = 0;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( " Copy Address to PC. Copy Bank to PB." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Finalizes JSR abs: applies the accumulated S modification, sets PC to the fetched absolute target,
	 * and begins the next instruction.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Jsr_Absolute_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
		if ( int16_t( rCpu.m_fsState.ui16SModify ) < 0 ) {
			lsn::DebugA( ("\tDec. S by " + std::to_string( -int16_t( rCpu.m_fsState.ui16SModify ) ) + ". ").c_str() );
		}
		else if ( int16_t( rCpu.m_fsState.ui16SModify ) > 0 ) {
			lsn::DebugA( ("\tInc. S by " + std::to_string( int16_t( rCpu.m_fsState.ui16SModify ) ) + ". ").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC
		LSN_UPDATE_S;

		// Start next instruction bookkeeping, then redirect PC to the target.
		BeginInst<false, false, false>( _prCpu );
		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Address;
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Perform PC = Address." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs Operand >>= 1. Sets C, N, and Z, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Lsr( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x01) != 0 );

			rCpu.m_fsState.ui8Operand[0] >>= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui16Operand & 0x0001) != 0 );

			rCpu.m_fsState.ui16Operand >>= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui16Operand & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C based off (Operand.L & $01). Perform Operand.L >>= 1. Set N based off (Operand.L & $80) and Z based off Operand.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C based off (Operand.L & $01), perform Operand.L >>= 1, and set N based off (Operand.L & $80) and Z based off Operand.L, otherwise set C based off (Operand.L & $01), perform Operand >>= 1, and set N based off (Operand.H & $80) and Z based off Operand." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs A = Operand. Sets N and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Lda_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			rCpu.m_fsState.rRegs.ui8A[0] = rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] == 0 );
		}
		else {
			rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16A == 0 );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set A.L to Operand.L. Set N based off (A.L & $80). Set Z based off A.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set A.L to Operand.L, set N based off (A.L & $80), and set Z based off A.L, otherwise set A to Operand, set N based off (A.H & $80), and set Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs X = Operand. Sets N and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Ldx_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[0] = rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8X[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] == 0 );
		}
		else {
			rCpu.m_fsState.rRegs.ui16X = rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16X & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16X == 0 );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set X.L to Operand.L. Set N based off (X.L & $80). Set Z based off X.L." );
		}
		else {
			lsn::DebugA( "If X flag is set, set X.L to Operand.L, set N based off (X.L & $80), and set Z based off X.L, otherwise set X to Operand, set N based off (X.H & $80), and set Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Y = Operand. Sets N and Z.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Ldy_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8Y[0] = rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8Y[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[0] == 0 );
		}
		else {
			rCpu.m_fsState.rRegs.ui16Y = rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16Y & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16Y == 0 );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set Y.L to Operand.L. Set N based off (Y.L & $80). Set Z based off Y.L." );
		}
		else {
			lsn::DebugA( "If X flag is set, set Y.L to Operand.L, set N based off (Y.L & $80), and set Z based off Y.L, otherwise set Y to Operand, set N based off (Y.H & $80), and set Z based off Y." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs A >>= 1. Sets C, N, and Z, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::LsrOnA_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x01) != 0 );

			rCpu.m_fsState.rRegs.ui8A[0] >>= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & 0x0001) != 0 );

			rCpu.m_fsState.rRegs.ui16A >>= 1;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C based off (A.L & $01). Perform A.L >>= 1. Set N based off (A.L & $80) and Z based off A.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C based off (A.L & $01), perform A.L >>= 1, and set N based off (A.L & $80) and Z based off A.L, otherwise set C based off (A.L & $01), perform A >>= 1, and set N based off (A.H & $80) and Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Adjusts A/X/Y for MVP and adjusts m_fsState.rRegs.ui16Pc by either 0 (done) or -3 (repeat).
	 *
	 * Notes:
	 * - A is treated as 16-bit counter for block moves.
	 * - If X flag is set, X/Y are adjusted as 8-bit (stay within page 0).
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	template <int16_t _i16AddrAdj>
	inline void CRicoh5A22::MvX_Adjust_And_SetRepeat( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		// A is the 16-bit counter for block moves.
		--rCpu.m_fsState.rRegs.ui16A;

		// X/Y obey the X flag width.
		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[0] += uint8_t( _i16AddrAdj );
			rCpu.m_fsState.rRegs.ui8Y[0] += uint8_t( _i16AddrAdj );
		}
		else {
			rCpu.m_fsState.rRegs.ui16X += uint16_t( _i16AddrAdj );
			rCpu.m_fsState.rRegs.ui16Y += uint16_t( _i16AddrAdj );
		}

		// If A != $FFFF, repeat by rewinding PC to opcode (3-byte instruction).
		if LSN_LIKELY( rCpu.m_fsState.rRegs.ui16A != 0xFFFF ) {
			rCpu.m_fsState.rRegs.ui16Pc -= 3;
		}
		rCpu.m_fsState.ui16PcModify = 0;

#ifdef LSN_CYCLES_DOC
		if constexpr ( _i16AddrAdj > 0 ) {
			lsn::DebugA( "\tPerform A -= 1. If X flag is set, perform X.L += 1 and Y.L += 1, otherwise perform X += 1 and Y += 1. If A is not $FFFF, perform PC -= 3." );
		}
		else {
			lsn::DebugA( "\tPerform A -= 1. If X flag is set, perform X.L -= 1 and Y.L -= 1, otherwise perform X -= 1 and Y -= 1. If A is not $FFFF, perform PC -= 3." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs NOP.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Nop_BeginInst( CRicoh5A22 * _prCpu ) {
		LSN_INSTR_START_PHI1( true );

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Generic null operation.
	 * 
	 * \tparam _ctReadWriteNull The cycle read/write/neither type.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bBeginInstr If true, BeginInst() is called.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <CRicoh5A22::LSN_CYCLE_TYPE _ctReadWriteNull, bool _bIncPc, bool _bAdjS, bool _bBeginInstr>
	inline void CRicoh5A22::Null( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bBeginInstr ) {
			BeginInst<_bIncPc, _bAdjS>( _prCpu );
		}
		else {
#ifdef LSN_CYCLES_DOC
			std::string sDebug = "\t";
#endif	// #ifdef LSN_CYCLES_DOC
			LSN_INSTR_START_PHI1( _ctReadWriteNull );

			if constexpr ( _bIncPc ) {
#ifdef LSN_CYCLES_DOC
				if ( int16_t( _prCpu->m_fsState.ui16PcModify ) < 0 ) {
					sDebug += "Dec. PC. ";
				}
				else {
					sDebug += "Inc. PC. ";
				}
#endif	// #ifdef LSN_CYCLES_DOC
				LSN_UPDATE_PC;
			}
			if constexpr ( _bAdjS ) {
#ifdef LSN_CYCLES_DOC
				if LSN_UNLIKELY( _prCpu->m_fsState.bEmulationMode ) {
					if ( int16_t( _prCpu->m_fsState.ui16SModify ) < 0 ) {
						sDebug += "Dec. S.L by " + std::to_string( -int16_t( _prCpu->m_fsState.ui16SModify ) ) + " and set S.H to 1. ";
					}
					else if ( int16_t( _prCpu->m_fsState.ui16SModify ) > 0 ) {
						sDebug += "Inc. S.L by " + std::to_string( int16_t( _prCpu->m_fsState.ui16SModify ) ) + " and set S.H to 1. ";
					}
				}
				else {
					if ( int16_t( _prCpu->m_fsState.ui16SModify ) < 0 ) {
						sDebug += "Dec. S by " + std::to_string( -int16_t( _prCpu->m_fsState.ui16SModify ) ) + ". ";
					}
					else if ( int16_t( _prCpu->m_fsState.ui16SModify ) > 0 ) {
						sDebug += "Inc. S by " + std::to_string( int16_t( _prCpu->m_fsState.ui16SModify ) ) + ". ";
					}
				}
#endif	// #ifdef LSN_CYCLES_DOC
				LSN_UPDATE_S;
			}

			LSN_NEXT_FUNCTION;

			LSN_INSTR_END_PHI1;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( sDebug.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC
		}
	}

	/**
	 * Generic null operation on PHI2. Sets the bus access speed to Fast.
	 * 
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _i8SOff If not INT8_MIN, S is scheduled to be adjusted by the given amount on the next PHI1.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bSkipIfM, int8_t _i8SOff, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Null_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		rCpu.m_ui8Speed = rCpu.m_ui8FastDiv;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _i8SOff != INT8_MIN ) {
			rCpu.m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) );
		}
		
		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}
			LSN_NEXT_FUNCTION;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If M flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}
			LSN_NEXT_FUNCTION;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Generic null operation for BRK that can be either a read or write, depending on RESET.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bBeginInstr If true, BeginInst() is called.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc, bool _bAdjS, bool _bBeginInstr>
	inline void CRicoh5A22::Null_RorW( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bBeginInstr ) {
			BeginInst<_bIncPc, _bAdjS>( _prCpu );
		}
		else {
#ifdef LSN_CYCLES_DOC
			std::string sDebug = "\t";
#endif	// #ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_bIsReset ) {
				LSN_INSTR_START_PHI1( true );
			}
			else {
				LSN_INSTR_START_PHI1( false );
			}

			if constexpr ( _bIncPc ) {
				LSN_UPDATE_PC;
#ifdef LSN_CYCLES_DOC
				sDebug += "Inc. PC. ";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			if constexpr ( _bAdjS ) {
				LSN_UPDATE_S;
#ifdef LSN_CYCLES_DOC
				if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
					if ( rCpu.m_fsState.ui16SModify < 0 ) {
						sDebug += "Dec. S.L by " + std::to_string( -rCpu.m_fsState.ui16SModify ) + " and set S.H to 1. ";
					}
					else if ( rCpu.m_fsState.ui16SModify > 0 ) {
						sDebug += "Inc. S.L by " + std::to_string( rCpu.m_fsState.ui16SModify ) + " and set S.H to 1. ";
					}
				}
				else {
					if ( rCpu.m_fsState.ui16SModify < 0 ) {
						sDebug += "Dec. S by " + std::to_string( -rCpu.m_fsState.ui16SModify ) + ". ";
					}
					else if ( rCpu.m_fsState.ui16SModify > 0 ) {
						sDebug += "Inc. S by " + std::to_string( rCpu.m_fsState.ui16SModify ) + ". ";
					}
				}
#endif	// #ifdef LSN_CYCLES_DOC
			}

			LSN_NEXT_FUNCTION;

			LSN_INSTR_END_PHI1;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( sDebug.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC
		}
	}

	/**
	 * Performs ORA with m_fsState.ui8Operand[0].
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Ora_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui16A |= rCpu.m_fsState.ui16Operand;

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
			if constexpr ( _bIncPc ) {
				lsn::DebugA( "Inc. PC. " );
			}

			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( "Perform A |= Operand. Set N based off (A.L & $80) and Z based off A.L." );
			}
			else {
				lsn::DebugA( "Perform A |= Operand. If M flag is set, set N based off (A.L & $80) and Z based off A.L, otherwise set N based off (A.H & $80) and Z based off A." );
			}

			
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<_bIncPc, false, false>( _prCpu );
	}

	/**
	 * Increases m_fsState.rRegs.ui16Pc and then sets m_fsState.ui16Operand to m_fsState.ui16Operand + m_fsState.rRegs.ui16Pc.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Per_IncPc( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		LSN_UPDATE_PC;

		rCpu.m_fsState.ui16Operand += rCpu.m_fsState.rRegs.ui16Pc;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tInc. PC. Set Operand to Operand + PC." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Sets m_fsState.ui8Operand[0] to the status byte with Break (X) and Reserved (M) set.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Php( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		rCpu.m_fsState.ui8Operand[0] = rCpu.m_fsState.rRegs.ui8Status;
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			SetBit<X() | M(), true>( rCpu.m_fsState.ui8Operand[0] );
		}

#ifdef LSN_CYCLES_DOC
		if ( !rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet Operand.L to P." );
		}
		else {
			lsn::DebugA( "\tSet Operand.L to P with X and M flags set." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Pull to A. Sets N and Z based on A.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Pla_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			// 8-bit pull.
			rCpu.m_fsState.rRegs.ui8A[0] = rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] == 0 );
		}
		else {
			// 16-bit pull.
			rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16A == 0 );
		}

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet A.L to Operand.L. Set N based off (A.L & $80) and Z based off A.L." );
		}
		else {
			lsn::DebugA( " If M flag is set, set A.L to Operand.L and set N based off (A.L & $80) and Z based off A.L, otherwise set A to Operand and set N based off (A.H & $80) and Z based off A." );
		}
#endif	// LSN_CYCLES_DOC
	}

	/**
	 * Pull to DB, updates N and Z based on DB.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Plb_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui8Db = rCpu.m_fsState.ui8Bank;

		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8Db & 0x80) != 0 );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Db == 0 );

		BeginInst<false, false, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet DB to Bank, set N based off (DB & $80), and set Z based off DB." );
#endif	// #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Pull to D. Sets N and Z based on D.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Pld_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui16D = rCpu.m_fsState.ui16Operand;

		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8D[1] & 0x80) != 0 );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16D == 0 );

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( " Set D to Operand. Set N based off (D.H & $80). Set Z based off D." );
#endif	// LSN_CYCLES_DOC
	}

	/**
	 * Performs PLP and begins the next instruction.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Plp_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui8Status = rCpu.m_fsState.ui8Operand[0];
		rCpu.m_fsState.ui16SModify = 0;

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.rRegs.ui8Status |= (X() | M());
		}

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode || (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[1] = 0;
			rCpu.m_fsState.rRegs.ui8Y[1] = 0;
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tP = Operand.L, set X and M flags, set X.H and Y.H to 0." );
		}
		else {
			lsn::DebugA( "\tP = Operand.L, set X.H and Y.H to 0 if X flag is set." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Pulls X from the stack. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Plx_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[0] = rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8X[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] == 0 );
		}
		else {
			rCpu.m_fsState.rRegs.ui16X = rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16X & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16X == 0 );
		}

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet X.L to Operand.L, set N based off (X.L & $80), and set Z based off X.L." );
		}
		else {
			lsn::DebugA( " If X flag is set, set X.L to Operand.L, set N based off (X.L & $80), and Z based off X.L, otherwise set X to Operand, set N based off (X.H & $80), and Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Pulls Y from the stack.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Ply_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8Y[0] = rCpu.m_fsState.ui8Operand[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8Y[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[0] == 0 );
		}
		else {
			rCpu.m_fsState.rRegs.ui16Y = rCpu.m_fsState.ui16Operand;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16Y & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui16Y == 0 );
		}

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( " Set Y.L to Operand.L. Set N based off (Y.L & $80). Set Z based off Y.L." );
		}
		else {
			lsn::DebugA( " If X flag is set, set Y.L to Operand.L, set N based off (Y.L & $80), and Z based off Y.L, otherwise set Y to Operand, set N based off (Y.H & $80), and Z based off Y." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8A[1].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_A_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH( rCpu.m_fsState.rRegs.ui8A[1], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush A.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush A.H onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8A[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_A_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8A[0], rCpu.m_ui8Speed );

		// Needs to use
		//	((0x100 | rCpu.m_fsState.rRegs.ui8S[0]) + _i8SOff)
		//	for the stack address??

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush A.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush A.L onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8D[1].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_D_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH( rCpu.m_fsState.rRegs.ui8D[1], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush D.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush D.H onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8D[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_D_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8D[0], rCpu.m_ui8Speed );

		// Needs to use
		//	((0x100 | rCpu.m_fsState.rRegs.ui8S[0]) + _i8SOff)
		//	for the stack address??

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush D.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush D.L onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Db.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial>
	inline void CRicoh5A22::Push_Db_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bSpecial ) {
			LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Db, rCpu.m_ui8Speed );
		}
		else {
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Db, rCpu.m_ui8Speed );
		}

#ifdef LSN_CYCLES_DOC
		if constexpr ( _bSpecial ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush DB onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush DB onto stack.").c_str() );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush DB onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush DB onto stack.").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.ui8Operand[1].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_Operand_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH_SPECIAL( rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush Operand.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush Operand.H onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.ui8Operand[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_Operand_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH_SPECIAL( rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush Operand.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush Operand.L onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

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
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial>
	inline void CRicoh5A22::Push_Pb_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bSpecial ) {
			LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_ui8Speed );
		}
		else {
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_ui8Speed );
		}

#ifdef LSN_CYCLES_DOC
		if constexpr ( _bSpecial ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush PB onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PB onto stack.").c_str() );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PB onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PB onto stack.").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

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
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_Pb_Brk_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if LSN_UNLIKELY( rCpu.m_bBrkIsReset ) {
			uint8_t ui8Tmp;
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.bEmulationMode ? (0x100 | uint8_t( rCpu.m_fsState.rRegs.ui8S[0] + _i8SOff )) : (rCpu.m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, rCpu.m_ui8Speed );
			rCpu.m_fsState.ui16SModify = uint16_t( -1 + _i8SOff );
		}
		else {
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Pb, rCpu.m_ui8Speed );
		}
#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PB onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PB onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pc[1] with the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bSpecial>
	inline void CRicoh5A22::Push_Pc_High_Brk_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if LSN_UNLIKELY( rCpu.m_bBrkIsReset ) {
			uint8_t ui8Tmp;
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.bEmulationMode ? (0x100 | uint8_t( rCpu.m_fsState.rRegs.ui8S[0] + _i8SOff )) : (rCpu.m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, rCpu.m_ui8Speed );
			rCpu.m_fsState.ui16SModify = uint16_t( int8_t( -1 ) + _i8SOff );
		}
		else {
			if constexpr ( _bSpecial ) {
				LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Pc[1], rCpu.m_ui8Speed );
			}
			else {
				LSN_PUSH( rCpu.m_fsState.rRegs.ui8Pc[1], rCpu.m_ui8Speed );
			}
		}
#ifdef LSN_CYCLES_DOC
		if constexpr ( _bSpecial ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PC.H onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pc[1] with the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bSpecial>
	inline void CRicoh5A22::Push_Pc_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bSpecial ) {
			LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Pc[1], rCpu.m_ui8Speed );
		}
		else {
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Pc[1], rCpu.m_ui8Speed );
		}
#ifdef LSN_CYCLES_DOC
		if constexpr ( _bSpecial ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PC.H onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.H onto stack.").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pc[0] with the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial>
	inline void CRicoh5A22::Push_Pc_Low_Brk_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if LSN_UNLIKELY( rCpu.m_bBrkIsReset ) {
			uint8_t ui8Tmp;
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.bEmulationMode ? (0x100 | uint8_t( rCpu.m_fsState.rRegs.ui8S[0] + _i8SOff )) : (rCpu.m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, rCpu.m_ui8Speed );
			rCpu.m_fsState.ui16SModify = uint16_t( int8_t( -1 ) + _i8SOff );
		}
		else {
			if constexpr ( _bSpecial ) {
				LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Pc[0], rCpu.m_ui8Speed );
			}
			else {
				LSN_PUSH( rCpu.m_fsState.rRegs.ui8Pc[0], rCpu.m_ui8Speed );
			}
		}
#ifdef LSN_CYCLES_DOC
		if constexpr ( _bSpecial ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PC.L onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Pc[0] with the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial>
	inline void CRicoh5A22::Push_Pc_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bSpecial ) {
			LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Pc[0], rCpu.m_ui8Speed );
		}
		else {
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Pc[0], rCpu.m_ui8Speed );
		}
#ifdef LSN_CYCLES_DOC
		if constexpr ( _bSpecial ) {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
			}
		}
		else {
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush PC.L onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush PC.L onto stack.").c_str() );
			}
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Status with or without B/X to the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bCop If this is the COP instruction, just do a normal push.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bCop>
	inline void CRicoh5A22::Push_S_Brk_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bCop ) {
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush P onto stack.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush P onto stack.").c_str() );
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			if LSN_UNLIKELY( rCpu.m_bBrkIsReset ) {
				uint8_t ui8Tmp;
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.bEmulationMode ? (0x100 | uint8_t( rCpu.m_fsState.rRegs.ui8S[0] + _i8SOff )) : (rCpu.m_fsState.rRegs.ui16S + _i8SOff), ui8Tmp, rCpu.m_ui8Speed );
				rCpu.m_fsState.ui16SModify = uint16_t( int8_t( -1 ) + _i8SOff );
			}
			else {
				if ( rCpu.m_fsState.bPushB ) {
					LSN_PUSH( rCpu.m_fsState.rRegs.ui8Status | X(), rCpu.m_ui8Speed );
				}
				else {
					LSN_PUSH( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_ui8Speed );
				}
			}
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush P onto stack with B flag if software BRK.").c_str() );
			}
			else {
				lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush P onto stack with B flag if software BRK.").c_str() );
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Status with or without B/X to the given S offset.
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_S_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
			LSN_PUSH( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush P onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush P onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8X[1].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_X_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH( rCpu.m_fsState.rRegs.ui8X[1], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush X.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush X.H onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8X[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_X_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8X[0], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush X.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush X.L onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Y[1].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Push_Y_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH( rCpu.m_fsState.rRegs.ui8Y[1], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tPush Y.H onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush Y.H onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Pushes m_fsState.rRegs.ui8Y[0].
	 * 
	 * \tparam _i8SOff The offset from S to which to write the pushed value.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CRicoh5A22::Push_Y_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_PUSH_SPECIAL( rCpu.m_fsState.rRegs.ui8Y[0], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Write to ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tPush Y.L onto stack.").c_str() );
		}
		else {
			lsn::DebugA( ("Write to (S" + std::format( "{:+}", _i8SOff ) + ")\tPush Y.L onto stack.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Address[1] or m_fsState.ui8Pointer[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bBankWrap If true, the bank wraps (instead of carries) on addresses where + 1 crosses into a new bank.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bEndInstr, bool _bBankWrap>
	inline void CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if constexpr ( _bBankWrap ) {
				LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui8Pointer[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Address + 1:Bank\tStore as Address.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				uint32_t ui32Offset = rCpu.m_fsState.ui16Address + 1;
				LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, rCpu.m_fsState.ui8Bank + (ui32Offset >> 16), rCpu.m_fsState.ui8Pointer[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Address + 1:Bank (With Carry)\tStore as Address.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if constexpr ( _bBankWrap ) {
				LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui8Address[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Pointer + 1:Bank\tStore as Address.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				uint32_t ui32Offset = rCpu.m_fsState.ui16Pointer + 1;
				LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, rCpu.m_fsState.ui8Bank + (ui32Offset >> 16), rCpu.m_fsState.ui8Address[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Pointer + 1:Bank (With Carry)\tStore as Address.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
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
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Address[0] or m_fsState.ui8Pointer[0].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui8Pointer[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address:Bank\tStore as Address.L.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui8Address[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer:Bank\tStore as Address.L.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
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
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank and stores the result in m_fsState.ui8Operand[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_A ) {
			uint32_t ui32Offset = rCpu.m_fsState.ui16Address + 1;
			LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, rCpu.m_fsState.ui8Bank + (ui32Offset >> 16), rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Address + 1:Bank (With Carry)\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			uint32_t ui32Offset = rCpu.m_fsState.ui16Pointer + 1;
			LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, rCpu.m_fsState.ui8Bank + (ui32Offset >> 16), rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Pointer + 1:Bank (With Carry)\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address:Bank\tStore as Operand.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer:Bank\tStore as Operand.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If X flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
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
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.rRegs.ui8Db and stores the result in m_fsState.ui8Operand[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bBankWrap If true, the bank wraps (instead of carries) on addresses where + 1 crosses into a new bank.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bEndInstr, bool _bBankWrap>
	inline void CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if constexpr ( _bBankWrap ) {
				LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.rRegs.ui8Db, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Address + 1:DB\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				uint32_t ui32Offset = rCpu.m_fsState.ui16Address + 1;
				LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, rCpu.m_fsState.rRegs.ui8Db + (ui32Offset >> 16), rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Address + 1:DB (With Carry)\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if constexpr ( _bBankWrap ) {
				LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.rRegs.ui8Db, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Pointer + 1:DB\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				uint32_t ui32Offset = rCpu.m_fsState.ui16Pointer + 1;
				LSN_INSTR_START_PHI2_READ_BUSA( ui32Offset, rCpu.m_fsState.rRegs.ui8Db + (ui32Offset >> 16), rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Pointer + 1:DB (With Carry)\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
//		if constexpr ( _bFrom == LSN_FROM_A ) {
//			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Address + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
//#ifdef LSN_CYCLES_DOC
//			lsn::DebugA( "Read Address + 1:DB\tStore as Operand.H." );
//#endif	// #ifdef LSN_CYCLES_DOC
//		}
//		else {
//			LSN_INSTR_START_PHI2_READ_BUSA( m_fsState.ui16Pointer + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
//#ifdef LSN_CYCLES_DOC
//			lsn::DebugA( "Read Pointer + 1:DB\tStore as Operand.H." );
//#endif	// #ifdef LSN_CYCLES_DOC
//		}

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
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bFrom == LSN_FROM_A ) {
			LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.rRegs.ui8Db, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address:DB\tStore as Operand.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.rRegs.ui8Db, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer:DB\tStore as Operand.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		
		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If X flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
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
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads (and discards) a byte from the stack.
	 * 
	 * \tparam _i8SOff Offset from S to read.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff>
	inline void CRicoh5A22::Read_Stack_Discard_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		uint8_t ui8Tmp;
		const uint16_t ui16Addr = rCpu.m_fsState.bEmulationMode ?
			(0x100 | uint8_t( rCpu.m_fsState.rRegs.ui8S[0] + _i8SOff )) :
			uint16_t( rCpu.m_fsState.rRegs.ui16S + _i8SOff );

		LSN_INSTR_START_PHI2_READ0_BUSA( ui16Addr, ui8Tmp, rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Read u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tDiscard.").c_str() );
		}
		else {
			lsn::DebugA( ("Read (S" + std::format( "{:+}", _i8SOff ) + ")\tDiscard.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads the stack, stores in m_fsState.ui8Bank.
	 * 
	 * \tparam _i8SOff Offset from S to read.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_POP_SPECIAL is used instead of LSN_POP.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial>
	inline void CRicoh5A22::Read_Stack_To_Bank_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			LSN_POP_SPECIAL( rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
		}
		else {
			LSN_POP( rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( ("Read ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tStore as Bank.").c_str() );
		}
		else {
			lsn::DebugA( ("Read (S" + std::format( "{:+}", _i8SOff ) + ")\tStore as Bank.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads the stack with offset, stores in m_fsState.ui8Operand[1].
	 * 
	 * \tparam _i8SOff Offset from S to read.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_PUSH_SPECIAL is used instead of LSN_PUSH.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial>
	inline void CRicoh5A22::Read_Stack_To_Operand_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			if constexpr ( _bSpecial ) {
				LSN_POP_SPECIAL( rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
			}
			else {
				LSN_POP( rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
			}
		}
		else {
			LSN_POP( rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			if constexpr ( _bSpecial ) {
				lsn::DebugA( ("Read u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tStore as Operand.H.").c_str() );
			}
			else {
				lsn::DebugA( ("Read ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tStore as Operand.H.").c_str() );
			}
		}
		else {
			lsn::DebugA( ("Read (S" + std::format( "{:+}", _i8SOff ) + ")\tStore as Operand.H.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads the stack, stores in m_fsState.ui8Operand[0].
	 * 
	 * \tparam _i8SOff Offset from S to read.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSpecial If true, LSN_POP_SPECIAL is used instead of LSN_POP.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr, bool _bSpecial, bool _bSkipIfM, bool _bSkipIfX>
	inline void CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			if constexpr ( _bSpecial ) {
				LSN_POP_SPECIAL( rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );
			}
			else {
				LSN_POP( rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );
			}
		}
		else {
			LSN_POP( rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			if constexpr ( _bSpecial ) {
				lsn::DebugA( ("Read u8(S.L" + std::format( "{:+}", _i8SOff ) + ") | $0100\tStore as Operand.L.").c_str() );
			}
			else {
				lsn::DebugA( ("Read ((S.L | $0100)" + std::format( "{:+}", _i8SOff ) + ")\tStore as Operand.L.").c_str() );
			}
		}
		else {
			lsn::DebugA( ("Read (S" + std::format( "{:+}", _i8SOff ) + ")\tStore as Operand.L.").c_str() );
		}
#endif	// #ifdef LSN_CYCLES_DOC
		
		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If M flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );

				if constexpr ( _bEndInstr ) {
					LSN_FINISH_INST( true );
				}
				else {
					LSN_NEXT_FUNCTION;
				}
			}
			else {
				// If the next cycle is skippable, it can't be the last PHI2 in the series. Ignore _bEndInstr, as it will also be present on the following cycle's PHI2 function.
				LSN_NEXT_FUNCTION;
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Reads from [m_fsState.rRegs.ui16X:m_fsState.ui8Bank] into m_fsState.ui8Operand[0] for MVP.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI2_READ_BUSA( rCpu.m_fsState.rRegs.ui16X, rCpu.m_fsState.ui8Bank, rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Read X:Bank\tStore as Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \tparam _bLowByteWrap If true, when adding 1 to the target address causes overflow, the high bits are unaffected (the low byte wraps only).
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bLowByteWrap, bool _bEndInstr>	
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bTo == LSN_TO_A ) {
			if constexpr ( _bLowByteWrap ) {	// Emulation Mode only.
				uint16_t ui16Target = (rCpu.m_fsState.rRegs.ui8D[0]) ? rCpu.m_fsState.ui16Pointer + 1 : (rCpu.m_fsState.ui16Pointer & 0xFF00) | uint8_t( rCpu.m_fsState.ui8Pointer[0] + 1 );
				LSN_INSTR_START_PHI2_READ0_BUSA( ui16Target, rCpu.m_fsState.ui8Address[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				sDebug += "If D.l is not 0, read (Pointer + 1), otherwise read (Pointer & $FF00) | ui8(Pointer.L + 1)\tStore as Address.H.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.ui8Address[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				sDebug += "Read Pointer + 1\tStore as Address.H.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if constexpr ( _bLowByteWrap ) {	// Emulation Mode only.
				uint16_t ui16Target = (rCpu.m_fsState.rRegs.ui8D[0]) ? rCpu.m_fsState.ui16Address + 1 : (rCpu.m_fsState.ui16Address & 0xFF00) | uint8_t( rCpu.m_fsState.ui8Address[0] + 1 );
				LSN_INSTR_START_PHI2_READ0_BUSA( ui16Target, rCpu.m_fsState.ui8Pointer[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				sDebug += "If D.l is not 0, read (Address + 1), otherwise read (Address & $FF00) | ui8(Address.L + 1)\tStore as Pointer.H.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.ui8Pointer[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				sDebug += "Read Address + 1\tStore as Pointer.H.";
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( sDebug.c_str() );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the low byte in m_fsState.ui8Pointer[0] or m_fsState.ui8Address[0].
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is taken from m_fsState.ui16Pointer and stored to m_fsState.ui16Address, otherwise it is taken from m_fsState.ui16Address and stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>	
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.ui16Address, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer\tStore as Address.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.ui16Pointer, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address\tStore as Pointer.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If M flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				LSN_NEXT_FUNCTION_BY( 2 );
			}
#ifdef LSN_CYCLES_DOC
			sDebug += " If X flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
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
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bLowByteWrap If true, when adding 1 to the target address causes overflow, the high bits are unaffected (the low byte wraps only).
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bLowByteWrap>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if constexpr ( _bLowByteWrap ) {	// Emulation Mode only.
				uint16_t ui16Target = (rCpu.m_fsState.rRegs.ui8D[0]) ? rCpu.m_fsState.ui16Address + 2 : (rCpu.m_fsState.ui16Address & 0xFF00) | uint8_t( rCpu.m_fsState.ui8Address[0] + 2 );
				LSN_INSTR_START_PHI2_READ0_BUSA( ui16Target, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "If D.l is not 0, read (Address + 2), otherwise read (Address & $FF00) | ui8(Address.L + 2)\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address + 2, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Address + 2\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if constexpr ( _bLowByteWrap ) {	// Emulation Mode only.
				uint16_t ui16Target = (rCpu.m_fsState.rRegs.ui8D[0]) ? rCpu.m_fsState.ui16Pointer + 2 : (rCpu.m_fsState.ui16Pointer & 0xFF00) | uint8_t( rCpu.m_fsState.ui8Pointer[0] + 2 );
				LSN_INSTR_START_PHI2_READ0_BUSA( ui16Target, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "If D.l is not 0, read (Pointer + 2), otherwise read (Pointer & $FF00) | ui8(Pointer.L + 2)\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer + 2, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Read Pointer + 2\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the result in m_fsState.ui8Bank.
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_LowByteWrap_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_INSTR_START_PHI2_READ0_BUSA( uint8_t( rCpu.m_fsState.ui8Address[0] + 2 ) | (rCpu.m_fsState.ui8Address[1] << 8), rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address + 2, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If D.L is 0, Read (((Address.L + 2) & $FF) | (Address.H << 8)), otherwise read Address + 2\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_INSTR_START_PHI2_READ0_BUSA( uint8_t( rCpu.m_fsState.ui8Pointer[0] + 2 ) | (rCpu.m_fsState.ui8Pointer[1] << 8), rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer + 2, rCpu.m_fsState.ui8Bank, rCpu.m_ui8Speed );
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If D.L is 0, Read (((Pointer.L + 2) & $FF) | (Pointer.H << 8)), otherwise read Pointer + 2\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_LowByteWrap_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_INSTR_START_PHI2_READ0_BUSA( uint8_t( rCpu.m_fsState.ui8Address[0] + 1 ) | (rCpu.m_fsState.ui8Address[1] << 8), rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If D.L is 0, Read (((Address.L + 1) & $FF) | (Address.H << 8)), otherwise read Address + 1\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
				LSN_INSTR_START_PHI2_READ0_BUSA( uint8_t( rCpu.m_fsState.ui8Pointer[0] + 1 ) | (rCpu.m_fsState.ui8Pointer[1] << 8), rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
			}
			else {
				LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
			}
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "If D.L is 0, Read (((Pointer.L + 1) & $FF) | (Pointer.H << 8)), otherwise read Pointer + 1\tStore as Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Reads from m_fsState.ui16Address or m_fsState.ui16Pointer and stores the high byte in m_fsState.ui8Pointer[1] or m_fsState.ui8Address[1].
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the final address is calculated using m_fsState.ui16Address, otherwise it is determined using m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bEndInstr>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bFrom == LSN_FROM_P ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Pointer + 1\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Read Address + 1\tStore as Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bFrom, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
#ifdef LSN_CYCLES_DOC
		std::string sDebug;
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bFrom == LSN_FROM_P ) {
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Pointer\tStore as Operand.";
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_READ0_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.ui16Operand, rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			sDebug += "Read Address\tStore as Operand.";
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
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
			sDebug += " If X flag is set, skip the next cycle.";
#endif	// #ifdef LSN_CYCLES_DOC
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
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Resets Status bits based on Operand. Handles X/M flag sizing updates.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Rep_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			// In Emulation mode, X and M are unused/Break and cannot be cleared via REP.
			rCpu.m_fsState.rRegs.ui8Status &= ~(rCpu.m_fsState.ui8Operand[0] & ~(X() | M()));
		}
		else {
			rCpu.m_fsState.rRegs.ui8Status &= ~rCpu.m_fsState.ui8Operand[0];
			
			// If X flag became 1 (8-bit), we must clear the high bytes of X and Y?
			// The 65816 datasheet says "Index registers are not cleared".
			// But for consistency with 8-bit operations, we often ensure the high byte is zeroed
			// if we are paranoid, or rely on operations to mask it. 
			// However, standard behavior is that the high byte is hidden but preserved when switching 16->8.
			// When switching 8->16, the old high byte reappears (unless XCE cleared it).
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				rCpu.m_fsState.rRegs.ui8X[1] = 0;
				rCpu.m_fsState.rRegs.ui8Y[1] = 0;
			}
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tP &= ~(Operand.L & ~(X flag | M flag))." );
		}
		else {
			lsn::DebugA( "\tP &= ~Operand.L, set X.H and Y.H to 0 if X flag is set." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Operand = (Operand << 1) | C. Sets C, N, and Z, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Rol( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		const bool bOldC = (rCpu.m_fsState.rRegs.ui8Status & C()) != 0;

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );

			rCpu.m_fsState.ui16Operand <<= 1;
			if ( bOldC ) { rCpu.m_fsState.ui8Operand[0] |= 0x01; }

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[1] & 0x80) != 0 );

			rCpu.m_fsState.ui16Operand <<= 1;
			if ( bOldC ) { rCpu.m_fsState.ui16Operand |= 0x0001; }

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[1] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C based off (Operand.L & $80). Perform Operand.L = (Operand.L << 1) | C. Set N based off (Operand.L & $80) and Z based off Operand.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C based off (Operand.L & $80), perform Operand.L = (Operand.L << 1) | C, and set N based off (Operand.L & $80) and Z based off Operand.L, otherwise set C based off (Operand.H & $80), perform Operand = (Operand << 1) | C, and set N based off (Operand.H & $80) and Z based off Operand." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs A = (A << 1) | C. Sets C, N, and Z, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::RolOnA_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		const uint16_t ui16OldC = rCpu.m_fsState.rRegs.ui8Status & C();

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );

			rCpu.m_fsState.rRegs.ui8A[0] = uint8_t( (rCpu.m_fsState.rRegs.ui8A[0] << 1) | ui16OldC );

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[1] & 0x80) != 0 );

			rCpu.m_fsState.rRegs.ui16A = uint16_t( (rCpu.m_fsState.rRegs.ui16A << 1) | ui16OldC );

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[1] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C based off (A.L & $80). Perform A.L = (A.L << 1) | C. Set N based off (A.L & $80) and Z based off A.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C based off (A.L & $80), perform A.L = (A.L << 1) | C, and set N based off (A.L & $80) and Z based off A.L, otherwise set C based off (A.H & $80), perform A = (A << 1) | C, and set N based off (A.H & $80) and Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Operand = (Operand >> 1) | (C << 7/15). Sets C, N, and Z, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Ror( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		const bool bOldC = (rCpu.m_fsState.rRegs.ui8Status & C()) != 0;

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x01) != 0 );

			rCpu.m_fsState.ui8Operand[0] >>= 1;
			if ( bOldC ) { rCpu.m_fsState.ui8Operand[0] |= 0x80; }

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui16Operand & 0x0001) != 0 );

			rCpu.m_fsState.ui16Operand >>= 1;
			if ( bOldC ) { rCpu.m_fsState.ui16Operand |= 0x8000; }

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.ui16Operand & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C based off (Operand.L & $01). Perform Operand.L = (Operand.L >> 1) | (C << 7). Set N based off (Operand.L & $80) and Z based off Operand.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C based off (Operand.L & $01), perform Operand.L = (Operand.L >> 1) | (C << 7), and set N based off (Operand.L & $80) and Z based off Operand.L, otherwise set C based off (Operand.L & $01), perform Operand = (Operand >> 1) | (C << 15), and set N based off (Operand.H & $80) and Z based off Operand." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs A = (A >> 1) | (C << 7/15). Sets C, N, and Z, optionally increases PC.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::RorOnA_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		const uint16_t ui16OldC = rCpu.m_fsState.rRegs.ui8Status & C();

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x01) != 0 );

			rCpu.m_fsState.rRegs.ui8A[0] >>= 1;
			rCpu.m_fsState.rRegs.ui8A[0] |= ui16OldC << 7;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & 0x0001) != 0 );

			rCpu.m_fsState.rRegs.ui16A >>= 1;
			rCpu.m_fsState.rRegs.ui16A |= ui16OldC << 15;

			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & 0x8000) != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc. PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "Set C based off (A.L & $01). Perform A.L = (A.L >> 1) | (C << 7). Set N based off (A.L & $80) and Z based off A.L." );
		}
		else {
			lsn::DebugA( "If M flag is set, set C based off (A.L & $01), perform A.L = (A.L >> 1) | (C << 7), and set N based off (A.L & $80) and Z based off A.L, otherwise set C based off (A.L & $01), perform A = (A >> 1) | (C << 15), and set N based off (A.H & $80) and Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs RTI (sets PC/PB from pulled bytes) and begins the next instruction.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Rti_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Operand;
		rCpu.m_fsState.ui16PcModify = 0;

		if LSN_LIKELY( !rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.rRegs.ui8Pb = rCpu.m_fsState.ui8Bank;
			if ( lsn::CheckBit( rCpu.m_fsState.rRegs.ui8Status, X() ) ) {	
				rCpu.m_fsState.rRegs.ui16X = rCpu.m_fsState.rRegs.ui8X[0];
				rCpu.m_fsState.rRegs.ui16Y = rCpu.m_fsState.rRegs.ui8Y[0];
			}
		}

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( " Set PC to Operand." );
		}
		else {
			lsn::DebugA( " Set PB to Bank. Set PC to Operand. If X flag is set, set X to X.L and Y to Y.L." );
		}
#endif	// #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Pulls the PBR and PC from the stack for RTL.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Rtl_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui8Pb = rCpu.m_fsState.ui8Bank;
		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Operand + 1;
		rCpu.m_fsState.ui16PcModify = 0;

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( " Set PC to (Operand + 1). Set PB to Bank." );
#endif	// #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Returns from subroutine. Pulls PC from stack, adds 1, begins next instruction.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Rts_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		rCpu.m_fsState.rRegs.ui16Pc = rCpu.m_fsState.ui16Operand + 1;

		BeginInst<false, true, false>( _prCpu );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( " Set PC to (Operand + 1)." );
#endif	// #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Performs a subtract-with-borrow with an operand, setting flags C, N, V, and Z.
	 *
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Sbc_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		BeginInst<_bIncPc>( _prCpu );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			Sbc_8( _prCpu, rCpu.m_fsState.rRegs.ui8A[0], rCpu.m_fsState.ui8Operand[0] );
		}
		else {
			Sbc_16( _prCpu, rCpu.m_fsState.rRegs.ui16A, rCpu.m_fsState.ui16Operand );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA(
				"\tIf D flag == 0:\r\n"
				"\t\t  Result = ui16(A.L) - ui16(Operand) - (1 - C flag).\r\n"
				"\t\t  V flag = ((ui16(A.L) ^ ui16(Operand)) & (ui16(A.L) ^ ui8(Result)) & $80) != 0.\r\n"
				"\t\t  C flag = Result <= $FF.\r\n"
				"\t\t  Result = ui8(Result). Z flag = Result == $00. N flag = (Result & $80) != 0.\r\n"
				"\t\tIf D flag == 1:\r\n"
				"\t\t  Lo = int16(A.L & 0x0F) - int16(Operand & 0x0F) - (1 - C flag).\r\n"
				"\t\t  if (Lo < 0) Lo -= 6.\r\n"
				"\t\t  BorrowToHi = Lo < 0 ? 1 : 0.\r\n"
				"\t\t  HiSum = int16(A.L >> 4) - int16(Operand >> 4) - BorrowToHi.\r\n"
				"\t\t  V flag = (((A.L >> 4) ^ (Operand >> 4)) & ((A.L >> 4) ^ HiSum) & $08) != 0.\r\n"
				"\t\t  if (HiSum < 0) HiSum -= 6.\r\n"
				"\t\t  C flag = HiSum >= 0.\r\n"
				"\t\t  Result = ui8(((HiSum & 0x0F) << 4) | (Lo & $0F)).\r\n"
				"\t\t  Z flag = Result == $00. N flag = (Result & $80) != 0." );
		}
		else {
			lsn::DebugA( 
				"\tIf M flag == 1 (8-bit):\r\n"
				"\t\t  If D flag == 0:\r\n"
				"\t\t    Result = ui16(A.L) - ui16(Operand) - (1 - C flag).\r\n"
				"\t\t    V flag = ((ui16(A.L) ^ ui16(Operand)) & (ui16(A.L) ^ ui8(Result)) & $80) != 0.\r\n"
				"\t\t    C flag = Result <= $FF.\r\n"
				"\t\t    Result = ui8(Result). Z flag = Result == $00. N flag = (Result & $80) != 0.\r\n"
				"\t\t  If D flag == 1:\r\n"
				"\t\t    Lo = int16(A.L & 0x0F) - int16(Operand & 0x0F) - (1 - C flag).\r\n"
				"\t\t    if (Lo < 0) Lo -= 6.\r\n"
				"\t\t    BorrowToHi = Lo < 0 ? 1 : 0.\r\n"
				"\t\t    HiSum = int16(A.L >> 4) - int16(Operand >> 4) - BorrowToHi.\r\n"
				"\t\t    V flag = (((A.L >> 4) ^ (Operand >> 4)) & ((A.L >> 4) ^ HiSum) & $08) != 0.\r\n"
				"\t\t    if (HiSum < 0) HiSum -= 6.\r\n"
				"\t\t    C flag = HiSum >= 0.\r\n"
				"\t\t    Result = ui8(((HiSum & 0x0F) << 4) | (Lo & $0F)).\r\n"
				"\t\t    Z flag = Result == $00. N flag = (Result & $80) != 0.\r\n"
				"\t\tIf M flag == 0 (16-bit):\r\n"
				"\t\t  If D flag == 0:\r\n"
				"\t\t    Result = ui32(A) - ui32(Operand) - (1 - C flag).\r\n"
				"\t\t    V flag = ((ui32(A) ^ ui32(Operand)) & (ui32(A) ^ ui16(Result)) & $8000) != 0.\r\n"
				"\t\t    C flag = Result <= $FFFF.\r\n"
				"\t\t    Result = ui16(Result).\r\n"
				"\t\t    Z flag = Result == $0000. N flag = (Result & $8000) != 0.\r\n"
				"\t\t  If D flag == 1:\r\n"
				"\t\t    Result = ui16(0). Borrow = ui16(1 - C flag).\r\n"
				"\t\t    for i = 0, 4, 8, 12:\r\n"
				"\t\t      DigitSum = int16((A >> i) & $0F) - int16((Operand >> i) & $0F) - Borrow.\r\n"
				"\t\t      if (i == 12) V flag = (((A >> 12) ^ (Operand >> 12)) & ((A >> 12) ^ DigitSum) & $08) != 0.\r\n"
				"\t\t      if (DigitSum < 0) DigitSum -= 6.\r\n"
				"\t\t      Borrow = (DigitSum < 0) ? 1 : 0.\r\n"
				"\t\t      Result |= ui16((DigitSum & $0F) << i).\r\n"
				"\t\t    C flag = Borrow == 0. Z flag = Result == $0000. N flag = (Result & $8000) != 0." );
		}
#endif // #ifdef LSN_CYCLES_DOC
	}

	/**
	 * Sets the carry bit.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Sec_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<C(), true>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the C flag to 1." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Sets the decimal flag (D).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Sed_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<D(), true>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the D flag to 1." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Sets the IRQ flag.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Sei_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );
		
		SetBit<I(), true>( rCpu.m_fsState.rRegs.ui8Status );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet the I flag to 1." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Selects the BRK vector etc.
	 * 
	 * \tparam _bAdjS If true, S is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bAdjS>
	inline void CRicoh5A22::Select_Brk_Vectors( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

#ifdef LSN_CYCLES_DOC
		std::string sDebug = "\t";
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bAdjS ) {
			LSN_UPDATE_S;
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				if ( rCpu.m_fsState.ui16SModify < 0 ) {
					sDebug += "Dec. S.L by " + std::to_string( -rCpu.m_fsState.ui16SModify ) + " and set S.H to 1. ";
				}
				else if ( rCpu.m_fsState.ui16SModify > 0 ) {
					sDebug += "Inc. S.L by " + std::to_string( rCpu.m_fsState.ui16SModify ) + " and set S.H to 1. ";
				}
			}
			else {
				if ( rCpu.m_fsState.ui16SModify < 0 ) {
					sDebug += "Dec. S by " + std::to_string( -rCpu.m_fsState.ui16SModify ) + ". ";
				}
				else if ( rCpu.m_fsState.ui16SModify > 0 ) {
					sDebug += "Inc. S by " + std::to_string( rCpu.m_fsState.ui16SModify ) + ". ";
				}
			}
#endif	// #ifdef LSN_CYCLES_DOC
		}

#ifdef LSN_CPU_VERIFY
		rCpu.m_fsState.vBrkVector = rCpu.m_fsState.bEmulationMode ? LSN_V_IRQ_BRK_E : LSN_V_BRK;
		rCpu.m_fsState.bPushB = rCpu.m_fsState.bEmulationMode;

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			sDebug += "Use Interrupt flags to decide which vector to use. RESET = $FFFC. NMI = $FFFA. IRQ/BRK = $FFFE.";
		}
		else {
			sDebug += "Use Interrupt flags to decide which vector to use. RESET = $FFFC. NMI = $FFEA. IRQ = $FFEE. BRK = $FFE6.";
		}
		lsn::DebugA( sDebug.c_str() );
#endif // #ifdef LSN_CYCLES_DOC
#else

		// Select vector to use.
		if ( rCpu.m_bIsReset ) {
			rCpu.m_fsState.vBrkVector = rCpu.m_fsState.bEmulationMode ? LSN_V_RESET_E : LSN_V_RESET_E;
			rCpu.m_bIsReset = false;
		}
		else if ( rCpu.m_bDetectedNmi ) {
			rCpu.m_fsState.vBrkVector = rCpu.m_fsState.bEmulationMode ? LSN_V_NMI_E : LSN_V_NMI;
		}
		else if ( rCpu.m_bHandleIrq ) {
			rCpu.m_fsState.vBrkVector = rCpu.m_fsState.bEmulationMode ? LSN_V_IRQ_BRK_E : LSN_V_IRQ;
		}
		else {
			rCpu.m_fsState.vBrkVector = rCpu.m_fsState.bEmulationMode ? LSN_V_IRQ_BRK_E : LSN_V_BRK;
		}

		if LSN_LIKELY( !rCpu.m_bRdyLow ) {
			if ( rCpu.m_bDetectedNmi ) {
				rCpu.m_bHandleNmi = rCpu.m_bDetectedNmi = false;
				rCpu.m_bNmiStatusLine = false;
			}
			rCpu.m_bHandleIrq = false;
		}
#endif	// #ifdef LSN_CPU_VERIFY

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Selects the COP vector etc.
	 * 
	 * \tparam _bAdjS If true, S is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bAdjS>
	inline void CRicoh5A22::Select_Cop_Vectors( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );
		
		if constexpr ( _bAdjS ) {	
			LSN_UPDATE_S;
		}

		// Select vector to use.
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.vBrkVector = LSN_V_COP_E;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet Vector to $FFF4." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.vBrkVector = LSN_V_COP;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet Vector to $FFE4." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Sets Status bits based on Operand. Handles X/M flag sizing updates.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	inline void CRicoh5A22::Sep_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			// In Emulation mode, X and M are forced.
			rCpu.m_fsState.rRegs.ui8Status |= (rCpu.m_fsState.ui8Operand[0] & ~(X() | M()));
		}
		else {
			rCpu.m_fsState.rRegs.ui8Status |= rCpu.m_fsState.ui8Operand[0];
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
				rCpu.m_fsState.rRegs.ui8X[1] = 0;
				rCpu.m_fsState.rRegs.ui8Y[1] = 0;
			}
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform P |= (Operand.L & ~(X flag | M flag))." );
		}
		else {
			lsn::DebugA( "\tPerform P |= Operand.L, set X.H and Y.H to 0 if X flag is set." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<true, false, false>( _prCpu );
	}

	/**
	 * Sets I and X.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Set_Brk_Flags( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		SetBit<I(), true>( rCpu.m_fsState.rRegs.ui8Status );
		SetBit<D(), false>( rCpu.m_fsState.rRegs.ui8Status );
		
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet I, unset D." );
#endif // #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Skips the next instruction if the M status flag is set.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::SkipIfM_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_NEXT_FUNCTION;

		rCpu.m_ui8Speed = rCpu.m_ui8FastDiv;

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			LSN_NEXT_FUNCTION_BY( 2 );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tIf M flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Skips the next instruction if the low byte of D is 0.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::SkipOnDL_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_NEXT_FUNCTION;

		rCpu.m_ui8Speed = rCpu.m_ui8FastDiv;

		if ( !rCpu.m_fsState.rRegs.ui8D[0] ) {
			LSN_NEXT_FUNCTION_BY( 2 );
		}

#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tIf D.L is 0, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Copies A to m_fsState.ui16Operand.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Sta( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		rCpu.m_fsState.ui16Operand = rCpu.m_fsState.rRegs.ui16A;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
			LSN_UPDATE_PC;
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Set Operand to A." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Stops the processor (STP).
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Stp_BeginInst( CRicoh5A22 * _prCpu ) {
		LSN_INSTR_START_PHI1( false );
		//rCpu.m_fsState.rRegs.ui16Pc--;
		
#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tStop processor." );
#endif	// #ifdef LSN_CYCLES_DOC

		// Loop this instruction forever until Reset.
		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Copies X to m_fsState.ui16Operand.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Stx( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		rCpu.m_fsState.ui16Operand = rCpu.m_fsState.rRegs.ui16X;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
			LSN_UPDATE_PC;
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Set Operand to X." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Copies Y to m_fsState.ui16Operand.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Sty( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		rCpu.m_fsState.ui16Operand = rCpu.m_fsState.rRegs.ui16Y;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
			LSN_UPDATE_PC;
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Set Operand to Y." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Sets m_fsState.ui16Operand to 0.
	 * 
	 * \tparam _bIncPc If true, PC is updated.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bIncPc>
	inline void CRicoh5A22::Stz( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		rCpu.m_fsState.ui16Operand = 0;

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_CYCLES_DOC

		if constexpr ( _bIncPc ) {
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Inc PC. " );
#endif	// #ifdef LSN_CYCLES_DOC
			LSN_UPDATE_PC;
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Set Operand to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs X = A. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tax_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[0] = rCpu.m_fsState.rRegs.ui8A[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8X[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16X = rCpu.m_fsState.rRegs.ui16A;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16X );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform X.L = A.L, set N based off (X.L & $80), set Z based off X.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform X.L = A.L, set N based off (X.L & $80), and set Z based off X.L, otherwise perform X = A, set N based off (X.H & $80), and set Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Y = A. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tay_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8Y[0] = rCpu.m_fsState.rRegs.ui8A[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8Y[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16Y = rCpu.m_fsState.rRegs.ui16A;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16Y );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform Y.L = A.L, set N based off (Y.L & $80), set Z based off Y.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform Y.L = A.L, set N based off (Y.L & $80), and set Z based off Y.L, otherwise perform Y = A, set N based off (Y.H & $80), and set Z based off Y." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Transfer 16 bit A to D. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tcd_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		// TCD transfers the full 16-bit C (A) into D regardless of M.
		rCpu.m_fsState.rRegs.ui16D = rCpu.m_fsState.rRegs.ui16A;

		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8D[1] & 0x80) != 0 );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16D );

	#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet D to A. Set N based off (D.H & $80) and Z based off D." );
	#endif	// LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Transfer 16 bit A to S. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tcs_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.rRegs.ui8S[0] = rCpu.m_fsState.rRegs.ui8A[0];
			rCpu.m_fsState.rRegs.ui8S[1] = 1;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet S.L to A.L and S.H to 1." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.rRegs.ui16S = rCpu.m_fsState.rRegs.ui16A;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet S to A." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Transfer 16-bit D to A. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tdc_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		// TDC transfers the full 16-bit D into C (A) regardless of M.
		rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.rRegs.ui16D;

		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[1] & 0x80) != 0 );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSet A to D. Set N based off (A.H & $80) and Z based off A." );
#endif	// LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs m_ui16Operand &= ~A. Sets Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Trb( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & rCpu.m_fsState.ui8Operand[0]) == 0 );
		}
		else {
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & rCpu.m_fsState.ui16Operand) == 0 );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet Z based off (A.L & Operand.L)." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, set Z based off (A.L & Operand.L), otherwise set Z based off (A & Operand)." );
		}
		lsn::DebugA( " Perform Operand &= ~A." );
#endif	// #ifdef LSN_CYCLES_DOC
		
		rCpu.m_fsState.ui16Operand &= ~rCpu.m_fsState.rRegs.ui16A;


		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs m_ui16Operand |= A. Sets Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tsb( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( false );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui8A[0] & rCpu.m_fsState.ui8Operand[0]) == 0 );
		}
		else {
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, (rCpu.m_fsState.rRegs.ui16A & rCpu.m_fsState.ui16Operand) == 0 );
		}
		
#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet Z based off (A.L & Operand.L)." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, set Z based off (A.L & Operand.L), otherwise set Z based off (A & Operand)." );
		}
		lsn::DebugA( " Perform Operand |= A." );
#endif	// #ifdef LSN_CYCLES_DOC

		rCpu.m_fsState.ui16Operand |= rCpu.m_fsState.rRegs.ui16A;


		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI1;
	}

	/**
	 * Transfer 16-bit S to A. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tsc_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.rRegs.ui8S[0] | 0x0100;
		}
		else {
			rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.rRegs.ui16S;
		}
		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tSet A to (S.L | $0100). Set N based off (A.H & $80) and Z based off A." );
		}
		else {
			lsn::DebugA( "\tSet A to S. Set N based off (A.H & $80) and Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs X = S. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tsx_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[0] = rCpu.m_fsState.rRegs.ui8S[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8X[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16X = rCpu.m_fsState.rRegs.ui16S;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16X );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform X.L = S.L, set N based off (X.L & $80), set Z based off X.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform X.L = S.L, set N based off (X.L & $80), and set Z based off X.L, otherwise perform X = S, set N based off (X.H & $80), and set Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs A = X. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Txa_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			rCpu.m_fsState.rRegs.ui8A[0] = rCpu.m_fsState.rRegs.ui8X[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.rRegs.ui16X;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform A.L = X.L, set N based off (A.L & $80), set Z based off A.L." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, perform A.L = X.L, set N based off (A.L & $80), and set Z based off A.L, otherwise perform A = X, set N based off (A.H & $80), and set Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs S = X. Does not set flags.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Txs_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.rRegs.ui8S[0] = rCpu.m_fsState.rRegs.ui8X[0];
			rCpu.m_fsState.rRegs.ui8S[1] = 1;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet S.L to X.L and S.H to 1." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			rCpu.m_fsState.rRegs.ui16S = rCpu.m_fsState.rRegs.ui16X;
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "\tSet S to X." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs Y = X. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Txy_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8Y[0] = rCpu.m_fsState.rRegs.ui8X[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8Y[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16Y = rCpu.m_fsState.rRegs.ui16X;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8Y[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16Y );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform Y.L = X.L, set N based off (Y.L & $80), set Z based off Y.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform Y.L = X.L, set N based off (Y.L & $80), and set Z based off Y.L, otherwise perform Y = X, set N based off (Y.H & $80), and set Z based off Y." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs A = Y. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tya_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
			rCpu.m_fsState.rRegs.ui8A[0] = rCpu.m_fsState.rRegs.ui8Y[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8A[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16A = rCpu.m_fsState.rRegs.ui16Y;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16A );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform A.L = Y.L, set N based off (A.L & $80), set Z based off A.L." );
		}
		else {
			lsn::DebugA( "\tIf M flag is set, perform A.L = Y.L, set N based off (A.L & $80), and set Z based off A.L, otherwise perform A = Y, set N based off (A.H & $80), and set Z based off A." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Performs X = Y. Sets N and Z.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Tyx_BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		LSN_INSTR_START_PHI1( true );

		if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
			rCpu.m_fsState.rRegs.ui8X[0] = rCpu.m_fsState.rRegs.ui8Y[0];
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[0] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui8X[0] );
		}
		else {
			rCpu.m_fsState.rRegs.ui16X = rCpu.m_fsState.rRegs.ui16Y;
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, rCpu.m_fsState.rRegs.ui8X[1] & 0x80 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, !rCpu.m_fsState.rRegs.ui16X );
		}

#ifdef LSN_CYCLES_DOC
		if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			lsn::DebugA( "\tPerform X.L = Y.L, set N based off (X.L & $80), set Z based off X.L." );
		}
		else {
			lsn::DebugA( "\tIf X flag is set, perform X.L = Y.L, set N based off (X.L & $80), and set Z based off X.L, otherwise perform X = Y, set N based off (X.H & $80), and set Z based off X." );
		}
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Puts the CPU into a waiting state.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Wai_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		rCpu.m_ui8Speed = rCpu.m_ui8FastDiv;

		LSN_NEXT_FUNCTION_BY( uint8_t( -1 ) );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tEnter waiting state. Repeat this cycle forever." );
#endif	// LSN_CYCLES_DOC

		LSN_FINISH_INST( true );

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Executes WDM (reserved). Consumes the immediate byte; no architecturally visible effects.
	 * 
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	inline void CRicoh5A22::Wdm_BeginInst( CRicoh5A22 * _prCpu ) {
		LSN_INSTR_START_PHI1( true );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tInc. PC." );
#endif	// LSN_CYCLES_DOC

		BeginInst<true, false, false>( _prCpu );
	}

	/**
	 * Writes A to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_A_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.rRegs.ui8A[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1\tWrite A.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.rRegs.ui8A[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1\tWrite A.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes A to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.rRegs.ui8A[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address\tWrite A.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.rRegs.ui8A[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer\tWrite A.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.ui8Operand[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.ui8Operand[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes X to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_X_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Address + 1, rCpu.m_fsState.rRegs.ui8X[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1\tWrite X.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Pointer + 1, rCpu.m_fsState.rRegs.ui8X[1], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1\tWrite X.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes X to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CRicoh5A22 instance.
	 **/
	template <bool _bTo, bool _bSkipIfX, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Address, rCpu.m_fsState.rRegs.ui8X[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address\tWrite X.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( rCpu.m_fsState.ui16Pointer, rCpu.m_fsState.rRegs.ui8X[0], rCpu.m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer\tWrite X.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfX ) {
			if ( (rCpu.m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes Y to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_Y_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Address + 1, _prCpu->m_fsState.rRegs.ui8Y[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1\tWrite Y.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Pointer + 1, _prCpu->m_fsState.rRegs.ui8Y[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1\tWrite Y.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes Y to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfX, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Address, _prCpu->m_fsState.rRegs.ui8Y[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address\tWrite Y.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Pointer, _prCpu->m_fsState.rRegs.ui8Y[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer\tWrite Y.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfX ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes 0 to m_fsState.ui16Address + 1 or m_fsState.ui16Pointer + 1.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_Zero_High_To_AddrOrPtr_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Address + 1, 0, _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1\tWrite 0." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Pointer + 1, 0, _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1\tWrite 0." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes 0 to m_fsState.ui16Address or m_fsState.ui16Pointer.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr>
	inline void CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Address, 0, _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address\tWrite 0." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE0_BUSA( _prCpu->m_fsState.ui16Pointer, 0, _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer\tWrite 0." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.rRegs.ui8A[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::Write_A_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Address + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.rRegs.ui8A[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1:Bank (With Carry)\tWrite A.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Pointer + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.rRegs.ui8A[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1:Bank (With Carry)\tWrite A.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.rRegs.ui8A[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Write_A_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Address, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.rRegs.ui8A[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address:Bank\tWrite A.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Pointer, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.rRegs.ui8A[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer:Bank\tWrite A.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bBankWrap If true, the bank wraps (instead of carries) on addresses where + 1 crosses into a new bank.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr, bool _bBankWrap>
	inline void CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			if constexpr ( _bBankWrap ) {
				LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Address + 1, _prCpu->m_fsState.rRegs.ui8Db, _prCpu->m_fsState.ui8Operand[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Write to Address + 1:DB\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				uint32_t ui32Offset = _prCpu->m_fsState.ui16Address + 1;
				LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.rRegs.ui8Db + (ui32Offset >> 16), _prCpu->m_fsState.ui8Operand[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Write to Address + 1:DB (With Carry)\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}
		else {
			if constexpr ( _bBankWrap ) {
				LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Pointer + 1, _prCpu->m_fsState.rRegs.ui8Db, _prCpu->m_fsState.ui8Operand[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Write to Pointer + 1:DB\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
			else {
				uint32_t ui32Offset = _prCpu->m_fsState.ui16Pointer + 1;
				LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.rRegs.ui8Db + (ui32Offset >> 16), _prCpu->m_fsState.ui8Operand[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
				lsn::DebugA( "Write to Pointer + 1:DB (With Carry)\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
			}
		}

//		if constexpr ( _bTo == LSN_TO_A ) {
//			LSN_INSTR_START_PHI2_WRITE_BUSA( m_fsState.ui16Address + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
//#ifdef LSN_CYCLES_DOC
//			lsn::DebugA( "Write to Address + 1:DB\tWrite Operand.H." );
//#endif	// #ifdef LSN_CYCLES_DOC
//		}
//		else {
//			LSN_INSTR_START_PHI2_WRITE_BUSA( m_fsState.ui16Pointer + 1, m_fsState.rRegs.ui8Db, m_fsState.ui8Operand[1], m_ui8Speed );
//#ifdef LSN_CYCLES_DOC
//			lsn::DebugA( "Write to Pointer + 1:DB\tWrite Operand.H." );
//#endif	// #ifdef LSN_CYCLES_DOC
//		}
		
		if constexpr ( _bEndInstr ) {
			LSN_FINISH_INST( true );
		}
		else {
			LSN_NEXT_FUNCTION;
		}

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Address or m_fsState.ui16Pointer with bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Address, _prCpu->m_fsState.rRegs.ui8Db, _prCpu->m_fsState.ui8Operand[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address:DB\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Pointer, _prCpu->m_fsState.rRegs.ui8Db, _prCpu->m_fsState.ui8Operand[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer:DB\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.rRegs.ui8X[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::Write_X_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Address + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.rRegs.ui8X[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1:Bank (With Carry)\tWrite X.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Pointer + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.rRegs.ui8X[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1:Bank (With Carry)\tWrite X.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.rRegs.ui8X[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Write_X_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Address, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.rRegs.ui8X[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address:Bank\tWrite X.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Pointer, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.rRegs.ui8X[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer:Bank\tWrite X.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.rRegs.ui8Y[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::Write_Y_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Address + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.rRegs.ui8Y[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1:Bank (With Carry)\tWrite Y.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Pointer + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.rRegs.ui8Y[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1:Bank (With Carry)\tWrite Y.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.rRegs.ui8Y[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Write_Y_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Address, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.rRegs.ui8Y[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address:Bank\tWrite Y.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Pointer, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.rRegs.ui8Y[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer:Bank\tWrite Y.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.ui8Operand[1] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bEndInstr>
	inline void CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Address + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.ui8Operand[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address + 1:Bank (With Carry)\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			uint32_t ui32Offset = _prCpu->m_fsState.ui16Pointer + 1;
			LSN_INSTR_START_PHI2_WRITE_BUSA( ui32Offset, _prCpu->m_fsState.ui8Bank + (ui32Offset >> 16), _prCpu->m_fsState.ui8Operand[1], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer + 1:Bank (With Carry)\tWrite Operand.H." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.ui8Operand[0] to m_fsState.ui16Pointer or m_fsState.ui16Address and m_fsState.ui8Bank.
	 * 
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bSkipIfM If true, the next cycle is skipped if M() is set.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 * \tparam _bSkipIfX If true, the next cycle is skipped if X() is set.
	 * \param _prCpu The CPU object.
	 **/
	template <bool _bTo, bool _bSkipIfM, bool _bEndInstr, bool _bSkipIfX>
	inline void CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2( CRicoh5A22 * _prCpu ) {
		if constexpr ( _bTo == LSN_TO_A ) {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Address, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.ui8Operand[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Address:Bank\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else {
			LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.ui16Pointer, _prCpu->m_fsState.ui8Bank, _prCpu->m_fsState.ui8Operand[0], _prCpu->m_ui8Speed );
#ifdef LSN_CYCLES_DOC
			lsn::DebugA( "Write to Pointer:Bank\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC
		}

		if constexpr ( _bSkipIfM ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & M()) ) {
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
#endif	// #ifdef LSN_CYCLES_DOC
		}
		else if constexpr ( _bSkipIfX ) {
			if ( (_prCpu->m_fsState.rRegs.ui8Status & X()) ) {
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
			lsn::DebugA( " If X flag is set, skip the next cycle." );
#endif	// #ifdef LSN_CYCLES_DOC
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
	 * Writes m_fsState.ui8Operand[0] to [m_fsState.rRegs.ui16Y:m_fsState.rRegs.ui8Db] for MVP.
	 * 
	 * \param _prCpu The CPU object.
	 **/
	inline void CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2( CRicoh5A22 * _prCpu ) {
		LSN_INSTR_START_PHI2_WRITE_BUSA( _prCpu->m_fsState.rRegs.ui16Y, _prCpu->m_fsState.rRegs.ui8Db, _prCpu->m_fsState.ui8Operand[0], _prCpu->m_ui8Speed );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "Write Y:DB\tWrite Operand.L." );
#endif	// #ifdef LSN_CYCLES_DOC

		LSN_NEXT_FUNCTION;

		LSN_INSTR_END_PHI2;
	}

	/**
	 * Exchanges the low and high bytes of the Accumulator. Sets N and Z based on the new low byte.
	 * 
	 * \param _prCpu The CPU object.
	 **/
	inline void CRicoh5A22::Xba_BeginInst( CRicoh5A22 * _prCpu ) {
		LSN_INSTR_START_PHI1( true );

		uint8_t ui8Tmp = _prCpu->m_fsState.rRegs.ui8A[0];
		_prCpu->m_fsState.rRegs.ui8A[0] = _prCpu->m_fsState.rRegs.ui8A[1];
		_prCpu->m_fsState.rRegs.ui8A[1] = ui8Tmp;

		SetBit<N()>( _prCpu->m_fsState.rRegs.ui8Status, _prCpu->m_fsState.rRegs.ui8A[0] & 0x80 );
		SetBit<Z()>( _prCpu->m_fsState.rRegs.ui8Status, !_prCpu->m_fsState.rRegs.ui8A[0] );

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tSwap A.L and A.H, set N based off (A.L & $80), and set Z based off A.L." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Exchanges the carry (C) and emulation (E) flags.
	 * 
	 * \param _prCpu The CPU object.
	 **/
	inline void CRicoh5A22::Xce_BeginInst( CRicoh5A22 * _prCpu ) {
		LSN_INSTR_START_PHI1( true );

		const bool bOldCarry = (_prCpu->m_fsState.rRegs.ui8Status & C()) != 0;
		SetBit<C()>( _prCpu->m_fsState.rRegs.ui8Status, _prCpu->m_fsState.bEmulationMode );
		_prCpu->m_fsState.bEmulationMode = bOldCarry;

		if LSN_UNLIKELY( _prCpu->m_fsState.bEmulationMode ) {
			_prCpu->m_fsState.rRegs.ui8Status |= (M() | X());
			_prCpu->m_fsState.rRegs.ui8X[1] = 0;
			_prCpu->m_fsState.rRegs.ui8Y[1] = 0;
			_prCpu->m_fsState.rRegs.ui8S[1] = 1;
		}

#ifdef LSN_CYCLES_DOC
		lsn::DebugA( "\tExchanges the Carry and Emulation flags. If Emulation mode is entered, M and X flags are set to 1, S.H is set to 1, and X.H and Y.H are cleared to 0." );
#endif	// #ifdef LSN_CYCLES_DOC

		BeginInst<false, false, false>( _prCpu );
	}

	/**
	 * Prepares to enter a new instruction.
	 *
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
	 * \param _prCpu The CRicoh5A22 instance.
	 */
	template <bool _bIncPc, bool _bAdjS, bool _bCheckStartOfFunction>
	inline void CRicoh5A22::BeginInst( CRicoh5A22 * _prCpu ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		if constexpr ( _bCheckStartOfFunction ) {
			LSN_INSTR_START_PHI1( true );
		}

		if constexpr ( _bIncPc ) {
			LSN_UPDATE_PC;
		}

		if constexpr ( _bAdjS ) {
#ifdef LSN_CYCLES_DOC
			if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
				if ( int16_t( rCpu.m_fsState.ui16SModify ) < 0 ) {
					lsn::DebugA( ("\tDec. S.L by " + std::to_string( -int16_t( rCpu.m_fsState.ui16SModify ) ) + " and set S.H to 1.").c_str() );
				}
				else if ( int16_t( rCpu.m_fsState.ui16SModify ) > 0 ) {
					lsn::DebugA( ("\tInc. S.L by " + std::to_string( int16_t( rCpu.m_fsState.ui16SModify ) ) + " and set S.H to 1.").c_str() );
				}
			}
			else {
				if ( int16_t( rCpu.m_fsState.ui16SModify ) < 0 ) {
					lsn::DebugA( ("\tDec. S by " + std::to_string( -int16_t( rCpu.m_fsState.ui16SModify ) ) + ".").c_str() );
				}
				else if ( int16_t( rCpu.m_fsState.ui16SModify ) > 0 ) {
					lsn::DebugA( ("\tInc. S by " + std::to_string( int16_t( rCpu.m_fsState.ui16SModify ) ) + ".").c_str() );
				}
			}
#endif	// #ifdef LSN_CYCLES_DOC
			LSN_UPDATE_S;
		}

		// Enter normal instruction context.
		rCpu.m_fsState.ui8FuncIndex = 0;
		rCpu.m_pfTickFunc = rCpu.m_pfTickFuncCopy = &CRicoh5A22::Tick_InstructionCycleStd;
		rCpu.m_fsState.bBoundaryCrossed = false;
		/*if LSN_UNLIKELY( rCpu.m_fsState.bEmulationMode ) {
			rCpu.m_fsState.rRegs.ui8S[1] = 1;
		}*/
		//rCpu.m_ui8RdyOffCnt = 0;
		LSN_INSTR_END_PHI1;
	}

	/**
	 * Performs an 8-bit add-with-carry with an operand, setting flags C, N, V, and Z.
	 *
	 * \param _prCpu The CRicoh5A22 instance.
	 * \param _ui8RegVal The register value used in the comparison.
	 * \param _ui8OpVal The operand value used in the comparison.
	 */
	inline void CRicoh5A22::Adc_8( CRicoh5A22 * _prCpu, uint8_t &_ui8RegVal, uint8_t _ui8OpVal ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		const uint8_t ui8A = _ui8RegVal;
		const uint8_t ui8CarryIn = rCpu.m_fsState.rRegs.ui8Status & C();

		if ( (rCpu.m_fsState.rRegs.ui8Status & D()) ) {
			uint16_t ui16Lo = uint16_t( ui8A & 0x0F ) + uint16_t( _ui8OpVal & 0x0F ) + uint16_t( ui8CarryIn );
			if ( ui16Lo > 9 ) { ui16Lo += 6; }
			
			const uint8_t ui8CarryToHi = (ui16Lo > 0x0F) ? 1 : 0;
			const uint16_t ui16HiSum = uint16_t( ui8A >> 4 ) + uint16_t( _ui8OpVal >> 4 ) + uint16_t( ui8CarryToHi );

			SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
				(~((ui8A >> 4) ^ (_ui8OpVal >> 4)) & ((ui8A >> 4) ^ ui16HiSum) & 0x08) != 0 );

			uint16_t ui16Hi = ui16HiSum;
			if ( ui16Hi > 9 ) { ui16Hi += 6; }

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, ui16Hi > 0x0F );

			_ui8RegVal = uint8_t( ((ui16Hi & 0x0F) << 4) | (ui16Lo & 0x0F) );

			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui8RegVal == 0x00 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui8RegVal & 0x80) != 0 );
		}
		else {
			const uint16_t ui16Result = uint16_t( ui8A ) + uint16_t( _ui8OpVal ) + uint16_t( ui8CarryIn );

			SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
				(~(uint16_t( ui8A ) ^ uint16_t( _ui8OpVal )) & (uint16_t( ui8A ) ^ (uint8_t)ui16Result) & 0x0080) != 0 );

			_ui8RegVal = uint8_t( ui16Result );

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, ui16Result > 0x00FF );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui8RegVal == 0x00 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui8RegVal & 0x80) != 0 );
		}
	}

	/**
	 * Performs a 16-bit add-with-carry with an operand, setting flags C, N, V, and Z.
	 * Respects Decimal Mode (D) when enabled.
	 *
	 * \param _prCpu The CRicoh5A22 instance.
	 * \param _ui16RegVal The register value used in the operation.
	 * \param _ui16OpVal The operand value used in the operation.
	 */
	inline void CRicoh5A22::Adc_16( CRicoh5A22 * _prCpu, uint16_t &_ui16RegVal, uint16_t _ui16OpVal ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		const uint16_t ui16A = _ui16RegVal;
		const uint16_t ui16CarryIn = rCpu.m_fsState.rRegs.ui8Status & C();

		if ( (rCpu.m_fsState.rRegs.ui8Status & D()) ) {
			uint16_t ui16Res = 0;
			uint16_t ui16Carry = ui16CarryIn;

			for ( int32_t I = 0; I < 16; I += 4 ) {
				uint16_t ui16DigitSum = uint16_t( (ui16A >> I) & 0x000F ) + uint16_t( (_ui16OpVal >> I) & 0x000F ) + ui16Carry;

				if ( I == 12 ) {
					SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
						(~((ui16A >> 12) ^ (_ui16OpVal >> 12)) & ((ui16A >> 12) ^ ui16DigitSum) & 0x08) != 0 );
				}

				if ( ui16DigitSum > 9 ) { ui16DigitSum += 6; }

				ui16Carry = (ui16DigitSum > 0x000F) ? 1 : 0;
				ui16Res |= uint16_t( (ui16DigitSum & 0x000F) << I );
			}

			_ui16RegVal = ui16Res;

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, ui16Carry != 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui16RegVal == 0x0000 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui16RegVal & 0x8000) != 0 );
		}
		else {
			const uint32_t ui32Result = uint32_t( ui16A ) + uint32_t( _ui16OpVal ) + uint32_t( ui16CarryIn );

			SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
				(~(uint32_t( ui16A ) ^ uint32_t( _ui16OpVal )) & (uint32_t( ui16A ) ^ (uint16_t)ui32Result) & 0x00008000) != 0 );

			_ui16RegVal = uint16_t( ui32Result );

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, ui32Result > 0xFFFF );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui16RegVal == 0x0000 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui16RegVal & 0x8000) != 0 );
		}
	}

	/**
	 * Performs a compare against a register and an operand by setting flags.
	 *
	 * \param _prCpu The CRicoh5A22 instance.
	 * \param _ui8RegVal The register value used in the comparison.
	 * \param _ui8OpVal The operand value used in the comparison.
	 */
	inline void CRicoh5A22::Cmp( CRicoh5A22 * _prCpu, uint8_t _ui8RegVal, uint8_t _ui8OpVal ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, _ui8RegVal >= _ui8OpVal );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui8RegVal == _ui8OpVal );
		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, ((_ui8RegVal - _ui8OpVal) & 0x80) != 0 );
	}

	/**
	 * Performs a compare against a register and an operand by setting flags.
	 *
	 * \param _prCpu The CRicoh5A22 instance.
	 * \param _ui16RegVal The register value used in the comparison.
	 * \param _ui16OpVal The operand value used in the comparison.
	 */
	inline void CRicoh5A22::Cmp( CRicoh5A22 * _prCpu, uint16_t _ui16RegVal, uint16_t _ui16OpVal ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, _ui16RegVal >= _ui16OpVal );
		SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui16RegVal == _ui16OpVal );
		SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, ((_ui16RegVal - _ui16OpVal) & 0x8000) != 0 );
	}

	/**
	 * Performs an 8-bit subtract-with-carry with an operand, setting flags C, N, V, and Z.
	 *
	 * \param _prCpu The CRicoh5A22 instance.
	 * \param _ui8RegVal The register value used in the comparison.
	 * \param _ui8OpVal The operand value used in the comparison.
	 */
	inline void CRicoh5A22::Sbc_8( CRicoh5A22 * _prCpu, uint8_t &_ui8RegVal, uint8_t _ui8OpVal ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		const uint8_t ui8A = _ui8RegVal;
		const uint8_t ui8CarryIn = (rCpu.m_fsState.rRegs.ui8Status & C()) ? 1 : 0;

		if ( (rCpu.m_fsState.rRegs.ui8Status & D()) ) {
			int16_t i16Lo = int16_t( ui8A & 0x0F ) - int16_t( _ui8OpVal & 0x0F ) - (1 - ui8CarryIn);
			if ( i16Lo < 0 ) { i16Lo -= 6; }
			
			const int16_t i16BorrowToHi = (i16Lo < 0) ? 1 : 0;
			const int16_t i16HiSum = int16_t( ui8A >> 4 ) - int16_t( _ui8OpVal >> 4 ) - i16BorrowToHi;

			SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
				(((ui8A >> 4) ^ (_ui8OpVal >> 4)) & ((ui8A >> 4) ^ i16HiSum) & 0x08) != 0 );

			int16_t i16Hi = i16HiSum;
			if ( i16Hi < 0 ) { i16Hi -= 6; }

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, i16Hi >= 0 );

			_ui8RegVal = uint8_t( ((i16Hi & 0x0F) << 4) | (i16Lo & 0x0F) );

			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui8RegVal == 0x00 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui8RegVal & 0x80) != 0 );
		}
		else {
			const uint32_t ui32Result = uint32_t( ui8A ) - uint32_t( _ui8OpVal ) - (1 - ui8CarryIn);

			SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
				(((uint16_t( ui8A ) ^ uint16_t( _ui8OpVal )) & (uint16_t( ui8A ) ^ (uint16_t)ui32Result) & 0x0080) != 0) );

			_ui8RegVal = uint8_t( ui32Result );

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, ui32Result <= 0xFF );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui8RegVal == 0x00 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui8RegVal & 0x80) != 0 );
		}
	}

	/**
	 * Performs a 16-bit subtract-with-carry with an operand, setting flags C, N, V, and Z.
	 * Respects Decimal Mode (D) when enabled.
	 *
	 * \param _prCpu The CRicoh5A22 instance.
	 * \param _ui16RegVal The register value used in the operation.
	 * \param _ui16OpVal The operand value used in the operation.
	 */
	inline void CRicoh5A22::Sbc_16( CRicoh5A22 * _prCpu, uint16_t &_ui16RegVal, uint16_t _ui16OpVal ) {
		CRicoh5A22 & rCpu = (*_prCpu);
		const uint16_t ui16A = _ui16RegVal;
		const uint16_t ui16CarryIn = (rCpu.m_fsState.rRegs.ui8Status & C()) ? 1 : 0;

		if ( (rCpu.m_fsState.rRegs.ui8Status & D()) ) {
			uint16_t ui16Res = 0;
			int16_t i16Borrow = (1 - ui16CarryIn);

			for ( int32_t i = 0; i < 16; i += 4 ) {
				int16_t i16DigitSum = int16_t( (ui16A >> i) & 0x000F ) - int16_t( (_ui16OpVal >> i) & 0x000F ) - i16Borrow;
				
				if ( i == 12 ) {
					SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
						(((ui16A >> 12) ^ (_ui16OpVal >> 12)) & ((ui16A >> 12) ^ i16DigitSum) & 0x08) != 0 );
				}

				if ( i16DigitSum < 0 ) { i16DigitSum -= 6; }

				i16Borrow = (i16DigitSum < 0) ? 1 : 0;
				ui16Res |= uint16_t( (i16DigitSum & 0x000F) << i );
			}

			_ui16RegVal = ui16Res;

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, i16Borrow == 0 );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui16RegVal == 0x0000 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui16RegVal & 0x8000) != 0 );
		}
		else {
			const uint32_t ui32Result = uint32_t( ui16A ) - uint32_t( _ui16OpVal ) - (1 - ui16CarryIn);

			SetBit<V()>( rCpu.m_fsState.rRegs.ui8Status,
				(((uint32_t( ui16A ) ^ uint32_t( _ui16OpVal )) & (uint32_t( ui16A ) ^ (uint32_t)ui32Result) & 0x00008000) != 0) );

			_ui16RegVal = uint16_t( ui32Result );

			SetBit<C()>( rCpu.m_fsState.rRegs.ui8Status, ui32Result <= 0xFFFF );
			SetBit<Z()>( rCpu.m_fsState.rRegs.ui8Status, _ui16RegVal == 0x0000 );
			SetBit<N()>( rCpu.m_fsState.rRegs.ui8Status, (_ui16RegVal & 0x8000) != 0 );
		}
	}

#pragma warning( pop )

}	// namespace lsn
