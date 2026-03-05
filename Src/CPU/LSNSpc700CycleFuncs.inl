CSpc700::LSN_INSTR CSpc700::m_iInstructionSet[256] = {										/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			/* BeginInst() */																&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2<INT8_MIN, true>,
			&CSpc700::BeginInst<true>
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_NOP, "NOP", "Implied", "NOP", "Implied"
	},
};