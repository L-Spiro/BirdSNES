#define LSN_DIRECT_PAGE_BIT_RMW( NAME0, NAME1, BIT, VALUE )									{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::Set1<BIT, VALUE>, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 4, LSN_AM_DIRECT_PAGE_BIT, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page Bit d.b (Read/Modify/Write)", #NAME1

#define LSN_IMPLIED_BCC( IDX )																{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_W>, &CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_H, 0>, &CSpc700::Null<LSN_W>, &CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_L, -1>, &CSpc700::Null<LSN_N, false, true>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_R>, &CSpc700::Read_Phi2<0xFFDE-(2*IDX), CSpc700::LSN_RT_PC_L>, &CSpc700::Null<LSN_R>, &CSpc700::Read_Phi2<0xFFDE-(2*IDX)+1, CSpc700::LSN_RT_PC_H>, &CSpc700::BeginInst }, 8, LSN_AM_IMPLIED, 1, LSN_I_TCALL, "TCALL" #IDX, "Implied", "JST" #IDX

#define LSN_PAGE_BIT_RELATIVE( NAME, BIT, VALUE )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::Bbc<BIT, VALUE>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_R>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::EndIfNotJmp_BeginInst, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_L, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_H_BeginInst }, 5, LSN_AM_DIRECT_PAGE_BIT_RELATIVE, 3, LSN_I_ ## NAME, #NAME #BIT, "Direct Page Bit Relative d.b, r", #NAME #BIT
#define LSN_RELATIVE( NAME, FLAG, VALUE )													{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Branch<FLAG, VALUE>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::EndIfNotJmp_BeginInst<4>, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_L, &CSpc700::Null_Phi2, &CSpc700::Branch_UpdatePc_H_BeginInst }, 2, LSN_AM_RELATIVE, 2, LSN_I_ ## NAME, #NAME, "Relative r", #NAME

#define LSN_DIRECT_PAGE_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 3, LSN_AM_DIRECT_PAGE, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page d (Read)", #NAME1
#define LSN_DIRECT_PAGE_RMW( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 4, LSN_AM_DIRECT_PAGE, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page d (Read/Modify/Write)", #NAME1
#define LSN_DIRECT_PAGE_RMW_16( NAME0, NAME1, FUNC0, FUNC1 )								{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC0, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_R>, &CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND, 0xFF>, &CSpc700::FUNC1, &CSpc700::Write_PtrOrAddr_H_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND, 0xFF>, &CSpc700::BeginInst }, 6, LSN_AM_DIRECT_PAGE, 2, LSN_I_ ## NAME0, #NAME0, "Direct Page d (Read/Modify/Write 16)", #NAME1

#define LSN_DIRECT_PAGE_IMMEDIATE_RMW( NAME0, NAME1, FUNC )									{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND0>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND1>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND0>, &CSpc700::BeginInst }, 5, LSN_AM_DIRECT_PAGE_IMMEDIATE, 3, LSN_I_ ## NAME0, #NAME0, "Immediate Data to Direct Page d, #i (Read/Modify/Write)", #NAME1

#define LSN_ABSOLUTE_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 4, LSN_AM_ABSOLUTE, 3, LSN_I_ ## NAME0, #NAME0, "Absolute !a (Read)", #NAME1
#define LSN_ABSOLUTE_RMW( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 5, LSN_AM_ABSOLUTE, 3, LSN_I_ ## NAME0, #NAME0, "Absolute !a (Read/Modify/Write)", #NAME1
#define LSN_ABSOLUTE_RMW_BIT( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_DUMMY>, &CSpc700::Null<LSN_R>, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 6, LSN_AM_ABSOLUTE, 3, LSN_I_ ## NAME0, #NAME0, "Absolute !a (Read/Modify/Write)", #NAME1

