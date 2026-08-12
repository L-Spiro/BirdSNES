/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: An SPC700 processor.
 */

#include "LSNSpc700.h"


namespace lsn {

	// == Members.
#include "LSNSpc700CycleFuncs.inl"

	CSpc700::CSpc700( CBusB &_bBusB ) :
		m_bbBusB( _bBusB ) {
		m_ui64MasterClock = LSN_CS_SPC700_MASTER;
		m_ui64MasterDiv = LSN_CS_SPC700_MASTER_DIVISOR;
		m_ui8Speed = LSN_CS_SPC700_CPU_DIVISOR;
	}
	CSpc700::~CSpc700() {
	}

	// == Functions.
	/**
	 * Performs a single PHI1 update.
	 */
	void CSpc700::Tick() {
		(this->*m_pfTickFunc)();
	}

	/**
	 * Performs a single PHI2 update.
	 **/
	void CSpc700::TickPhi2() {
		(this->*m_pfTickFunc)();

		++m_ui64CycleCount;
	}

#ifdef LSN_SPC700_CPU_VERIFY
	/**
	 * Runs a test given a JSON's value representing the test to run.
	 *
	 * \param _jJson The JSON file.
	 * \param _jvTest The test to run.
	 * \return Returns -1 on error, the number of cycles otherwise.
	 */
	int32_t CSpc700::RunJsonTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest ) {
		LSN_CPU_VERIFY_OBJ cvoVerifyMe;
		if ( !GetTest( _jJson, _jvTest, cvoVerifyMe ) ) { return -1; }

		// Create the initial state.
		Reset<true>();
		m_bbBusB.ApplyBasicMapping();				// Set default read/write functions.
		m_ui64CycleCount = 0;
		
		m_fsState.rRegs.ui8A = cvoVerifyMe.cvsStart.cvrRegisters.ui8A;
		m_fsState.rRegs.ui8Sp = cvoVerifyMe.cvsStart.cvrRegisters.ui8Sp;
		m_fsState.rRegs.ui8X = cvoVerifyMe.cvsStart.cvrRegisters.ui8X;
		m_fsState.rRegs.ui8Y = cvoVerifyMe.cvsStart.cvrRegisters.ui8Y;
		
		m_fsState.rRegs.ui8Status = cvoVerifyMe.cvsStart.cvrRegisters.ui8Status;
		m_fsState.rRegs.ui16Pc = cvoVerifyMe.cvsStart.cvrRegisters.ui16Pc;

		{
			for ( auto I = cvoVerifyMe.cvsStart.vRam.size(); I--; ) {
				m_bbBusB.Write( uint16_t( cvoVerifyMe.cvsStart.vRam[I].ui32Addr ), cvoVerifyMe.cvsStart.vRam[I].ui8Value );
			}
		}

		/*if ( "2b e 42" == cvoVerifyMe.sName ) {
			volatile int ghg = 0;
		}*/
		// Tick once for each cycle.
		m_bbBusB.ReadWriteLog().clear();
		//BeginInst();
		/*m_bbBusB.ReadWriteLog().push_back( {} );
		m_fsState.ui16Operand = m_bbBusB.Read( m_fsState.rRegs.ui16Pc );
		m_fsState.ui16PcModify = 1;*/

		int32_t i32Cnt = 0;
#ifdef LSN_SPC700_CYCLES_DOC
		
		std::string sLine;
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		for ( auto I = cvoVerifyMe.vCycles.size(); I--; ) {
			m_bbBusB.ReadWriteLog().push_back( {} );
#ifdef LSN_SPC700_CYCLES_DOC
			if ( i32Cnt ) {
				lsn::DebugA( (std::to_string( i32Cnt ) + ".1\t").c_str() );
			}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
			Tick();

#ifdef LSN_SPC700_CYCLES_DOC
			if ( i32Cnt ) {
				lsn::DebugA( ("\r\n" + std::to_string( i32Cnt ) + ".2\t").c_str() );
			}
			else {
				lsn::DebugA( " -X.2\t" );
			}
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
			++i32Cnt;
			TickPhi2();
#ifdef LSN_SPC700_CYCLES_DOC
			lsn::DebugA( "\r\n" );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		}
#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( (std::to_string( i32Cnt ) + ".1\t").c_str() );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC
		Tick();
#ifdef LSN_SPC700_CYCLES_DOC
		lsn::DebugA( (std::string( "\r\n" ) + std::to_string( i32Cnt ) + ".2\tRead PC\tStore as OpCode.\r\n").c_str() );
		lsn::DebugA( " +X.1\t\t\r\n\r\n\r\n" );
#endif	// #ifdef LSN_SPC700_CYCLES_DOC

		

		bool bErrored = false;
		// Verify.
		if ( m_fsState.ui8FuncIndex != 0 ) {
			if ( m_iInstructionSet[m_fsState.ui16OpCode].iInstruction != LSN_I_SLEEP && m_iInstructionSet[m_fsState.ui16OpCode].iInstruction != LSN_I_STOP ) {
				lsn::DebugA( "\r\nDid not end on BeginInst().\r\n" );
				bErrored = true;
			}
		}

#define LSN_VURIFFY( REG )																																											\
	if ( m_fsState.rRegs.REG != cvoVerifyMe.cvsEnd.cvrRegisters.REG ) {																																\
		lsn::DebugA( cvoVerifyMe.sName.c_str() );																																					\
		lsn::DebugA( "\r\nCPU Failure: " # REG "\r\n" );																																			\
		lsn::DebugA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.cvsEnd.cvrRegisters.REG ) + std::string( " Got: " ) + std::to_string( m_fsState.rRegs.REG ) ).c_str() );				\
		lsn::DebugA( "\r\n\r\n" ); bErrored = true;																																					\
	}

		LSN_VURIFFY( ui8A );
		LSN_VURIFFY( ui8X );
		LSN_VURIFFY( ui8Y );
		LSN_VURIFFY( ui8Sp );

		LSN_VURIFFY( ui8Status );
		LSN_VURIFFY( ui16Pc );
