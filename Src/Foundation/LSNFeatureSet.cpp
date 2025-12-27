/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Detects the processor feature set.
 */

#include "NN9FeatureSet.h"

namespace nn9 {

	// == Members.
#ifdef NN9_CPUID
	const FeatureSet::InstructionSet_Internal FeatureSet::m_iiCpuRep;
#endif	// #ifdef NN9_CPUID

}	// namespace nn9
