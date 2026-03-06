/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: An SPC700 processor.
 */


#pragma once

#include "../../LSNBirdSNES.h"
#include "../../Bus/LSNBusB.h"
#include "../../Foundation/LSNBits.h"
#include "../../System/LSNTickable.h"

#include <cassert>

#ifdef LSN_SPC700_CPU_VERIFY
#include <LSONJson.h>
#endif	// #ifdef LSN_SPC700_CPU_VERIFY

#define LSN_SPC700_INSTR_START_PHI1( ISREAD )									/*m_fsState.bIsReadCycle = (ISREAD)*/
#define LSN_SPC700_INSTR_END_PHI1
#define LSN_SPC700_INSTR_START_PHI2_READ_BUSB( ADDR, RESULT )					RESULT = m_bbBusB.Read( uint16_t( ADDR ) )
#define LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( ADDR, VAL )						m_bbBusB.Write( uint16_t( ADDR ), uint8_t( VAL ) )
#define LSN_SPC700_INSTR_END_PHI2

#define LSN_SPC700_NEXT_FUNCTION_BY( AMT )										m_fsState.ui8FuncIndex += AMT
#define LSN_SPC700_NEXT_FUNCTION												LSN_SPC700_NEXT_FUNCTION_BY( 1 )
#define LSN_SPC700_FINISH_INST( CHECK_INTERRUPTS )								if constexpr ( CHECK_INTERRUPTS ) { LSN_SPC700_CHECK_INTERRUPTS; } LSN_SPC700_NEXT_FUNCTION

#ifdef LSN_SPC700_CPU_VERIFY
#define LSN_SPC700_CHECK_INTERRUPTS												m_bHandleNmi |= m_bDetectedNmi
#else
#define LSN_SPC700_CHECK_INTERRUPTS												//if ( !(m_fsState.rRegs.ui8Status & I()) ) { m_bHandleIrq = m_bIrqStatusPhi1Flag; } m_bHandleNmi |= m_bDetectedNmi
#endif	// #ifdef LSN_SPC700_CPU_VERIFY

#define LSN_SPC700_PUSH( VAL )													LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( (0x100 | uint8_t( m_fsState.rRegs.ui8Sp + _i8SOff )), (VAL) ); m_fsState.ui8SModify = uint8_t( int8_t( -1 + _i8SOff ) )
#define LSN_SPC700_POP( RESULT )												LSN_SPC700_INSTR_START_PHI2_READ_BUSA( (0x100 | uint8_t( m_fsState.rRegs.ui8Sp + _i8SOff )), (RESULT) ); m_fsState.ui8SModify = uint8_t( int8_t( _i8SOff ) )

#define LSN_SPC700_UPDATE_PC													/*if LSN_LIKELY( m_fsState.bAllowWritingToPc ) */{ m_fsState.rRegs.ui16Pc += m_fsState.ui16PcModify; } m_fsState.ui16PcModify = 0
#define LSN_SPC700_UPDATE_S														m_fsState.rRegs.ui8Sp += m_fsState.ui8SModify; m_fsState.ui8SModify = 0

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

#ifdef LSN_SPC700_CPU_VERIFY
#define LSN_SPC700_CYCLES_DOC													1
#endif	// #ifdef LSN_SPC700_CPU_VERIFY
#ifdef LSN_SPC700_CYCLES_DOC
#define LSN_SPC700_PRINT_STACK																																	\
	if ( int8_t( m_fsState.ui8SModify ) < 0 ) { lsn::DebugA( ("Dec. SP by " + std::to_string( -int8_t( m_fsState.ui8SModify ) ) + ". ").c_str() ); }			\
	else if ( int8_t( m_fsState.ui8SModify ) > 0 ) { lsn::DebugA( ("Inc. SP by " + std::to_string( int8_t( m_fsState.ui8SModify ) ) + ". ").c_str() ); }
#define LSN_SPC700_PRINT_PC																																		\
	if ( int16_t( m_fsState.ui16PcModify ) < 0 ) { lsn::DebugA( "Dec. PC. " ); }																				\
	else if ( int16_t( m_fsState.ui16PcModify ) > 0 ) { lsn::DebugA( "Inc. PC. " ); }
