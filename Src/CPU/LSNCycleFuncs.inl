#define LSN_INDIRECT_X_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::Ora, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC, }, }, 6, 6, LSN_AM_INDIRECT_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indexed Indirect (d,x) (Read)"

#define LSN_STACK_RELATIVE_R( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC, }, }, 4, 4, LSN_AM_STACK_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative (Read)"

#define LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( NAME, FUNC )								{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::Ora }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::Ora }, }, 7, 7, LSN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative Indirect Indexed (Read)"

#define LSN_DIRECT_PAGE_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_ ## NAME, #NAME, "Direct (Read)"
#define LSN_DIRECT_PAGE_RMW( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::SkipIfM_Phi2, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst, }, }, 5, 5, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_ ## NAME, #NAME, "Direct (Read/Modify/Write)"

#define LSN_DIRECT_PAGE_INDEXED_X_R( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct, X (Read)"
#define LSN_DIRECT_PAGE_INDEXED_X_RMW( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::Null<LSN_R, false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::Null<LSN_R, false, false, true> }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indexed Indirect (d,x) (Read/Modify/Write)"

#define LSN_DIRECT_PAGE_INDIRECT_R( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect (Read)"

#define LSN_DIRECT_PAGE_INDIRECT_LONG_R( NAME, FUNC )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Long (Read)"

#define LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( NAME, FUNC )									{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Indexed (d),y (Read)"

#define LSN_IMMEDIATE( NAME, FUNC )															{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<true, true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_High_IncPc<true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, true>, &CRicoh5A22::FUNC }, }, 3, 2, LSN_AM_IMMEDIATE, 2, 2, LSN_I_ ## NAME, #NAME, "Immediate"

#define LSN_ABSOLUTE_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 4, 4, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Read)"
#define LSN_ABSOLUTE_RMW( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, }, 6, 6, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Read/Modify/Write)"

#define LSN_ABSOLUTE_LONG_R( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 5, 5, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long (Read)"

#define LSN_BRANCH( NAME, COND, VALUE )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Branch_Cycle1<COND, VALUE>, &CRicoh5A22::Branch_Cycle1_Phi2, &CRicoh5A22::Branch_Cycle2, &CRicoh5A22::Branch_Cycle2_Phi2, &CRicoh5A22::Branch_Cycle3_Native }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Branch_Cycle1<COND, VALUE>, &CRicoh5A22::Branch_Cycle1_Phi2, &CRicoh5A22::Branch_Cycle2, &CRicoh5A22::Branch_Cycle2_Phi2, &CRicoh5A22::Branch_Cycle3, &CRicoh5A22::Branch_Cycle3_Phi2, &CRicoh5A22::Branch_Cycle4 }, }, 2, 2, LSN_AM_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Relative"

CRicoh5A22::LSN_INSTR CRicoh5A22::m_iInstructionSet[256] = {								/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::Push_Pb_Phi2<0>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_High_Phi2<-1>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_Low_Phi2<-2>,
				&CRicoh5A22::SelectBrkVectors<false>,										&CRicoh5A22::Push_S_Phi2<-3>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_Low_Phi2<-1>,
				&CRicoh5A22::SelectBrkVectors<false>,										&CRicoh5A22::Push_S_Phi2<-2>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
		},
		8, 7, LSN_AM_IMPLIED, 2, 2, LSN_I_BRK, "BRK", "Implied"
	},
	{
		// 01
		LSN_INDIRECT_X_R( ORA, Ora )
	},
	{	// 02
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pb_Phi2<0>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-2>,
				&CRicoh5A22::SelectCopVectors<false>,										&CRicoh5A22::Push_S_Phi2<-3, true>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-1>,
				&CRicoh5A22::SelectCopVectors<false>,										&CRicoh5A22::Push_S_Phi2<-2, true>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			}
		},
		8, 7, LSN_AM_IMPLIED, 2, 2, LSN_I_COP, "COP", "Implied"
	},
	{	// 03
		LSN_STACK_RELATIVE_R( ORA, Ora )
	},
	{	// 04
		LSN_DIRECT_PAGE_RMW( TSB, Tsb )
	},
	{	// 05
		LSN_DIRECT_PAGE_R( ORA, Ora )
	},
	{	// 06
		LSN_DIRECT_PAGE_RMW( ASL, Asl )
	},
	{	// 07
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( ORA, Ora )
	},


	/** 08-0F */
	{	// 08
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Php,															&CRicoh5A22::Push_Operand_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Php,															&CRicoh5A22::Push_Operand_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>,
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHP, "PHP", "Implied"
	},
	{	// 09
		LSN_IMMEDIATE( ORA, Ora<true> )
	},
	{	// 0A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::AslOnA_BeginInst<false>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::AslOnA_BeginInst<false>
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_ASL, "ASL", "Implied"
	},
	{	// 0B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_D_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_D_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_D_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_D_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PHD, "PHD", "Implied"
	},
	{	// 0C
		LSN_ABSOLUTE_RMW( TSB, Tsb )
	},
	{	// 0D
		LSN_ABSOLUTE_R( ORA, Ora )
	},
	{	// 0E
		LSN_ABSOLUTE_RMW( ASL, Asl )
	},
	{	// 0F
		LSN_ABSOLUTE_LONG_R( ORA, Ora )
	},


	/** 10-17 */
	{	// 10
		LSN_BRANCH( BPL, N(), 0 )
	},
	{	// 11
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( ORA, Ora )
	},
	{	// 12
		LSN_DIRECT_PAGE_INDIRECT_R( ORA, Ora )
	},
	{	// 13
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( ORA, Ora )
	},
	{	// 14
		LSN_DIRECT_PAGE_RMW( TRB, Trb )
	},
	{	// 15
		LSN_DIRECT_PAGE_INDEXED_X_R( ORA, Ora )
	},
	{	// 16
		LSN_DIRECT_PAGE_INDEXED_X_RMW( ASL, Asl )
	}
};