#undef LSN_VURIFFY

		// Ensure no pending updates to PC or S.
		if ( m_fsState.ui8SModify ) {
			lsn::DebugA( cvoVerifyMe.sName.c_str() );
			lsn::DebugA( "\r\nSP is pending an update.\r\n" );
			lsn::DebugA( "\r\n\r\n" ); bErrored = true;
		}
		if ( m_fsState.ui16PcModify ) {
			lsn::DebugA( cvoVerifyMe.sName.c_str() );
			lsn::DebugA( "\r\nPC is pending an update.\r\n" );
			lsn::DebugA( "\r\n\r\n" ); bErrored = true;
		}

		if ( m_bbBusB.ReadWriteLog().size() > cvoVerifyMe.vCycles.size() ) {
			lsn::DebugA( cvoVerifyMe.sName.c_str() );
			lsn::DebugA( "\r\nInternal Error\r\n" );
			lsn::DebugA( "\r\n\r\n" ); bErrored = true;
		}
		else {
			size_t J = 0;
			for ( size_t I = 0; I < m_bbBusB.ReadWriteLog().size(); ++I ) {
				if ( cvoVerifyMe.vCycles[I].bNoReadOrWrite == false ) {
					if ( m_bbBusB.ReadWriteLog()[J].ui16Address != cvoVerifyMe.vCycles[I].ui32Addr ) {
						lsn::DebugA( cvoVerifyMe.sName.c_str() );
						lsn::DebugA( "\r\nCPU Failure: Cycle Address Wrong\r\n" );
						lsn::DebugA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.vCycles[I].ui32Addr ) + std::string( " Got: " ) + std::to_string( m_bbBusB.ReadWriteLog()[J].ui16Address ) ).c_str() );
						lsn::DebugA( "\r\n\r\n" ); bErrored = true;
					}
					if ( m_bbBusB.ReadWriteLog()[J].ui8Value != cvoVerifyMe.vCycles[I].ui8Value ) {
						lsn::DebugA( cvoVerifyMe.sName.c_str() );
						lsn::DebugA( "\r\nCPU Failure: Cycle Value Wrong\r\n" );
						lsn::DebugA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.vCycles[I].ui8Value ) + std::string( " Got: " ) + std::to_string( m_bbBusB.ReadWriteLog()[J].ui8Value ) ).c_str() );
						lsn::DebugA( "\r\n\r\n" ); bErrored = true;
					}
					/*if ( m_bbBusB.ReadWriteLog()[J].bRead != (cvoVerifyMe.vCycles[I].sStatus[3] == 'r') ) {
						lsn::DebugA( cvoVerifyMe.sName.c_str() );
						lsn::DebugA( "\r\nCPU Failure: Cycle Read/Write Wrong\r\n" );
						lsn::DebugA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.vCycles[I].sStatus[3] ) + std::string( " Got: " ) + std::to_string( m_bbBusB.ReadWriteLog()[J].bRead ) ).c_str() );
						lsn::DebugA( "\r\n\r\n" ); bErrored = true;
					}*/
				}
				++J;
			}
		}
		if ( bErrored ) {
			lsn::DebugA( (std::format( "Mega Fail.\r\n\r\n" )).c_str() );
		}
		return i32Cnt;
	}