#else
#define LSN_SPC700_PRINT_STACK
#define LSN_SPC700_PRINT_PC
#endif	// #ifdef LSN_SPC700_CYCLES_DOC


namespace lsn {

#pragma warning( push )
#pragma warning( disable : 4324 )	// warning C4324: 'lsn::CSpc700::LSN_FULL_STATE': structure was padded due to alignment specifier
#pragma warning( disable : 26495 )	// warning C26495: Variable 'lsn::CSpc700::LSN_REGISTERS::ui8X' is uninitialized. Always initialize a member variable (type.6).

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
			LSN_M_MAX_INSTR_CYCLE_COUNT											= 12,
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

		/** Register types. */
		enum LSN_REG_TYPE : uint8_t {
#define LSN_INST( NAME, DESC )													LSN_RT_ ## NAME,
#include "LSNSpc700Regs.inl"
#undef LSN_INST
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


		// == Functions.
		/**
		 * Resets the CPU to a known state.
		 * 
		 * \tparam _bToKnown If true, the CPU is reset to a known state.
		 */
		template <bool _bToKnown = true>
		void																	Reset() {
			m_pfTickFunc = m_pfTickFuncCopy = &CSpc700::Tick_NextInstructionStd;
			//m_fsState.bBoundaryCrossed = false;
			m_fsState.ui16PcModify = 0;
			m_fsState.ui8SModify = 0;
			m_fsState.ui16OpCode = 0;
			
#ifdef LSN_SPC700_CPU_VERIFY
			//m_fsState.bAllowWritingToPc = true;
			/*m_bIsReset = m_bBrkIsReset = false;*/
#else
			//m_fsState.bAllowWritingToPc = false;
			/*m_bIsReset = m_bBrkIsReset = true;*/
#endif	// #ifdef LSN_SPC700_CPU_VERIFY

			m_fsState.pfCurInstruction = m_iInstructionSet[m_fsState.ui16OpCode].pfHandler;


			if constexpr ( _bToKnown ) {
				/*std::memset( &m_fsState.rRegs, 0, sizeof( m_fsState.rRegs ) );
				m_ui64CycleCount = 0ULL;
				
				m_fsState.ui8Operand = 0;*/

				//m_ui16DmaCounter = 0;
				//m_ui16DmaAddress = 0;

				//m_ui8DmaPos = m_ui8DmaValue = 0;
				/*m_bNmiStatusLine = false;
				m_bLastNmiStatusLine = false;
				m_bDetectedNmi = false;
				m_bHandleNmi = false;
				m_ui8IrqStatusLine = 0;
				m_bIrqSeenLowPhi2 = false;
				m_bIrqStatusPhi1Flag = false;
				m_bHandleIrq = false;
				m_bRdyLow = false;*/
				//m_ui8RdyOffCnt = 0;

				/*std::memset( m_ui8Inputs, 0, sizeof( m_ui8Inputs ) );
				std::memset( m_ui8InputsState, 0, sizeof( m_ui8InputsState ) );
				std::memset( m_ui8InputsPoll, 0, sizeof( m_ui8InputsPoll ) );*/
			}
		}

		/**
		 * Performs a single PHI1 update.
		 */
		void																	Tick();

		/**
		 * Performs a single PHI2 update.
		 **/
		void																	TickPhi2();

		/** Fetches the next opcode and begins the next instruction. */
		inline void																Tick_NextInstructionStd();

		/** Performs a cycle inside an instruction. */
		inline void																Tick_InstructionCycleStd();

#ifdef LSN_SPC700_CPU_VERIFY
		/**
		 * Runs a test given a JSON's value representing the test to run.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \return Returns -1 on error, the number of cycles otherwise.
		 */
		int32_t																	RunJsonTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest );

		/**
		 * Gets the instruction table.
		 * 
		 * \return Returns a constant pointer to the instruction table (256 entries).
		 **/
		static inline const LSN_INSTR *											InstrTable() { return m_iInstructionSet; }
#endif	// #ifdef LSN_SPC700_CPU_VERIFY

