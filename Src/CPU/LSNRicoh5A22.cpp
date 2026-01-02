/**
 * Copyright L. Spiro 2026
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A Ricoh 5A22 processor.
 */

#include "LSNRicoh5A22.h"


namespace lsn {

	Ricoh5A22::Ricoh5A22( BusA &_bBusA ) :
		m_baBusA( _bBusA ) {
	}
	Ricoh5A22::~Ricoh5A22() {
	}

	// == Functions.
	/**
	 * Resets the bus to a known state.
	 */
	void Ricoh5A22::ResetToKnown() {
		ResetAnalog();
		std::memset( &m_fsState.rRegs, 0, sizeof( m_fsState.rRegs ) );
		uint8_t ui8Speed;
		m_fsState.rRegs.ui16Pc = m_baBusA.Read( 0xFFFC, 0x00, ui8Speed ) | (m_baBusA.Read( 0xFFFD, 0x00, ui8Speed ) << 8);
		m_fsState.rRegs.ui16S = 0;
		m_fsState.bEmulationMode = true;

		m_ui64CycleCount = 0ULL;
	}

	/**
	 * Performs an "analog" reset, allowing previous data to remain.
	 */
	void Ricoh5A22::ResetAnalog() {
		//m_pfTickFunc = m_pfTickFuncCopy = &Ricoh5A22::Tick_NextInstructionStd;
		m_fsState.bBoundaryCrossed = false;
		m_fsState.ui16PcModify = 0;
		m_fsState.ui16SModify = 0;
		m_fsState.bAllowWritingToPc = true;
	}

}	// namespace lsn
