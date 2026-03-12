#define LSN_DIRECT_PAGE_BIT_RMW( NAME0, NAME1, BIT, VALUE )									{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::Set1<BIT, VALUE>, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 4, LSN_AM_DIRECT_PAGE_BIT, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page Bit (Read/Modify/Write)", #NAME1

#define LSN_IMPLIED_BCC( IDX )																{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_W>, &CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_H, 0>, &CSpc700::Null<LSN_W>, &CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_L, -1>, &CSpc700::Null<LSN_N, false, true>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_R>, &CSpc700::Read_Phi2<0xFFDE-(2*IDX), CSpc700::LSN_RT_PC_L>, &CSpc700::Null<LSN_R>, &CSpc700::Read_Phi2<0xFFDE-(2*IDX)+1, CSpc700::LSN_RT_PC_H>, &CSpc700::BeginInst }, 8, LSN_AM_IMPLIED, 1, LSN_I_TCALL, "TCALL" #IDX, "Implied", "JST" #IDX

#define LSN_PAGE_BIT_RELATIVE( NAME, BIT, VALUE )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::Bbc<BIT, VALUE>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_R>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::EndIfNotJmp_BeginInst, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_L, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_H_BeginInst }, 5, LSN_AM_DIRECT_PAGE_BIT_RELATIVE, 3, LSN_I_ ## NAME, #NAME #BIT, "Direct Page Bit Relative", #NAME #BIT
#define LSN_RELATIVE( NAME, FLAG, VALUE )													{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Branch<FLAG, VALUE>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::EndIfNotJmp_BeginInst<4>, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_L, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_H_BeginInst }, 2, LSN_AM_RELATIVE, 2, LSN_I_ ## NAME, #NAME, "Implied", #NAME

#define LSN_DIRECT_PAGE_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 3, LSN_AM_DIRECT_PAGE, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page (Read)", #NAME1
#define LSN_DIRECT_PAGE_RMW( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 4, LSN_AM_DIRECT_PAGE, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page (Read/Modify/Write)", #NAME1

#define LSN_ABSOLUTE_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 4, LSN_AM_ABSOLUTE, 3, LSN_I_ ## NAME0, #NAME0, "Absolute (Read)", #NAME1
#define LSN_ABSOLUTE_RMW( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 5, LSN_AM_ABSOLUTE, 3, LSN_I_ ## NAME0, #NAME0, "Absolute (Read/Modify/Write)", #NAME1
#define LSN_ABSOLUTE_RMW_BIT( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_DUMMY>, &CSpc700::Null<LSN_R>, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 6, LSN_AM_ABSOLUTE, 3, LSN_I_ ## NAME0, #NAME0, "Absolute (Read/Modify/Write)", #NAME1

#define LSN_INDIRECT_X_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_N>, &CSpc700::Read_X_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 3, LSN_AM_INDIRECT_X, 1, LSN_I_ ## NAME0, #NAME0, "Indirect X (Read)", #NAME1

#define LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( NAME0, NAME1, FUNC )							{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::X_Or_Y_Plus_Operand_To_AddrOrPtr_Masked_ApplyP<CSpc700::LSN_RT_X, LSN_TO_A, 0xFF>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_L>, &CSpc700::Null<LSN_R>, &CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_H, 0xFF>, &CSpc700::Null<LSN_R>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_P, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, LSN_I_ ## NAME0, #NAME0, "X-Indexed Indirect (Read)", #NAME1

#define LSN_IMMEDIATE_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 2, LSN_AM_IMMEDIATE, 2, LSN_I_ ## NAME0, #NAME0, "Immediate", #NAME1

#define LSN_DIRECT_PAGE_DIRECT_PAGE_RMW( NAME0, NAME1, FUNC )								{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND0>, &CSpc700::Null<LSN_N, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND1>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND0>, &CSpc700::BeginInst }, 6, LSN_AM_DIRECT_PAGE_DIRECT_PAGE, 3, LSN_I_ ## NAME0, #NAME0, "Direct Page to Direct Page (Read/Modify/Write)", #NAME1

