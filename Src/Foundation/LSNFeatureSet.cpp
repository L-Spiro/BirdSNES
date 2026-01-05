/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Detects the processor feature set.
 */

#include "LSNFeatureSet.h"

namespace lsn {

	// == Members.
#ifdef LSN_CPUID
	const CFeatureSet::InstructionSet_Internal CFeatureSet::m_iiCpuRep;
#endif	// #ifdef LSN_CPUID

}	// namespace lsn
