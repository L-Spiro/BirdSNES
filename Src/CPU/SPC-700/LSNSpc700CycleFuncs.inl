#define LSN_DIRECT_PAGE_BIT( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND, false>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND, true>, &CSpc700::BeginInst }, 4, LSN_AM_DIRECT_PAGE_BIT, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page Bit (Read/Modify/Write)", #NAME1, "Direct Page Bit (Read/Modify/Write)"

#ifndef LSN_R
#define LSN_R																				LSN_CT_READ
#endif	// #ifndef LSN_R
#ifndef LSN_W
#define LSN_W																				LSN_CT_WRITE
#endif	// #ifndef LSN_W
#ifndef LSN_N
#define LSN_N																				LSN_CT_NULL
#endif	// #ifndef LSN_N

CSpc700::LSN_INSTR CSpc700::m_iInstructionSet[256] = {										/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2<INT8_MIN, true>,
			&CSpc700::BeginInst
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_NOP, "NOP", "Implied", "NOP", "Implied"
	},
	{	// 01
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Null<LSN_N>,															&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_H, 0>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_L, -1>,
			&CSpc700::Null<LSN_N, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_Phi2<0xFFDE, CSpc700::LSN_RT_PC_L, false>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_Phi2<0xFFDE+1, CSpc700::LSN_RT_PC_H, true>,
			&CSpc700::BeginInst
		},
		8, LSN_AM_IMPLIED, 1, LSN_I_TCALL, "TCALL", "Implied", "JST0", "Implied"
	},
	{	// 02
#define LSN_TMP_INST Set1<0, 1>
		LSN_DIRECT_PAGE_BIT( SET1, SET1, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 03
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Operand_To_DirectPage<LSN_TO_A, true>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND, false>,
			&CSpc700::Null<LSN_N>,															&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_R>,															&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Null<LSN_N>,															&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_N>,															&CSpc700::Null_Phi2<INT8_MIN, true>,
			&CSpc700::BeginInst
		},
		5, LSN_AM_DIRECT_PAGE_BIT_RELATIVE, 3, LSN_I_BBS, "BBS", "Direct Page Bit Relative", "BBS", "Direct Page Bit Relative"
	},
};

#undef LSN_R
#undef LSN_W
#undef LSN_N

#undef LSN_DIRECT_PAGE_BIT