#endif	// #ifdef LSN_SPC700_CPU_VERIFY


#ifdef LSN_SPC700_CPU_VERIFY
	/**
	 * Given a JSON object and the value for the test to run, this loads the test and fills a LSN_SPC700_CPU_VERIFY structure.
	 *
	 * \param _jJson The JSON file.
	 * \param _jvTest The test to run.
	 * \param _cvoTest The test structure to fill out.
	 * \return Returns true if the JSON data was successfully extracted and the test created.
	 */
	bool CSpc700::GetTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest, LSN_CPU_VERIFY_OBJ &_cvoTest ) {
		const lson::CJsonContainer::LSON_JSON_VALUE * pjvVal;
		// The name.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "name" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_STRING ) {
			_cvoTest.sName = _jJson.GetContainer()->GetString( pjvVal->u.stString );
		}
		else { return false; }

		// The initial state.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "initial" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_OBJECT ) {
			if ( !LoadState( _jJson, (*pjvVal), _cvoTest.cvsStart ) ) { return false; }
		}
		else { return false; }

		// The final state.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "final" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_OBJECT ) {
			if ( !LoadState( _jJson, (*pjvVal), _cvoTest.cvsEnd ) ) { return false; }
		}
		else { return false; }

		// The cycles.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "cycles" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_ARRAY ) {
			for ( size_t I = 0; I < pjvVal->vArray.size(); ++I ) {
				const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = _jJson.GetContainer()->GetValue( pjvVal->vArray[I] );
				if ( jvThis.vtType == lson::CJsonContainer::LSON_VT_ARRAY && jvThis.vArray.size() == 3 ) {
					auto aReadWrite = _jJson.GetContainer()->GetValue( jvThis.vArray[1] );
					LSN_CPU_VERIFY_CYCLE cvcCycle = {
						.ui32Addr = uint32_t( _jJson.GetContainer()->GetValue( jvThis.vArray[0] ).u.dDecimal ),
						.ui8Value = uint8_t( aReadWrite.u.dDecimal ),
						.sStatus = _jJson.GetContainer()->GetString( _jJson.GetContainer()->GetValue( jvThis.vArray[2] ).u.stString ),
						.bNoReadOrWrite = aReadWrite.vtType == lson::CJsonContainer::LSON_VT_NULL,
					};
					_cvoTest.vCycles.push_back( cvcCycle );
				}
				else { return false; }
			}
		}
		else { return false; }
		return true;
	}

	/**
	 * Fills out a LSN_CPU_VERIFY_STATE structure given a JSON "initial" or "final" member.
	 *
	 * \param _jJson The JSON file.
	 * \param _jvState The bject member representing the state to load.
	 * \param _cvsState The state structure to fill.
	 * \return Returns true if the state was loaded.
	 */
	bool CSpc700::LoadState( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvState, LSN_CPU_VERIFY_STATE &_cvsState ) {
		const lson::CJsonContainer::LSON_JSON_VALUE * pjvVal;

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "pc" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16Pc = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "sp" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8Sp = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "a" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8A = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "x" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8X = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "y" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8Y = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "psw" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8Status = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }


		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "ram" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_ARRAY ) {
			for ( size_t I = 0; I < pjvVal->vArray.size(); ++I ) {
				const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = _jJson.GetContainer()->GetValue( pjvVal->vArray[I] );
				if ( jvThis.vtType == lson::CJsonContainer::LSON_VT_ARRAY && jvThis.vArray.size() == 2 ) {
					LSN_CPU_VERIFY_RAM cvrRam = {
						.ui32Addr = uint32_t( _jJson.GetContainer()->GetValue( jvThis.vArray[0] ).u.dDecimal ),
						.ui8Value = uint8_t( _jJson.GetContainer()->GetValue( jvThis.vArray[1] ).u.dDecimal ),
					};
					_cvsState.vRam.push_back( cvrRam );
				}
				else { return false; }
			}
		}
		else { return false; }

		return true;
	}
#endif	// #ifdef LSN_SPC700_CPU_VERIFY

}	// namespace lsn