		/**
		 * Reg-types to string.
		 * 
		 * \param _rtType The register type to name.
		 */
		static constexpr const char *											RegTypeToString( LSN_REG_TYPE _rtType ) {
			switch ( _rtType ) {
#define LSN_INST( NAME, DESC )													case LSN_RT_ ## NAME : { return DESC; }
#include "LSNSpc700Regs.inl"
#undef LSN_INST
				default : { assert( 0 ); return ""; }
			}
		}


	protected :
		// == Types.
		/** The full state structure for instructions. */
		LSN_ALIGN_STRUCT( 64 )
		struct LSN_FULL_STATE {
			const PfCycle *														pfCurInstruction = nullptr;															/**< The current instruction being executed. */
			LSN_REGISTERS														rRegs;																				/**< Registers. */
			uint8_t																ui8Operand;																			/**< The operand. */
			union {
				uint8_t															ui8Address[2];																		/**< An address loaded into memory before transfer to a register such as PC. */
				uint16_t														ui16Address;																		/**< An address loaded into memory before transfer to a register such as PC. */
			};
			union {
				uint8_t															ui8Pointer[2];																		/**< An address loaded into memory for indirect access. */
				uint16_t														ui16Pointer;																		/**< An address loaded into memory for indirect access. */
			};
			uint16_t															ui16OpCode = 0;																		/**< The current opcode. */
			uint16_t															ui16PcModify = 0;																	/**< The amount by which to modify PC during the next Phi1. */
			uint8_t																ui8SModify = 0;																		/**< The amount by which to modify S during the next Phi1. */
			uint8_t																ui8FuncIndex = 0;																	/**< The function index. */

			//bool																bIsReadCycle = true;																/**< Is the current cycle a read? */
			//bool																bBoundaryCrossed = false;															/**< Did we cross a page boundary? */
			//bool																bPushB = false;																		/**< Push the B flag with the status byte? */
			//bool																bAllowWritingToPc = true;															/**< Allow writing to PC? */
			//bool																bTakeJump;																			/**< Determines if a branch is taken. */
		} LSN_ALIGN_STRUCT_END( 64 );


		// == Members.
		uint64_t																m_ui64CycleCount = 0;																/**< The cycle count. */
		PfTicks																	m_pfTickFunc = nullptr;																/**< The current tick function (called by Tick()). */
		PfTicks																	m_pfTickFuncCopy = nullptr;															/**< A copy of the current tick, used to restore the intended original tick when control flow is changed by DMA transfers. */
		CBusB &																	m_bbBusB;																			/**< A reference to the bus. */
		LSN_FULL_STATE															m_fsState;																			/**< Everything a standard instruction-cycle function can modify.  Backed up at the start of the first DMA read cycle and restored at the end after the read address for that cycle has been calculated. */
		static LSN_INSTR														m_iInstructionSet[256];																/**< The instruction set. */


#ifdef LSN_SPC700_CPU_VERIFY
		// == Types.
		struct LSN_CPU_VERIFY_RAM {
			uint32_t															ui32Addr;
			uint8_t																ui8Value;
		};

		struct LSN_CPU_VERIFY_STATE {
			LSN_REGISTERS														cvrRegisters;
			std::vector<LSN_CPU_VERIFY_RAM>										vRam;
			bool																bEmulationMode;
		};

		struct LSN_CPU_VERIFY_CYCLE {
			uint32_t															ui32Addr;
			uint8_t																ui8Value;
			std::string															sStatus;
			bool																bNoReadOrWrite;
		};

		struct LSN_CPU_VERIFY_OBJ {
			std::string															sName;
			LSN_CPU_VERIFY_STATE												cvsStart;
			LSN_CPU_VERIFY_STATE												cvsEnd;
			std::vector<LSN_CPU_VERIFY_CYCLE>									vCycles;
		};


		// == Members.
		bool																	m_bDetectedNmi = false;																/**< Only for verification of proper cycle structure.  At run-time, interrupts are not checked/handled. */
		bool																	m_bHandleNmi = false;																/**< Only for verification of proper cycle structure.  At run-time, interrupts are not checked/handled. */


