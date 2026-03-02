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

}	// namespace lsn
