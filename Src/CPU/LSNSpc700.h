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

#define LSN_SPC700_PUSH( VAL )													LSN_SPC700_INSTR_START_PHI2_WRITE_BUSB( (0x100 | uint8_t( m_fsState.rRegs.ui8Sp + _i8SOff )), (VAL) ); m_fsState.ui16SModify = uint16_t( int16_t( -1 + _i8SOff ) )
#define LSN_SPC700_POP( RESULT )												LSN_SPC700_INSTR_START_PHI2_READ_BUSA( (0x100 | uint8_t( m_fsState.rRegs.ui8Sp + _i8SOff )), (RESULT) ); m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) )

#define LSN_SPC700_UPDATE_PC													/*if LSN_LIKELY( m_fsState.bAllowWritingToPc ) */{ m_fsState.rRegs.ui16Pc += m_fsState.ui16PcModify; } m_fsState.ui16PcModify = 0
#define LSN_SPC700_UPDATE_S														m_fsState.rRegs.ui8Sp += m_fsState.ui16SModify; m_fsState.ui16SModify = 0

#ifndef LSN_R
#define LSN_R																	LSN_CT_READ
#endif	// #ifndef LSN_R
#ifndef LSN_W
#define LSN_W																	LSN_CT_WRITE
#endif	// #ifndef LSN_W
#ifndef LSN_N
#define LSN_N																	LSN_CT_NULL
#endif	// #ifndef LSN_N

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
//#define LSN_SPC700_CYCLES_DOC													1
#endif	// #ifdef LSN_SPC700_CPU_VERIFY


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


		// == Functions.
		/**
		 * Resets the CPU to a known state.
		 * 
		 * \tparam _bToKnown If true, the CPU is reset to a known state..
		 */
		template <bool _bToKnown = true>
		void																	Reset() {
			m_pfTickFunc = m_pfTickFuncCopy = &CSpc700::Tick_NextInstructionStd;
			//m_fsState.bBoundaryCrossed = false;
			m_fsState.ui16PcModify = 0;
			m_fsState.ui16SModify = 0;
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
				
				m_fsState.ui16Operand = 0;*/

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


	protected :
		// == Types.
		/** The full state structure for instructions. */
		LSN_ALIGN_STRUCT( 64 )
		struct LSN_FULL_STATE {
			const PfCycle *														pfCurInstruction = nullptr;															/**< The current instruction being executed. */
			LSN_REGISTERS														rRegs;																				/**< Registers. */

			union {
				uint8_t															ui8Operand[2];																		/**< The operand. */
				uint16_t														ui16Operand;																		/**< The operand. */
			};
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
			uint16_t															ui16SModify = 0;																	/**< The amount by which to modify S during the next Phi1. */
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
#endif	// #ifdef LSN_CPU_VERIFY


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// CYCLES
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		/**
		 * Generic null operation.
		 * 
		 * \tparam _ctReadWriteNull The cycle read/write/neither type.
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bBeginInstr If true, BeginInst() is called.
		 **/
		template <CSpc700::LSN_CYCLE_TYPE _ctReadWriteNull = CSpc700::LSN_CT_NULL, bool _bIncPc = false, bool _bAdjS = false, bool _bBeginInstr = false>
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
		 * Prepares to enter a new instruction.
		 *
		 * \tparam _bIncPc If true, PC is updated.
		 * \tparam _bAdjS If true, S is updated.
		 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
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
	 * Generic null operation.
	 * 
	 * \tparam _ctReadWriteNull The cycle read/write/neither type.
	 * \tparam _bIncPc If true, PC is updated.
	 * \tparam _bAdjS If true, S is updated.
	 * \tparam _bBeginInstr If true, BeginInst() is called.
	 **/
	template <CSpc700::LSN_CYCLE_TYPE _ctReadWriteNull, bool _bIncPc, bool _bAdjS, bool _bBeginInstr>
	inline void CSpc700::Null() {
		if constexpr ( _bBeginInstr ) {
			BeginInst<_bIncPc, _bAdjS>();
		}
		else {
#ifdef LSN_SPC700_CYCLES_DOC
			std::string sDebug = "\t";
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
			LSN_SPC700_INSTR_START_PHI1( _ctReadWriteNull );

			if constexpr ( _bIncPc ) {
#ifdef LSN_SPC700_CYCLES_DOC
				if ( int16_t( m_fsState.ui16PcModify ) < 0 ) {
					sDebug += "Dec. PC. ";
				}
				else {
					sDebug += "Inc. PC. ";
				}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
				LSN_SPC700_UPDATE_PC;
			}
			if constexpr ( _bAdjS ) {
#ifdef LSN_SPC700_CYCLES_DOC
				if LSN_UNLIKELY( m_fsState.bEmulationMode ) {
					if ( int16_t( m_fsState.ui16SModify ) < 0 ) {
						sDebug += "Dec. S.L by " + std::to_string( -int16_t( m_fsState.ui16SModify ) ) + " and set S.H to 1. ";
					}
					else if ( int16_t( m_fsState.ui16SModify ) > 0 ) {
						sDebug += "Inc. S.L by " + std::to_string( int16_t( m_fsState.ui16SModify ) ) + " and set S.H to 1. ";
					}
				}
				else {
					if ( int16_t( m_fsState.ui16SModify ) < 0 ) {
						sDebug += "Dec. S by " + std::to_string( -int16_t( m_fsState.ui16SModify ) ) + ". ";
					}
					else if ( int16_t( m_fsState.ui16SModify ) > 0 ) {
						sDebug += "Inc. S by " + std::to_string( int16_t( m_fsState.ui16SModify ) ) + ". ";
					}
				}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
				LSN_SPC700_UPDATE_S;
			}

			LSN_SPC700_NEXT_FUNCTION;

			LSN_SPC700_INSTR_END_PHI1;
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( sDebug.c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
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
			m_fsState.ui16SModify = uint16_t( int16_t( _i8SOff ) );
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
	 * \tparam _bCheckStartOfFunction If true, the LSN_INSTR_START_PHI1( true ) macro call is embedded.
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
#ifdef LSN_SPC700_CYCLES_DOC
			if LSN_UNLIKELY( m_fsState.bEmulationMode ) {
				if ( int16_t( m_fsState.ui16SModify ) < 0 ) {
					lsn::DebugA( ("\tDec. S.L by " + std::to_string( -int16_t( m_fsState.ui16SModify ) ) + " and set S.H to 1.").c_str() );
				}
				else if ( int16_t( m_fsState.ui16SModify ) > 0 ) {
					lsn::DebugA( ("\tInc. S.L by " + std::to_string( int16_t( m_fsState.ui16SModify ) ) + " and set S.H to 1.").c_str() );
				}
			}
			else {
				if ( int16_t( m_fsState.ui16SModify ) < 0 ) {
					lsn::DebugA( ("\tDec. S by " + std::to_string( -int16_t( m_fsState.ui16SModify ) ) + ".").c_str() );
				}
				else if ( int16_t( m_fsState.ui16SModify ) > 0 ) {
					lsn::DebugA( ("\tInc. S by " + std::to_string( int16_t( m_fsState.ui16SModify ) ) + ".").c_str() );
				}
			}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
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
