#define LSN_INDIRECT_X_R( NAME, FUNC )												{ {	&CRicoh5A22::FetchPointerAndIncPc_Phi2, &CRicoh5A22::AddXAndDAndPointerToAddressAndIncPc, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::FixPointerHigh, &CRicoh5A22::Null_Phi2, &CRicoh5A22::ReadPointerToAddressLow, &CRicoh5A22::ReadPointerToAddressLow_Phi2, &CRicoh5A22::Null_Read, &CRicoh5A22::ReadPointerToAddressHigh_Phi2, &CRicoh5A22::Null_Read, &CRicoh5A22::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CRicoh5A22::Null_Read, &CRicoh5A22::ReadAddressAndBankToOperandHigh_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::PrefetchNextOp }, {	&CRicoh5A22::FetchPointerAndIncPc_Phi2, &CRicoh5A22::AddXAndDAndPointerToAddressAndIncPc, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::FixPointerHigh, &CRicoh5A22::Null_Phi2, &CRicoh5A22::ReadPointerToAddressLow, &CRicoh5A22::ReadPointerToAddressLow_Phi2, &CRicoh5A22::Null_Read, &CRicoh5A22::ReadPointerToAddressHigh_Phi2, &CRicoh5A22::Null_Read, &CRicoh5A22::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CRicoh5A22::Null_Read, &CRicoh5A22::ReadAddressAndBankToOperandHigh_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::PrefetchNextOp }, }, 8, 7, LSN_AM_INDIRECT_X, 2, 2, LSN_I_ ## NAME

CRicoh5A22::LSN_INSTR CRicoh5A22::m_iInstructionSet[256] = {								/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_Phi2,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::PushPb_Phi2<0>,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::Push_Pc_H_Phi2<-1>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_L_Phi2<-2>,
				&CRicoh5A22::SelectBrkVectors<false>,										&CRicoh5A22::Push_S_Phi2<-3>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_Phi2,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::Push_Pc_H_Phi2<0>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_L_Phi2<-1>,
				&CRicoh5A22::SelectBrkVectors<false>,										&CRicoh5A22::Push_S_Phi2<-2>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
		},
		8, 7, LSN_AM_IMPLIED, 2, 2, LSN_I_BRK,
	},

	{
		{	// 01
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>,				&CRicoh5A22::SkipOnDL_Phi2,
				&CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>,					&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_OperandLow_SkipIfM_Phi2<LSN_FROM_P>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_OperandHigh_Phi2<LSN_FROM_P>,
				&CRicoh5A22::Ora,
				/* BeginInst() */															/*&CRicoh5A22::FetchPointerAndIncPc_Phi2,
				&CRicoh5A22::AddXAndDAndPointerToAddressAndIncPc,							&CRicoh5A22::SkipOnDL_Phi2,
				&CRicoh5A22::FixPointerHigh,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::ReadPointerToAddressLow,										&CRicoh5A22::ReadPointerToAddressLow_Phi2,
				&CRicoh5A22::Null_Read,														&CRicoh5A22::ReadPointerToAddressHigh_Phi2,
				&CRicoh5A22::Null_Read,														&CRicoh5A22::ReadAddressAndBankToOperandLow_SkipIfM_Phi2,
				&CRicoh5A22::Null_Read,														&CRicoh5A22::ReadAddressAndBankToOperandHigh_Phi2,
				&CRicoh5A22::Ora_BeginInst,*/
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>,				&CRicoh5A22::SkipOnDL_Phi2,
				&CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>,					&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_OperandLow_SkipIfM_Phi2<LSN_FROM_P>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_OperandHigh_Phi2<LSN_FROM_P>,
				&CRicoh5A22::Ora,
				/* BeginInst() */															/*&CRicoh5A22::FetchPointerAndIncPc_Phi2,
				&CRicoh5A22::AddXAndDAndPointerToAddressAndIncPc,							&CRicoh5A22::SkipOnDL_Phi2,
				&CRicoh5A22::FixPointerHigh,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::ReadPointerToAddressLow,										&CRicoh5A22::ReadPointerToAddressLow_Phi2,
				&CRicoh5A22::Null_Read,														&CRicoh5A22::ReadPointerToAddressHigh_Phi2,
				&CRicoh5A22::Null_Read,														&CRicoh5A22::ReadAddressAndBankToOperandLow_SkipIfM_Phi2,
				&CRicoh5A22::Null_Read,														&CRicoh5A22::ReadAddressAndBankToOperandHigh_Phi2,
				&CRicoh5A22::Ora_BeginInst,*/
			},
		},
		8, 7, LSN_AM_INDIRECT_X, 2, 2, LSN_I_ORA
	}

	/*	{	// 01
		LSN_INDIRECT_X_R( ORA, Ora )
	},*/
};