		// == Functions.
		/**
		 * Given a JSON object and the value for the test to run, this loads the test and fills a LSN_SPC700_CPU_VERIFY structure.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \param _cvoTest The test structure to fill out.
		 * \return Returns true if the JSON data was successfully extracted and the test created.
		 */
		bool																	GetTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest, LSN_CPU_VERIFY_OBJ &_cvoTest );

		/**
		 * Fills out a LSN_CPU_VERIFY_STATE structure given a JSON "initial" or "final" member.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvState The bject member representing the state to load.
		 * \param _cvsState The state structure to fill.
		 * \return Returns true if the state was loaded.
		 */
		bool																	LoadState( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvState, LSN_CPU_VERIFY_STATE &_cvsState );
#endif	// #ifdef LSN_SPC700_CPU_VERIFY


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// CYCLES
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		/**
		 * Fetches the target and increments PC.
		 * 
		 * \tparam _rtRegType The fetch target.
		 **/
		template <LSN_REG_TYPE _rtRegType = LSN_RT_OPERAND>
		void																	Fetch_IncPc_Phi2();

		/**
		 * Generic null operation.
		 * 
		 * \tparam _ctReadWriteNull The cycle read/write/neither type.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bBeginInstr If true, BeginInst() is called.
		 **/
		template <LSN_CYCLE_TYPE _ctReadWriteNull = LSN_CT_NULL, bool _bIncPc = false, bool _bAdjS = false, bool _bBeginInstr = false>
		void																	Null();

		/**
		 * Generic null operation on PHI2.  Sets the bus access speed to Fast.
		 * 
		 * \tparam _i8SOff If not INT8_MIN, S is scheduled to be adjusted by the given amount on the next PHI1.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <int8_t _i8SOff = INT8_MIN, bool _bEndInstr = false>
		void																	Null_Phi2();

		/**
		 * Calculates the Direct Page target address from the current Operand, storing the result in either Address or Pointer.
		 *
		 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
		 * \tparam _bIncPc If true, PC is updated.
		 **/
		template <bool _bTo = LSN_TO_A, bool _bIncPc = false>
		void																	Operand_To_DirectPage();

		/**
		 * Pushes a register type.
		 * 
		 * \tparam _rtRegType The register type to push.
		 * \tparam _i8SOff If not INT8_MIN, S is scheduled to be adjusted by the given amount on the next PHI1.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <LSN_REG_TYPE _rtRegType, int8_t _i8SOff = 0, bool _bEndInstr = false>
		void																	Push_Phi2();

		/**
		 * Reads a given specific address.
		 * 
		 * \tparam _ui16Addr The read to read.
		 * \tparam _rtRegType The destination to which to store the read.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <uint16_t _ui16Addr, LSN_REG_TYPE _rtRegType, bool _bEndInstr = false>
		void																	Read_Phi2();

		/**
		 * Reads from the current pointer or address and stores into the given register type.
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the address is read to the destination, otherwise the pointer is read to the destination.
		 * \tparam _rtRegType The destination to which to store the read.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, LSN_REG_TYPE _rtRegType = LSN_RT_OPERAND, bool _bEndInstr = false>
		void																	Read_PtrOrAddr_L_Phi2();

		/**
		 * Reads from the current pointer or address + 1 and stores into the given register type.
		 * 
		 * \tparam _bFrom If LSN_FROM_A, the address is read to the destination, otherwise the pointer is read to the destination.
		 * \tparam _rtRegType The destination to which to store the read.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bFrom = LSN_FROM_A, LSN_REG_TYPE _rtRegType = LSN_RT_OPERAND, bool _bEndInstr = false>
		void																	Read_PtrOrAddr_H_Phi2();

		/**
		 * Sets a bit in Operand to the given value.
		 * 
		 * \tparam _ui8Bit The bit to set to 0 or 1.
		 * \tparam _ui8Val The value to which to set the given bit (must be 0 or 1).
		 **/
		template <uint8_t _ui8Bit, uint8_t _ui8Val>
		void																	Set1();

		/**
		 * Writes the given register type to the current pointer or address.
		 * 
		 * \tparam _bTo If LSN_TO_A, the register type is written to the current address, otherwise it is written to the current pointer.
		 * \tparam _rtRegType The source to write to the current address or pointer.
		 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
		 **/
		template <bool _bTo = LSN_TO_A, LSN_REG_TYPE _rtRegType = LSN_RT_OPERAND, bool _bEndInstr = false>
		void																	Write_PtrOrAddr_L_Phi2();

		/**
		 * Prepares to enter a new instruction.
		 *
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bCheckStartOfFunction If true, the LSN_SPC700_INSTR_START_PHI1( true ) macro call is embedded.
		 */
		template <bool _bIncPc = false, bool _bAdjS = false, bool _bCheckStartOfFunction = true>
		inline void																BeginInst();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Fuctions.
	/** Fetches the next opcode and begins the next instruction. */
	inline void CSpc700::Tick_NextInstructionStd() {
		BeginInst();
	}

	/** Performs a cycle inside an instruction. */
	inline void CSpc700::Tick_InstructionCycleStd() {
		//(this->*m_iInstructionSet[m_fsState.ui16OpCode].pfHandler[m_fsState.bEmulationMode][m_fsState.ui8FuncIndex])();
		(this->*m_fsState.pfCurInstruction[m_fsState.ui8FuncIndex])();
	}

	/**
	 * Fetches the target and increments PC.
	 * 
	 * \tparam _rtRegType The fetch target.
	 **/
	template <CSpc700::LSN_REG_TYPE _rtRegType>
	inline void CSpc700::Fetch_IncPc_Phi2() {
		if constexpr ( _rtRegType == LSN_RT_OPCODE ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.ui16OpCode );
			m_fsState.pfCurInstruction = m_iInstructionSet[m_fsState.ui16OpCode].pfHandler;
		}
		/*else if constexpr ( _rtRegType == LSN_RT_PC_L ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pc[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PC_H ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Pc[1] );
		}*/
		else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.ui8Operand );
		}
		/*else if constexpr ( _rtRegType == LSN_RT_X ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8X );
		}
		else if constexpr ( _rtRegType == LSN_RT_Y ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Y );
		}
		else if constexpr ( _rtRegType == LSN_RT_A ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8A );
		}
		else if constexpr ( _rtRegType == LSN_RT_SP ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Sp );
		}
		else if constexpr ( _rtRegType == LSN_RT_STATUS ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.rRegs.ui8Status );
		}*/
		else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.ui8Address[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_ADDR_H ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.ui8Address[1] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.ui8Pointer[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PTR_H ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.rRegs.ui16Pc, m_fsState.ui8Pointer[1] );
		}
		
		m_fsState.ui16PcModify = 1;