#define LSN_ABSOLUTE_X_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::XorY_Plus_PtrOrAddr_To_AddrOrPtr<CSpc700::LSN_RT_X, LSN_FROM_A>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_P, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 5, LSN_AM_ABSOLUTE_X, 3, LSN_I_ ## NAME0, #NAME0, "X-Indexed Absolute !a+X (Read)", #NAME1

#define LSN_ABSOLUTE_Y_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::XorY_Plus_PtrOrAddr_To_AddrOrPtr<CSpc700::LSN_RT_Y, LSN_FROM_A>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_P, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 5, LSN_AM_ABSOLUTE_Y, 3, LSN_I_ ## NAME0, #NAME0, "Y-Indexed Absolute !a+Y (Read)", #NAME1

#define LSN_INDIRECT_X_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Null_Phi2, &CSpc700::Null<LSN_N>, &CSpc700::Read_X_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 3, LSN_AM_INDIRECT_X, 1, LSN_I_ ## NAME0, #NAME0, "Indirect X (X) (Read)", #NAME1

#define LSN_INDIRECT_X_INDIRECT_Y_RMW( NAME0, NAME1, FUNC )									{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>, &CSpc700::Null<LSN_R, false>, &CSpc700::Read_Y_Phi2<CSpc700::LSN_RT_OPERAND0>, &CSpc700::Null<LSN_R>, &CSpc700::Read_X_Phi2<CSpc700::LSN_RT_OPERAND1>, &CSpc700::FUNC, &CSpc700::Write_X_Phi2<CSpc700::LSN_RT_OPERAND0>, &CSpc700::BeginInst }, 5, LSN_AM_INDIRECT_X_INDIRECT_Y, 1, LSN_I_ ## NAME0, #NAME0, "Indirect Page to Indirect Page (X), (Y) (Read/Modify/Write)", #NAME1

#define LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( NAME0, NAME1, FUNC )							{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::XorY_Plus_Operand_To_AddrOrPtr_Masked<CSpc700::LSN_RT_X, LSN_TO_A, 0xFF>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_L>, &CSpc700::Null<LSN_R>, &CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_H, 0xFF>, &CSpc700::Null<LSN_R>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_P, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, LSN_I_ ## NAME0, #NAME0, "X-Indexed Indirect [d+X] (Read)", #NAME1

#define LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( NAME0, NAME1, FUNC )							{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::Operand_To_DirectPage<LSN_TO_A, false>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_L>, &CSpc700::Null<LSN_R>, &CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_H, 0xFF>, &CSpc700::XorY_Plus_PtrOrAddr_To_AddrOrPtr<CSpc700::LSN_RT_Y, LSN_FROM_P>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 6, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, LSN_I_ ## NAME0, #NAME0, "Indirect Y-Indexed [d]+Y (Read)", #NAME1

#define LSN_IMMEDIATE_R( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 2, LSN_AM_IMMEDIATE, 2, LSN_I_ ## NAME0, #NAME0, "Immediate", #NAME1

#define LSN_ACCUMULATOR( NAME0, NAME1, FUNC )												{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,&CSpc700::FUNC }, 2, LSN_AM_ACCUMULATOR, 1, LSN_I_ ## NAME0, #NAME0, "Accumulator A", #NAME1

#define LSN_DIRECT_PAGE_DIRECT_PAGE_RMW( NAME0, NAME1, FUNC )								{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND0>, &CSpc700::Null<LSN_N, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Operand_To_DirectPage<LSN_TO_A, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND1>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND0>, &CSpc700::BeginInst }, 6, LSN_AM_DIRECT_PAGE_DIRECT_PAGE, 3, LSN_I_ ## NAME0, #NAME0, "Direct Page to Direct Page dd, ds (Read/Modify/Write)", #NAME1

