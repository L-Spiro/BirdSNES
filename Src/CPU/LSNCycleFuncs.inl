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
};