#ifdef LSN_SPC700_CYCLES_DOC
		//lsn::DebugA( "Read PC\tStore as Operand." );
		lsn::DebugA( std::format( "Read PC\tStore as {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		LSN_SPC700_NEXT_FUNCTION;

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Generic null operation.
	 * 
	 * \tparam _ctReadWriteNull The cycle read/write/neither type.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bBeginInstr If true, BeginInst() is called.
	 **/
	template <LSN_CYCLE_TYPE _ctReadWriteNull, bool _bIncPc, bool _bAdjS, bool _bBeginInstr>
	inline void CSpc700::Null() {
		if constexpr ( _bBeginInstr ) {
			BeginInst<_bIncPc, _bAdjS>();
		}
		else {
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( "\t" );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
			LSN_SPC700_INSTR_START_PHI1( _ctReadWriteNull );

			if constexpr ( _bIncPc ) {
				LSN_SPC700_PRINT_PC;
				LSN_SPC700_UPDATE_PC;
			}
			if constexpr ( _bAdjS ) {
				LSN_SPC700_PRINT_STACK;
				LSN_SPC700_UPDATE_S;
			}

			LSN_SPC700_NEXT_FUNCTION;

			LSN_SPC700_INSTR_END_PHI1;
		}
	}

	/**
	 * Generic null operation on PHI2.  Sets the bus access speed to Fast.
	 * 
	 * \tparam _i8SOff If not INT8_MIN, S is scheduled to be adjusted by the given amount on the next PHI1.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <int8_t _i8SOff, bool _bEndInstr>
	inline void CSpc700::Null_Phi2() {
#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		if constexpr ( _i8SOff != INT8_MIN ) {
			m_fsState.ui8SModify = uint8_t( int8_t( _i8SOff ) );
		}
		if constexpr ( _bEndInstr ) {
			LSN_SPC700_FINISH_INST( true );
		}
		else {
			LSN_SPC700_NEXT_FUNCTION;
		}

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Calculates the Direct Page target address from the current Operand, storing the result in either Address or Pointer.
	 *
	 * \tparam _bTo If LSN_TO_A, the value is stored to m_fsState.ui16Address, otherwise it is stored to m_fsState.ui16Pointer.
	 * \tparam _bIncPc If true, PC is updated.
	 **/
	template <bool _bTo, bool _bIncPc>
	inline void CSpc700::Operand_To_DirectPage() {
		LSN_SPC700_INSTR_START_PHI1( true );

		if constexpr ( _bTo == LSN_TO_A ) {
			m_fsState.ui16Address = m_fsState.ui8Operand | ((m_fsState.rRegs.ui8Status & P()) << 3);
		}
		else {
			m_fsState.ui16Pointer = m_fsState.ui8Operand | ((m_fsState.rRegs.ui8Status & P()) << 3);
		}

#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( "\t" );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		if constexpr ( _bIncPc ) {
			LSN_SPC700_PRINT_PC;
			LSN_SPC700_UPDATE_PC;
		}

#ifdef LSN_SPC700_CYCLES_DOC
		if constexpr ( _bTo == LSN_TO_A ) {
			lsn::DebugA( "Address = (Operand | ((SPW & P flag) << 3)." );
		}
		else {
			lsn::DebugA( "Pointer = (Operand | ((SPW & P flag) << 3)." );
		}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		LSN_SPC700_NEXT_FUNCTION;

		LSN_SPC700_INSTR_END_PHI1;
	}

	/**
	 * Pushes a register type.
	 * 
	 * \tparam _rtRegType The register type to push.
	 **/
	template <CSpc700::LSN_REG_TYPE _rtRegType, int8_t _i8SOff, bool _bEndInstr>
	inline void CSpc700::Push_Phi2() {
		if constexpr ( _rtRegType == LSN_RT_PC_L ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8Pc[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PC_H ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8Pc[1] );
		}
		else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
			LSN_SPC700_PUSH( m_fsState.ui8Operand );
		}
		else if constexpr ( _rtRegType == LSN_RT_X ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8X );
		}
		else if constexpr ( _rtRegType == LSN_RT_Y ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8Y );
		}
		else if constexpr ( _rtRegType == LSN_RT_A ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8A );
		}
		else if constexpr ( _rtRegType == LSN_RT_SP ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8Sp );
		}
		else if constexpr ( _rtRegType == LSN_RT_STATUS ) {
			LSN_SPC700_PUSH( m_fsState.rRegs.ui8Status );
		}
		else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
			LSN_SPC700_PUSH( m_fsState.ui8Address[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_ADDR_H ) {
			LSN_SPC700_PUSH( m_fsState.ui8Address[1] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
			LSN_SPC700_PUSH( m_fsState.ui8Pointer[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PTR_H ) {
			LSN_SPC700_PUSH( m_fsState.ui8Pointer[1] );
		}

#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( std::format( "Write to u8(S.L{:+}) | $0100\tPush {} onto stack.", _i8SOff, RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_SPC700_FINISH_INST( true );
		}
		else {
			LSN_SPC700_NEXT_FUNCTION;
		}

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Reads a given specific address.
	 * 
	 * \tparam _ui16Addr The read to read.
	 * \tparam _rtRegType The destination to which to store the read.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <uint16_t _ui16Addr, CSpc700::LSN_REG_TYPE _rtRegType, bool _bEndInstr>
	inline void CSpc700::Read_Phi2() {
		if constexpr ( _rtRegType == LSN_RT_PC_L ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8Pc[0] );
			m_fsState.ui16PcModify = 0;
		}
		else if constexpr ( _rtRegType == LSN_RT_PC_H ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8Pc[1] );
			m_fsState.ui16PcModify = 0;
		}
		else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.ui8Operand );
		}
		else if constexpr ( _rtRegType == LSN_RT_X ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8X );
		}
		else if constexpr ( _rtRegType == LSN_RT_Y ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8Y );
		}
		else if constexpr ( _rtRegType == LSN_RT_A ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8A );
		}
		else if constexpr ( _rtRegType == LSN_RT_SP ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8Sp );
		}
		else if constexpr ( _rtRegType == LSN_RT_STATUS ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.rRegs.ui8Status );
		}
		else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.ui8Address[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_ADDR_H ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.ui8Address[1] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.ui8Pointer[0] );
		}
		else if constexpr ( _rtRegType == LSN_RT_PTR_H ) {
			LSN_SPC700_INSTR_START_PHI2_READ_BUSB( _ui16Addr, m_fsState.ui8Pointer[1] );
		}