#define LSN_DIRECT_PAGE_INDEXED_X_R( NAME0, NAME1, FUNC )									{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::XorY_Plus_Operand_To_AddrOrPtr_Masked<CSpc700::LSN_RT_X, LSN_TO_A, 0xFF>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC }, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, LSN_I_ ## NAME0, #NAME0, "X-Indexed Direct Page d+X (Read)", #NAME1
#define LSN_DIRECT_PAGE_INDEXED_X_R_RMW( NAME0, NAME1, FUNC )								{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>, &CSpc700::Null<LSN_N, true>, &CSpc700::Null_Phi2, &CSpc700::XorY_Plus_Operand_To_AddrOrPtr_Masked<CSpc700::LSN_RT_X, LSN_TO_A, 0xFF>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::FUNC, &CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>, &CSpc700::BeginInst }, 5, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, LSN_I_ ## NAME0, #NAME0, "X-Indexed Direct Page d+X (Read/Modify/Write)", #NAME1

#define LSN_ABSOLUTE_BIT_5( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND, 0x1FFF>, &CSpc700::Null<LSN_N>, &CSpc700::Null_Phi2, &CSpc700::AbsBitModify<FUNC, true> }, 5, LSN_AM_ABSOLUTE_BIT, 3, LSN_I_ ## NAME0, #NAME0, "Absolute Boolean Bit m.b", #NAME1
#define LSN_ABSOLUTE_BIT_4( NAME0, NAME1, FUNC )											{ /* BeginInst() */ &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>, &CSpc700::Null<LSN_R, true>, &CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>, &CSpc700::Null<LSN_R, true>, &CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND, 0x1FFF>, &CSpc700::AbsBitModify<FUNC, true>, }, 4, LSN_AM_ABSOLUTE_BIT, 3, LSN_I_ ## NAME0, #NAME0, "Absolute Boolean Bit m.b", #NAME1

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
		LSN_ABSOLUTE_BIT_5( OR1, ORC, LSN_BM_OR )
	},
	{	// 0B
		LSN_DIRECT_PAGE_RMW( ASL, ASL, Asl )
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
		LSN_DIRECT_PAGE_INDEXED_X_R( OR, ORA, Or_BeginInst<false> )
	},
	{	// 15
		LSN_ABSOLUTE_X_R( OR, ORA, Or_BeginInst<false> )
	},
	{	// 16
		LSN_ABSOLUTE_Y_R( OR, ORA, Or_BeginInst<false> )
	},
	{	// 17
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( OR, ORA, Or_BeginInst<false> )
	},


	/** 18-1F */
	{	// 18
#define LSN_TMP_INST	Or_BeginInst<false, true>
		LSN_DIRECT_PAGE_IMMEDIATE_RMW( OR, ORA, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 19
#define LSN_TMP_INST	Or_BeginInst<false, true>
		LSN_INDIRECT_X_INDIRECT_Y_RMW( OR, ORA, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 1A
		LSN_DIRECT_PAGE_RMW_16( DECW, DEW, DecW_L, DecW_H )
	},
	{	// 1B
		LSN_DIRECT_PAGE_INDEXED_X_R_RMW( ASL, ASL, Asl )
	},
	{	// 1C
		LSN_ACCUMULATOR( ASL, ASL, Asl<true> )
	},
	{	// 1D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::Dec_BeginInst
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_DEC, "DEC", "Implied", "DEX"
	},
	{	// 1E
		LSN_ABSOLUTE_R( CMP, CPX, Cmp_BeginInst )
	},
	{	// 1F
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>,
			&CSpc700::Null<LSN_N>,															&CSpc700::Null_Phi2,
			&CSpc700::XorY_Plus_PtrOrAddr_To_AddrOrPtr<CSpc700::LSN_RT_X, LSN_FROM_A>,		&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_P, CSpc700::LSN_RT_PC_L>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_P, CSpc700::LSN_RT_PC_H>,
			&CSpc700::BeginInst
		},
		6, LSN_AM_ABSOLUTE_INDEXED_INDIRECT_X, 3, LSN_I_JMP, "JMP", "Absolute X-Indexed Indirect [!a+X]", "JMP"
	},


	/** 20-27 */
	{	// 20
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::SetBit_BeginInst<P(), 0>
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_CLRP, "CLRP", "Implied", "CLP"
	},
	{	// 21
		LSN_IMPLIED_BCC( 2 )
	},
	{	// 22
		LSN_DIRECT_PAGE_BIT_RMW( SET1, SET1, 1, 1 )
	},
	{	// 23
		LSN_PAGE_BIT_RELATIVE( BBS, 1, 1 )
	},
	{	// 24
		LSN_DIRECT_PAGE_R( AND, AND, And_BeginInst<false> )
	},
	{	// 25
		LSN_ABSOLUTE_R( AND, AND, And_BeginInst<false> )
	},
	{	// 26
		LSN_INDIRECT_X_R( AND, AND, And_BeginInst<false> )
	},
	{	// 27
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( AND, AND, And_BeginInst<false> )
	},


	/** 28-2F */
	{	// 28
		LSN_IMMEDIATE_R( AND, AND, And_BeginInst<true> )
	},
	{	// 29
#define LSN_TMP_INST	And_BeginInst<false, true>
		LSN_DIRECT_PAGE_DIRECT_PAGE_RMW( AND, AND, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 2A
		LSN_ABSOLUTE_BIT_5( OR1, ORC, LSN_BM_NOR )
	},
	{	// 2B
		LSN_DIRECT_PAGE_RMW( ROL, ROL, Rol )
	},
	{	// 2C
		LSN_ABSOLUTE_RMW( ROL, ROL, Rol )
	},
	{	// 2D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_A, 0>,
			&CSpc700::Null<LSN_N, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::BeginInst
		},
		4, LSN_AM_IMPLIED, 1, LSN_I_PUSH, "PUSH", "Implied", "PHA"
	},
	{	// 2E
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Operand_To_DirectPage<LSN_TO_A, true>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Cbne,																	&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_R>,															&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::EndIfNotJmp_BeginInst,												&CSpc700::Null_Phi2,
			&CSpc700::Branch_UpdatePc_L,													&CSpc700::Null_Phi2,
			&CSpc700::Branch_UpdatePc_H_BeginInst
		},
		5, LSN_AM_DIRECT_PAGE_RELATIVE, 3, LSN_I_CBNE, "CBNE", "Direct Page Relative d, r", "CBNE"
	},
	{	// 2F
		LSN_RELATIVE( BRA, 0, 0 )
	},


	/** 30-37 */
	{	// 30
		LSN_RELATIVE( BMI, N(), 1 )
	},
	{	// 31
		LSN_IMPLIED_BCC( 3 )
	},
	{	// 32
		LSN_DIRECT_PAGE_BIT_RMW( CLR1, CLR1, 1, 0 )
	},
	{	// 33
		LSN_PAGE_BIT_RELATIVE( BBC, 1, 0 )
	},
	{	// 34
		LSN_DIRECT_PAGE_INDEXED_X_R( AND, AND, And_BeginInst<false> )
	},
	{	// 35
		LSN_ABSOLUTE_X_R( AND, AND, And_BeginInst<false> )
	},
	{	// 36
		LSN_ABSOLUTE_Y_R( AND, AND, And_BeginInst<false> )
	},
	{	// 37
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( AND, AND, And_BeginInst<false> )
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Null<LSN_N, true>,													&CSpc700::Null_Phi2,
		//	&CSpc700::Operand_To_DirectPage<LSN_TO_A, false>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_L>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_H, 0xFF>,
		//	&CSpc700::XorY_Plus_PtrOrAddr_To_AddrOrPtr<CSpc700::LSN_RT_Y, LSN_FROM_P>,		&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Or_BeginInst<false>
		//},
		//6, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, LSN_I_ ## NAME0, #NAME0, "Indirect Y-Indexed [d]+Y (Read)", #NAME1
	},


	/** 38-3F */
	{	// 38
#define LSN_TMP_INST	And_BeginInst<false, true>
		LSN_DIRECT_PAGE_IMMEDIATE_RMW( AND, AND, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 39
#define LSN_TMP_INST	And_BeginInst<false, true>
		LSN_INDIRECT_X_INDIRECT_Y_RMW( AND, AND, LSN_TMP_INST )
#undef LSN_TMP_INST
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
		//	&CSpc700::Null<LSN_R, false>,													&CSpc700::Read_Y_Phi2<CSpc700::LSN_RT_OPERAND0>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_X_Phi2<CSpc700::LSN_RT_OPERAND1>,
		//	&CSpc700::Or_BeginInst<false, true>,											&CSpc700::Write_X_Phi2<CSpc700::LSN_RT_OPERAND0>,
		//	&CSpc700::BeginInst
		//},
		//5, LSN_AM_INDIRECT_X_INDIRECT_Y, 1, LSN_I_ ## NAME0, #NAME0, "Indirect Page to Indirect Page (X), (Y) (Read/Modify/Write)", #NAME1
	},
	{	// 3A
		LSN_DIRECT_PAGE_RMW_16( INCW, INW, IncW_L, IncW_H )
	},
	{	// 3B
		LSN_DIRECT_PAGE_INDEXED_X_R_RMW( ROL, ROL, Rol )
	},
	{	// 3C
		LSN_ACCUMULATOR( ROL, ROL, Rol<true> )
	},
	{	// 3D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::Inc_BeginInst
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_INC, "INC", "Implied", "INX"
	},
	{	// 3E
		LSN_DIRECT_PAGE_R( CMP, CPX, Cmp_BeginInst<CSpc700::LSN_RT_X> )
	},
	{	// 3F
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>,
			&CSpc700::Null<LSN_N, true>,													&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_H, 0>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_L, -1>,
			&CSpc700::Null<LSN_R, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::Copy_AddrOrPtr_To_Pc_L<LSN_FROM_A>,									&CSpc700::Null_Phi2,
			&CSpc700::Copy_AddrOrPtr_To_Pc_H_BeginInst<LSN_FROM_A>
		},
		8, LSN_AM_ABSOLUTE, 3, LSN_I_CALL, "CALL", "Absolute Call !a", "JSR"
	},


	/** 40-47 */
	{	// 40
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::SetBit_BeginInst<P(), 1>
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_SETP, "SETP", "Implied", "SEP"
	},
	{	// 41
		LSN_IMPLIED_BCC( 4 )
	},
	{	// 42
		LSN_DIRECT_PAGE_BIT_RMW( SET1, SET1, 2, 1 )
	},
	{	// 43
		LSN_PAGE_BIT_RELATIVE( BBS, 2, 1 )
	},
	{	// 44
		LSN_DIRECT_PAGE_R( EOR, EOR, Eor_BeginInst<false> )
	},
	{	// 45
		LSN_ABSOLUTE_R( EOR, EOR, Eor_BeginInst<false> )
	},
	{	// 46
		LSN_INDIRECT_X_R( EOR, EOR, Eor_BeginInst<false> )
	},
	{	// 47
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( EOR, EOR, Eor_BeginInst<false> )
	},


	/** 48-4F */
	{	// 48
		LSN_IMMEDIATE_R( EOR, EOR, Eor_BeginInst<true> )
	},
	{	// 49
#define LSN_TMP_INST	Eor_BeginInst<false, true>
		LSN_DIRECT_PAGE_DIRECT_PAGE_RMW( EOR, EOR, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 4A
		LSN_ABSOLUTE_BIT_4( AND1, ANDC, LSN_BM_AND )
	},
	{	// 4B
		LSN_DIRECT_PAGE_RMW( LSR, LSR, Lsr )
	},
	{	// 4C
		LSN_ABSOLUTE_RMW( LSR, LSR, Lsr )
	},
	{	// 4D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_X, 0>,
			&CSpc700::Null<LSN_N, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::BeginInst
		},
		4, LSN_AM_IMPLIED, 1, LSN_I_PUSH, "PUSH", "Implied", "PHX"
	},
	{	// 4E
		LSN_ABSOLUTE_RMW_BIT( TCLR1, CLR1, TClr1 )
	},
	{	// 4F
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>,
			&CSpc700::Null<LSN_N, true>,													&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_H, 0>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_PC_L, -1>,
			&CSpc700::Null<LSN_R, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::Copy_AddrOrPtr_To_Pc_L_FF_To_Pc_H_BeginInst<LSN_FROM_A>
		},
		6, LSN_AM_ABSOLUTE, 2, LSN_I_PCALL, "PCALL", "Absolute Call !a", "JSP"
	},


	/** 50-57 */
	{	// 50
		LSN_RELATIVE( BVC, V(), 0 )
	},
	{	// 51
		LSN_IMPLIED_BCC( 5 )
	},
	{	// 52
		LSN_DIRECT_PAGE_BIT_RMW( CLR1, CLR1, 2, 0 )
	},
	{	// 53
		LSN_PAGE_BIT_RELATIVE( BBC, 2, 0 )
	},
	{	// 54
		LSN_DIRECT_PAGE_INDEXED_X_R( EOR, EOR, Eor_BeginInst<false> )
	},
	{	// 55
		LSN_ABSOLUTE_X_R( EOR, EOR, Eor_BeginInst<false> )
	},
	{	// 56
		LSN_ABSOLUTE_Y_R( EOR, EOR, Eor_BeginInst<false> )
	},
	{	// 57
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( EOR, EOR, Eor_BeginInst<false> )
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Null<LSN_N, true>,													&CSpc700::Null_Phi2,
		//	&CSpc700::Operand_To_DirectPage<LSN_TO_A, false>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_L>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_PTR_H, 0xFF>,
		//	&CSpc700::XorY_Plus_PtrOrAddr_To_AddrOrPtr<CSpc700::LSN_RT_Y, LSN_FROM_P>,		&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
		//	&CSpc700::Or_BeginInst<false>
		//},
		//6, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, LSN_I_ ## NAME0, #NAME0, "Indirect Y-Indexed [d]+Y (Read)", #NAME1
	},


	/** 58-5F */
	{	// 58
#define LSN_TMP_INST	Eor_BeginInst<false, true>
		LSN_DIRECT_PAGE_IMMEDIATE_RMW( EOR, EOR, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 59
#define LSN_TMP_INST	Eor_BeginInst<false, true>
		LSN_INDIRECT_X_INDIRECT_Y_RMW( EOR, EOR, LSN_TMP_INST )
#undef LSN_TMP_INST
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
		//	&CSpc700::Null<LSN_R, false>,													&CSpc700::Read_Y_Phi2<CSpc700::LSN_RT_OPERAND0>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_X_Phi2<CSpc700::LSN_RT_OPERAND1>,
		//	&CSpc700::Or_BeginInst<false, true>,											&CSpc700::Write_X_Phi2<CSpc700::LSN_RT_OPERAND0>,
		//	&CSpc700::BeginInst
		//},
		//5, LSN_AM_INDIRECT_X_INDIRECT_Y, 1, LSN_I_ ## NAME0, #NAME0, "Indirect Page to Indirect Page (X), (Y) (Read/Modify/Write)", #NAME1
	},
	{	// 5A
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Operand_To_DirectPage<LSN_TO_A, true>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND16_L>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND16_H, 0xFF>,
			&CSpc700::CmpW_BeginInst
		},
		4, LSN_AM_DIRECT_PAGE, 2, LSN_I_CMPW, "CMPW", "Direct Page d (Read 16)", "CPW"
	},
	{	// 5B
		LSN_DIRECT_PAGE_INDEXED_X_R_RMW( LSR, LSR, Lsr )
	},
	{	// 5C
		LSN_ACCUMULATOR( LSR, LSR, Lsr<true> )
	},
	{	// 5D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::Transfer<CSpc700::LSN_RT_A, CSpc700::LSN_RT_X, false, true>
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_MOV, "MOV", "Implied", "TAX"
	},
	{	// 5E
		LSN_ABSOLUTE_R( CMP, CPY, Cmp_BeginInst<CSpc700::LSN_RT_Y> )
	},
	{	// 5F
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_L>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_ADDR_H>,
			&CSpc700::Transfer<CSpc700::LSN_RT_ADDR, CSpc700::LSN_RT_PC, false, true>
		},
		3, LSN_AM_ABSOLUTE, 3, LSN_I_JMP, "JMP", "Absolute !a", "JMP"
	},


	/** 60-67 */
	{	// 60
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Null_Phi2,
			&CSpc700::SetBit_BeginInst<C(), 0>
		},
		2, LSN_AM_IMPLIED, 1, LSN_I_CLRC, "CLRC", "Implied", "CLC"
	},
	{	// 61
		LSN_IMPLIED_BCC( 6 )
	},
	{	// 62
		LSN_DIRECT_PAGE_BIT_RMW( SET1, SET1, 3, 1 )
	},
	{	// 63
		LSN_PAGE_BIT_RELATIVE( BBS, 3, 1 )
	},
	{	// 64
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_DIRECT_PAGE_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 65
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_ABSOLUTE_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 66
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_INDIRECT_X_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 67
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},


	/** 68-6F */
	{	// 68
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, true>
		LSN_IMMEDIATE_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 69
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_DUMMY, false>
		LSN_DIRECT_PAGE_DIRECT_PAGE_RMW( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 6A
		LSN_ABSOLUTE_BIT_4( AND1, ANDC, LSN_BM_NAND )
	},
	{	// 6B
		LSN_DIRECT_PAGE_RMW( ROR, ROR, Ror )
	},
	{	// 6C
		LSN_ABSOLUTE_RMW( ROR, ROR, Ror )
	},
	{	// 6D
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
			&CSpc700::Null<LSN_W>,															&CSpc700::Push_Phi2<CSpc700::LSN_RT_Y, 0>,
			&CSpc700::Null<LSN_N, false, true>,												&CSpc700::Null_Phi2,
			&CSpc700::BeginInst
		},
		4, LSN_AM_IMPLIED, 1, LSN_I_PUSH, "PUSH", "Implied", "PHY"
	},
	{	// 6E
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Operand_To_DirectPage<LSN_TO_A, true>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Dbnz,																	&CSpc700::Write_PtrOrAddr_L_Phi2<LSN_TO_A, CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::EndIfNotJmp_BeginInst,												&CSpc700::Null_Phi2,
			&CSpc700::Branch_UpdatePc_L,													&CSpc700::Null_Phi2,
			&CSpc700::Branch_UpdatePc_H_BeginInst
		},
		5, LSN_AM_DIRECT_PAGE_RELATIVE, 3, LSN_I_DBNZ, "DBNZ", "Direct Page Relative d, r", "DBNZ"
	},
	{	// 6F
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Null_Phi2<1>,
			&CSpc700::Null<LSN_R, false, true>,												&CSpc700::Pull_Phi2<CSpc700::LSN_RT_PC_L, 0>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Pull_Phi2<CSpc700::LSN_RT_PC_H, 1>,
			&CSpc700::BeginInst<false, true>
		},
		5, LSN_AM_IMPLIED, 1, LSN_I_RET, "RET", "Implied", "RTS"
	},


	/** 70-77 */
	{	// 70
		LSN_RELATIVE( BVS, V(), 1 )
	},
	{	// 71
		LSN_IMPLIED_BCC( 7 )
	},
	{	// 72
		LSN_DIRECT_PAGE_BIT_RMW( CLR1, CLR1, 3, 0 )
	},
	{	// 73
		LSN_PAGE_BIT_RELATIVE( BBC, 3, 0 )
	},
	{	// 74
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_DIRECT_PAGE_INDEXED_X_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 75
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_ABSOLUTE_X_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 76
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_ABSOLUTE_Y_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 77
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_A, false>
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},


	/** 78-7F */
	{	// 78
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_DUMMY, false>
		LSN_DIRECT_PAGE_IMMEDIATE_RMW( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
	},
	{	// 79
#define LSN_TMP_INST	Cmp_BeginInst<CSpc700::LSN_RT_DUMMY, false>
		LSN_INDIRECT_X_INDIRECT_Y_RMW( CMP, CMP, LSN_TMP_INST )
#undef LSN_TMP_INST
		//{
		//	/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
		//	&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_DUMMY>,
		//	&CSpc700::Null<LSN_R, false>,													&CSpc700::Read_Y_Phi2<CSpc700::LSN_RT_OPERAND0>,
		//	&CSpc700::Null<LSN_R>,															&CSpc700::Read_X_Phi2<CSpc700::LSN_RT_OPERAND1>,
		//	&CSpc700::Or_BeginInst<false, true>,											&CSpc700::Write_X_Phi2<CSpc700::LSN_RT_OPERAND0>,
		//	&CSpc700::BeginInst
		//},
		//5, LSN_AM_INDIRECT_X_INDIRECT_Y, 1, LSN_I_ ## NAME0, #NAME0, "Indirect Page to Indirect Page (X), (Y) (Read/Modify/Write)", #NAME1
	},
	{	// 7A
		{
			/* BeginInst() */																&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPCODE>,
			&CSpc700::Null<LSN_R, true>,													&CSpc700::Fetch_IncPc_Phi2<CSpc700::LSN_RT_OPERAND>,
			&CSpc700::Operand_To_DirectPage<LSN_TO_A, true>,								&CSpc700::Read_PtrOrAddr_L_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND16_L>,
			&CSpc700::Null<LSN_R>,															&CSpc700::Null_Phi2,
			&CSpc700::Null<LSN_R>,															&CSpc700::Read_PtrOrAddr_H_Phi2<LSN_FROM_A, CSpc700::LSN_RT_OPERAND16_H, 0xFF>,
			&CSpc700::AddW_BeginInst
		},
		5, LSN_AM_DIRECT_PAGE, 2, LSN_I_ADDW, "ADDW", "Direct Page d (Read 16)", "ADW"
	},
};