#define LSN_ABSOLUTE_BIT( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND, 0x1FFF>, &CSpc700::Or1<false>, &CSpc700::Null_Phi2, &CSpc700::FUNC }, 5, LSN_AM_ABSOLUTE_BIT, 3, LSN_I_ ## NAME0, #NAME0, "Absolute Boolean Bit", #NAME1

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
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::BeginInst
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_NOP, "NOP", "Implied", "NOP"
	},
	{	// 01
		LSN_IMPLIED_BCC( 0 )
	},
	{	// 02
		LSN_DIRECT_PAGE_BIT_RMW( SET1, SET1, 0, 1 )
	},
	{	// 03
		LSN_PAGE_BIT_RELATIVE( BBS, 0, 1 )
	},
	{	// 04
		LSN_DIRECT_PAGE_R( OR, ORA, Or_BeginInst<false> )
	},
	{	// 05
		LSN_ABSOLUTE_R( OR, ORA, Or_BeginInst<false> )
	},
	{	// 06
		LSN_INDIRECT_X_R( OR, ORA, Or_BeginInst<false> )
	},
	{	// 07
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( OR, ORA, Or_BeginInst<false> )

		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Null<LSN_N, true>,													&CSpc700::Null_Phi2,
		//	&CSpc700::X_Or_Y_Plus_Operand_To_AddrOrPtr_Masked_ApplyP<CSpc700::LSN_RT_X, LSN_TO_A, 0xFF>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_L>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_H, 0xFF>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_P, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Or_BeginInst<false>
		//},
		//6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, LSN_I_ ## NAME0, #NAME0, "X-Indexed Indirect (Read)", #NAME1
	},


	/** 08-0F */
	{	// 08
		LSN_IMMEDIATE_R( OR, ORA, Or_BeginInst<true> )
	},
	{	// 09
#define LSN_TMP_INST	Or_BeginInst<false, true>
		LSN_DIRECT_PAGE_DIRECT_PAGE_RMW( OR, ORA, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 0A
		LSN_ABSOLUTE_BIT( OR1, OR1, BeginInst<false> )
	},
	{	// 0B
		LSN_DIRECT_PAGE_RMW( ASL, ASL, Asl )
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Operand_To_DirectPage<LSN_TO_A, true>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Asl,																	&CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::BeginInst
		//},
		//4, LSN_AM_DIRECT_PAGE, 2, LSN_I_ASL, "ASL", "Direct Page (Read/Modify/Write)", "ASL"
	},
	{	// 0C
		LSN_ABSOLUTE_RMW( ASL, ASL, Asl )
	},
	{	// 0D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_STATUS, 0>,
			&CSpc700::Null<LSN_N, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::BeginInst
		},
		4, LSN_AM_IMPLIED, 1, LSN_I_PUSH, "PUSH", "Implied", "PHP"
	},
	{	// 0E
		LSN_ABSOLUTE_RMW_BIT( TSET1, SET1, TSet1 )
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::TSet1,																&CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::BeginInst
		//},
		//6, LSN_AM_ABSOLUTE, 3, LSN_I_TSET1, "TSET1", "Absolute (Read/Modify/Write)", "SET1"
	},
	{	// 0F
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_H, 0>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_L, -1>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_STATUS, -2>,
			&CSpc700::Brk,																	&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_Phi2<0xFFDE, CSpc700::LSN_RT_PC_L>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_Phi2<0xFFDF, CSpc700::LSN_RT_PC_H>,
			&CSpc700::BeginInst
		},
		8, LSN_AM_IMPLIED, 1, LSN_I_BRK, "BRK", "Implied", "BRK"
	},


	/** 10-17 */
	{	// 10
		LSN_RELATIVE( BPL, N(), 0 )
	},
	{	// 11
		LSN_IMPLIED_BCC( 1 )
	},
	{	// 12
		LSN_DIRECT_PAGE_BIT_RMW( CLR1, CLR1, 0, 0 )
	},
	{	// 13
		LSN_PAGE_BIT_RELATIVE( BBC, 0, 0 )
	},
	{	// 14
		//LSN_DIRECT_PAGE_INDEXED_X_R( OR, ORA, Or_BeginInst<false> )
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Null<LSN_N, true>,													&CSpc700::Null_Phi2,
			&CSpc700::X_Or_Y_Plus_Operand_To_AddrOrPtr_Masked_ApplyP<CSpc700::LSN_RT_X, LSN_TO_A, 0xFF, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Or_BeginInst<false>
		},
		4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, LSN_I_OR, "OR", "X-Indexed Direct Page (Read)", "ORA"
	},
};

#undef LSN_R
#undef LSN_W
#undef LSN_N
#undef LSN_ABSOLUTE_BIT
#undef LSN_DIRECT_PAGE_DIRECT_PAGE_RMW
#undef LSN_IMMEDIATE_R
#undef LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R
#undef LSN_INDIRECT_X_R
#undef LSN_ABSOLUTE_RMW_BIT
#undef LSN_ABSOLUTE_RMW
#undef LSN_ABSOLUTE_R
#undef LSN_DIRECT_PAGE_RMW
#undef LSN_DIRECT_PAGE_R
#undef LSN_RELATIVE
#undef LSN_PAGE_BIT_RELATIVE
#undef LSN_IMPLIED_BCC
#undef LSN_DIRECT_PAGE_BIT