#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( std::format( "Read ${:04X}\tStore as {}.", _ui16Addr, RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		if constexpr ( _bEndInstr ) {
			LSN_SPC700_FINISH_INST( true );
		}
		else {
			LSN_SPC700_NEXT_FUNCTION;
		}

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Reads from the current pointer or address and stores into the given register type.
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the address is read to the destination, otherwise the pointer is read to the destination.
	 * \tparam _rtRegType The destination to which to store the read.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, CSpc700::LSN_REG_TYPE _rtRegType, bool _bEndInstr>
	inline void CSpc700::Read_PtrOrAddr_L_Phi2() {
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if constexpr ( _rtRegType == LSN_RT_PC_L ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address, m_fsState.rRegs.ui8Pc[0] );
				m_fsState.ui16PcModify = 0;
			}
			else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address, m_fsState.ui8Operand );
			}
			else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address, m_fsState.ui8Address[0] );
			}
			else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address, m_fsState.ui8Pointer[0] );
			}
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( std::format( "Read Address\tStore as {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}
		else {
			if constexpr ( _rtRegType == LSN_RT_PC_L ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer, m_fsState.rRegs.ui8Pc[0] );
				m_fsState.ui16PcModify = 0;
			}
			else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer, m_fsState.ui8Operand );
			}
			else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer, m_fsState.ui8Address[0] );
			}
			else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer, m_fsState.ui8Pointer[0] );
			}
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( std::format( "Read Pointer\tStore as {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}

		if constexpr ( _bEndInstr ) {
			LSN_SPC700_FINISH_INST( true );
		}
		else {
			LSN_SPC700_NEXT_FUNCTION;
		}

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Reads from the current pointer or address + 1 and stores into the given register type.
	 * 
	 * \tparam _bFrom If LSN_FROM_A, the address is read to the destination, otherwise the pointer is read to the destination.
	 * \tparam _rtRegType The destination to which to store the read.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bFrom, CSpc700::LSN_REG_TYPE _rtRegType, bool _bEndInstr>
	inline void CSpc700::Read_PtrOrAddr_H_Phi2() {
		if constexpr ( _bFrom == LSN_FROM_A ) {
			if constexpr ( _rtRegType == LSN_RT_PC_H ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address + 1, m_fsState.rRegs.ui8Pc[1] );
				m_fsState.ui16PcModify = 0;
			}
			else if constexpr ( _rtRegType == LSN_RT_ADDR_H ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address + 1, m_fsState.ui8Address[1] );
			}
			else if constexpr ( _rtRegType == LSN_RT_PTR_H ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Address + 1, m_fsState.ui8Pointer[1] );
			}
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( std::format( "Read Address + 1\tStore as {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}
		else {
			if constexpr ( _rtRegType == LSN_RT_PC_H ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer + 1, m_fsState.rRegs.ui8Pc[1] );
				m_fsState.ui16PcModify = 0;
			}
			else if constexpr ( _rtRegType == LSN_RT_ADDR_H ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer + 1, m_fsState.ui8Address[1] );
			}
			else if constexpr ( _rtRegType == LSN_RT_PTR_H ) {
				LSN_SPC700_INSTR_START_PHI2_READ_BUSB( m_fsState.ui16Pointer + 1, m_fsState.ui8Pointer[1] );
			}
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( std::format( "Read Pointer + 1\tStore as {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}

		if constexpr ( _bEndInstr ) {
			LSN_SPC700_FINISH_INST( true );
		}
		else {
			LSN_SPC700_NEXT_FUNCTION;
		}

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Sets a bit in Operand to the given value.
	 * 
	 * \tparam _ui8Bit The bit to set to 0 or 1.
	 * \tparam _ui8Val The value to which to set the given bit (must be 0 or 1).
	 **/
	template <uint8_t _ui8Bit, uint8_t _ui8Val>
	inline void CSpc700::Set1() {
		LSN_SPC700_INSTR_START_PHI1( false );
		m_fsState.ui8Operand = (m_fsState.ui8Operand & ~(1 << _ui8Bit)) | (_ui8Val << _ui8Bit);

#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( std::format( "Operand = (Operand & ~{}) | {}.", (1 << _ui8Bit), _ui8Val << _ui8Bit ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		LSN_SPC700_NEXT_FUNCTION;

		LSN_SPC700_INSTR_END_PHI1;
	}

	/**
	 * Writes the given register type to the current pointer or address.
	 * 
	 * \tparam _bTo If LSN_TO_A, the register type is written to the current address, otherwise it is written to the current pointer.
	 * \tparam _rtRegType The source to write to the current address or pointer.
	 * \tparam _bEndInstr Indicates the PHI2 that polls interrupts, typically the last PHI2 in the instruction.
	 **/
	template <bool _bTo, CSpc700::LSN_REG_TYPE _rtRegType, bool _bEndInstr >
	inline void CSpc700::Write_PtrOrAddr_L_Phi2() {
		if constexpr ( _bTo == LSN_TO_A ) {
			if constexpr ( _rtRegType == LSN_RT_PC_L ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Address, m_fsState.rRegs.ui8Pc[0] );
			}
			else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Address, m_fsState.ui8Operand );
			}
			else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Address, m_fsState.ui8Address[0] );
			}
			else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Address, m_fsState.ui8Pointer[0] );
			}
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( std::format( "Write to Address\tWrite {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}
		else {
			if constexpr ( _rtRegType == LSN_RT_PC_L ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Pointer, m_fsState.rRegs.ui8Pc[0] );
			}
			else if constexpr ( _rtRegType == LSN_RT_OPERAND ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Pointer, m_fsState.ui8Operand );
			}
			else if constexpr ( _rtRegType == LSN_RT_ADDR_L ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Pointer, m_fsState.ui8Address[0] );
			}
			else if constexpr ( _rtRegType == LSN_RT_PTR_L ) {
				LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( m_fsState.ui16Pointer, m_fsState.ui8Pointer[0] );
			}
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( std::format( "Write to Pointer\tWrite {}.", RegTypeToString( _rtRegType ) ).c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}

		if constexpr ( _bEndInstr ) {
			LSN_SPC700_FINISH_INST( true );
		}
		else {
			LSN_SPC700_NEXT_FUNCTION;
		}

		LSN_SPC700_INSTR_END_PHI2;
	}

	/**
	 * Prepares to enter a new instruction.
	 *
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bCheckStartOfFunction If true, the LSN_SPC700_INSTR_START_PHI1( true ) macro call is embedded.
	 */
	template <bool _bIncPc, bool _bAdjS, bool _bCheckStartOfFunction>
	inline void CSpc700::BeginInst() {
		if constexpr ( _bCheckStartOfFunction ) {
			LSN_SPC700_INSTR_START_PHI1( true );
		}

		if constexpr ( _bIncPc ) {
			LSN_SPC700_UPDATE_PC;
		}

		if constexpr ( _bAdjS ) {
			LSN_SPC700_PRINT_STACK;
			LSN_SPC700_UPDATE_S;
		}

		// Enter normal instruction context.
		m_fsState.ui8FuncIndex = 0;
		m_pfTickFunc = m_pfTickFuncCopy = &CSpc700::Tick_InstructionCycleStd;
		//m_fsState.bBoundaryCrossed = false;
		LSN_SPC700_INSTR_END_PHI1;
	}

#pragma warning( pop )

}	// namespace lsn