#undef LSN_R
#undef LSN_W
#undef LSN_N
#undef LSN_ABSOLUTE_BIT_4
#undef LSN_ABSOLUTE_BIT_5
#undef LSN_DIRECT_PAGE_INDEXED_X_R_RMW
#undef LSN_DIRECT_PAGE_INDEXED_X_R
#undef LSN_DIRECT_PAGE_DIRECT_PAGE_RMW
#undef LSN_IMMEDIATE_R
#undef LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R
#undef LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R
#undef LSN_INDIRECT_X_INDIRECT_Y_RMW
#undef LSN_INDIRECT_X_R
#undef LSN_ABSOLUTE_Y_R
#undef LSN_ABSOLUTE_X_R
#undef LSN_ABSOLUTE_RMW_BIT
#undef LSN_ABSOLUTE_RMW
#undef LSN_ABSOLUTE_R
#undef LSN_DIRECT_PAGE_IMMEDIATE_RMW
#undef LSN_DIRECT_PAGE_RMW_16
#undef LSN_DIRECT_PAGE_RMW
#undef LSN_DIRECT_PAGE_R
#undef LSN_RELATIVE
#undef LSN_PAGE_BIT_RELATIVE
#undef LSN_IMPLIED_BCC
#undef LSN_DIRECT_PAGE_BIT
