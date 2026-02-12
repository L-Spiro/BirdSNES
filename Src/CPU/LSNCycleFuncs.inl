#define LSN_STACK_RELATIVE_R( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC, }, }, 4, 4, LSN_AM_STACK_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative (Read)"
#define LSN_STACK_RELATIVE_W( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>, &CRicoh5A22::BeginInst, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst, }, }, 4, 4, LSN_AM_STACK_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative (Write)"

#define LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( NAME, FUNC )								{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 7, 7, LSN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative Indirect Indexed (Read)"

#define LSN_DIRECT_PAGE_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_ ## NAME, #NAME, "Direct (Read)"
#define LSN_DIRECT_PAGE_RMW( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::SkipIfM_Phi2, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst, }, }, 5, 5, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_ ## NAME, #NAME, "Direct (Read/Modify/Write)"

#define LSN_DIRECT_PAGE_WITH_X_R( NAME, FUNC )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct, X (Read)"
#define LSN_DIRECT_PAGE_WITH_X_RMW( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::Null<LSN_R, false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::Null<LSN_R, false, false, true> }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct, X (Read/Modify/Write)"

#define LSN_DIRECT_PAGE_INDIRECT_R( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect (Read)"

#define LSN_DIRECT_PAGE_INDIRECT_LONG_R( NAME, FUNC )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Long (Read)"
#define LSN_DIRECT_PAGE_INDIRECT_LONG_W( NAME, FUNC )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::BeginInst }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Long (Write)"

#define LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( NAME, FUNC )									{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC, }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indexed Indirect (d,x) (Read)"
#define LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_W( NAME, FUNC )									{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_P, true, true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_P, true>, &CRicoh5A22::BeginInst, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst, }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indexed Indirect (d,x) (Write)"

#define LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( NAME, FUNC )									{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Indexed (d),y (Read)"

#define LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( NAME, FUNC )								{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_W, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_W, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A, true>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Indexed Long [d],y (Read)"

#define LSN_IMMEDIATE( NAME, FUNC )															{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<true, true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_High_IncPc<true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, true>, &CRicoh5A22::FUNC }, }, 2, 2, LSN_AM_IMMEDIATE, 2, 2, LSN_I_ ## NAME, #NAME, "Immediate"

#define LSN_ABSOLUTE_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 4, 4, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Read)"
#define LSN_ABSOLUTE_RMW( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, }, 6, 6, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Read/Modify/Write)"
#define LSN_ABSOLUTE_W_XREG( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_A, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst }, }, 4, 4, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Write)"
#define LSN_ABSOLUTE_W_MREG( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, true, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_A, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst }, }, 4, 4, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Write)"

#define LSN_ABSOLUTE_LONG_R( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC }, }, 5, 5, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long (Read)"
#define LSN_ABSOLUTE_LONG_W_MorX( NAME, FUNC, SKIPIFM)										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_A, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::BeginInst },}, 5, 5, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long (Write)"

#define LSN_ABSOLUTE_LONG_X_R( NAME, FUNC )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC, }, }, 5, 5, LSN_AM_ABSOLUTE_LONG_X, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long, X (Read)"

#define LSN_ABSOLUTE_INDEXED_X_R( NAME, FUNC )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 4, 4, LSN_AM_IMPLIED, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, X (Read)"
#define LSN_ABSOLUTE_INDEXED_X_RMW( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst<false, false, true>, }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, }, 7, 7, LSN_AM_IMPLIED, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, X (Read/Modiy/Write)"

#define LSN_ABSOLUTE_INDEXED_Y_R( NAME, FUNC )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC }, }, 4, 4, LSN_AM_ABSOLUTE_INDEXED_Y, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, Y (Read)"

#define LSN_BRANCH( NAME, COND, VALUE )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Branch_Cycle1<COND, VALUE>, &CRicoh5A22::Branch_Cycle1_Phi2, &CRicoh5A22::Branch_Cycle2, &CRicoh5A22::Branch_Cycle2_Phi2, &CRicoh5A22::Branch_Cycle3_Native }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Branch_Cycle1<COND, VALUE>, &CRicoh5A22::Branch_Cycle1_Phi2, &CRicoh5A22::Branch_Cycle2, &CRicoh5A22::Branch_Cycle2_Phi2, &CRicoh5A22::Branch_Cycle3, &CRicoh5A22::Branch_Cycle3_Phi2, &CRicoh5A22::Branch_Cycle4 }, }, 2, 2, LSN_AM_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Relative"

CRicoh5A22::LSN_INSTR CRicoh5A22::m_iInstructionSet[256] = {								/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::Push_Pb_Brk_Phi2<0>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_High_Brk_Phi2<-1>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_Low_Brk_Phi2<-2>,
				&CRicoh5A22::SelectBrkVectors<false>,										&CRicoh5A22::Push_S_Brk_Phi2<-3>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null_RorW<true>,												&CRicoh5A22::Push_Pc_High_Brk_Phi2<0>,
				&CRicoh5A22::Null_RorW,														&CRicoh5A22::Push_Pc_Low_Brk_Phi2<-1>,
				&CRicoh5A22::SelectBrkVectors<false>,										&CRicoh5A22::Push_S_Brk_Phi2<-2>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
		},
		8, 7, LSN_AM_IMPLIED, 2, 2, LSN_I_BRK, "BRK", "Implied"
	},
	{
		// 01
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( ORA, Ora )
	},
	{	// 02
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pb_Phi2<0, false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-2>,
				&CRicoh5A22::SelectCopVectors<false>,										&CRicoh5A22::Push_S_Phi2<-3>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,													&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-1>,
				&CRicoh5A22::SelectCopVectors<false>,										&CRicoh5A22::Push_S_Phi2<-2>,
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
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::AslOnA_BeginInst<false>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
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
		LSN_DIRECT_PAGE_WITH_X_R( ORA, Ora )
	},
	{	// 16
		LSN_DIRECT_PAGE_WITH_X_RMW( ASL, Asl )
	},
	{	// 17
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( ORA, Ora )
	},


	/** 18-1F */
	{	// 18
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Clc_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Clc_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_CLC, "CLC", "Implied"
	},
	{	// 19
		LSN_ABSOLUTE_INDEXED_Y_R( ORA, Ora )
	},
	{	// 1A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::IncOnA_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::IncOnA_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_INC, "INC", "Implied"
	},
	{	// 1B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tcs_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tcs_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_TCS, "TSC", "Implied"
	},
	{	// 1C
		LSN_ABSOLUTE_RMW( TRB, Trb )
	},
	{	// 1D
		LSN_ABSOLUTE_INDEXED_X_R( ORA, Ora )
	},
	{	// 1E
		LSN_ABSOLUTE_INDEXED_X_RMW( ASL, Asl )
	},
	{	// 1F
		LSN_ABSOLUTE_LONG_X_R( ORA, Ora )
	},


	/** 20-27 */
	{	// 20
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_DecPc_Phi2<false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-1, true>,
				&CRicoh5A22::Jsr_Absolute_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_DecPc_Phi2<false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-1, true>,
				&CRicoh5A22::Jsr_Absolute_BeginInst,
			},
		},
		6, 6, LSN_AM_ABSOLUTE, 3, 3, LSN_I_JSR, "JSR", "Absolute"
	},
	{
		// 21
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( AND, And )
	},
	{	// 22
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pb_Brk_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_Discard_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_High_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-2, true>,
				&CRicoh5A22::Jsl_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pb_Brk_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_Discard_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_High_Phi2<-1, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-2, true, true>,
				&CRicoh5A22::Jsl_BeginInst,
			},
		},
		8, 8, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_JSL, "JSL", "Absolute Long"
	},
	{	// 23
		LSN_STACK_RELATIVE_R( AND, And )
	},
	{	// 24
		LSN_DIRECT_PAGE_R( BIT, Bit_BeginInst )
	},
	{	// 25
		LSN_DIRECT_PAGE_R( AND, And )
	},
	{	// 26
		LSN_DIRECT_PAGE_RMW( ROL, Rol )
	},
	{	// 27
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( AND, And )
	},


	/** 28-2F */
	{	// 28
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true>,
				&CRicoh5A22::Plp_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Plp_BeginInst,
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLP, "PLP", "Implied"
	},
	{	// 29
		LSN_IMMEDIATE( AND, And<true> )
	},
	{	// 2A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::RolOnA_BeginInst<false>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::RolOnA_BeginInst<false>
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_ROL, "ROL", "Implied"
	},
	{	// 2B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, true>,
				&CRicoh5A22::Pld_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, true, true>,
				&CRicoh5A22::Pld_BeginInst,
			},
		},
		5, 5, LSN_AM_IMPLIED, 1, 1, LSN_I_PLD, "PLD", "Implied"
	},
	{	// 2C
		LSN_ABSOLUTE_R( BIT, Bit_BeginInst )
	},
	{	// 2D
		LSN_ABSOLUTE_R( AND, And )
	},
	{	// 2E
		LSN_ABSOLUTE_RMW( ROL, Rol )
	},
	{	// 2F
		LSN_ABSOLUTE_LONG_R( AND, And )
	},


	/** 30-37 */
	{	// 30
		LSN_BRANCH( BMI, N(), 1 )
	},
	{	// 31
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( AND, And )
	},
	{	// 32
		LSN_DIRECT_PAGE_INDIRECT_R( AND, And )
	},
	{	// 33
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( AND, And )
	},
	{	// 34
		LSN_DIRECT_PAGE_WITH_X_R( BIT, Bit_BeginInst )
	},
	{	// 35
		LSN_DIRECT_PAGE_WITH_X_R( AND, And )
	},
	{	// 36
		LSN_DIRECT_PAGE_WITH_X_RMW( ROL, Rol )
	},
	{	// 37
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( AND, And )
	},


	/** 38-3F */
	{	// 38
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Sec_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Sec_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_SEC, "SEC", "Implied"
	},
	{	// 39
		LSN_ABSOLUTE_INDEXED_Y_R( AND, And )
	},
	{	// 3A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::DecOnA_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::DecOnA_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_DEC, "DEC", "Implied"
	},
	{	// 3B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tsc_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tsc_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_TSC, "TSC", "Implied"
	},
	{	// 3C
		LSN_ABSOLUTE_INDEXED_X_R( BIT, Bit_BeginInst )
	},
	{	// 3D
		LSN_ABSOLUTE_INDEXED_X_R( AND, And )
	},
	{	// 3E
		LSN_ABSOLUTE_INDEXED_X_RMW( ROL, Rol )
	},
	{	// 3F
		LSN_ABSOLUTE_LONG_X_R( AND, And )
	},


	/** 40-47 */
	{	// 40
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Copy_Operand_To_Status_Mask<0>,								&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Bank_Phi2<3, true>,
				&CRicoh5A22::Rti_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Copy_Operand_To_Status_Mask<M() | X()>,						&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, true>,
				&CRicoh5A22::Rti_BeginInst,
			},
		},
		7, 6, LSN_AM_IMPLIED, 1, 1, LSN_I_RTI, "RTI", "Implied"
	},
	{
		// 41
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( EOR, Eor_BeginInst )
	},
	{	// 42
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,
				&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, true>,
				&CRicoh5A22::Wdm_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,
				&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, true>,
				&CRicoh5A22::Wdm_BeginInst,
			},
		},
		2, 2, LSN_AM_IMMEDIATE, 2, 2, LSN_I_WDM, "WDM", "Immediate"
	},
	{	// 43
		LSN_STACK_RELATIVE_R( EOR, Eor_BeginInst )
	},
	{	// 44
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,											&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<-1>,									&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,											&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<-1>,									&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
		},
		7, 7, LSN_AM_BLOCK_MOVE, 3, 3, LSN_I_MVP, "MVP", "Block Move (Positive)"
	},
	{	// 45
		LSN_DIRECT_PAGE_R( EOR, Eor_BeginInst )
	},
	{	// 46
		LSN_DIRECT_PAGE_RMW( LSR, Lsr )
	},
	{	// 47
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( EOR, Eor_BeginInst )
	},


	/** 48-4F */
	{	// 48
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2<true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_A_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W, false, true>,										&CRicoh5A22::Push_A_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_A_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHA, "PHA", "Implied"
	},
	{	// 49
		LSN_IMMEDIATE( EOR, Eor_BeginInst<true> )
	},
	{	// 4A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::LsrOnA_BeginInst<false>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::LsrOnA_BeginInst<false>
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_LSR, "LSR", "Implied"
	},
	{	// 4B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Pb_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Pb_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHK, "PHK", "Implied"
	},
	{	// 4C
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst,
			},
		},
		3, 3, LSN_AM_ABSOLUTE, 3, 3, LSN_I_JMP, "JMP", "Absolute"
	},
	{	// 4D
		LSN_ABSOLUTE_R( EOR, Eor_BeginInst )
	},
	{	// 4E
		LSN_ABSOLUTE_RMW( LSR, Lsr )
	},
	{	// 4F
		LSN_ABSOLUTE_LONG_R( EOR, Eor_BeginInst )
	},


	/** 50-57 */
	{	// 50
		LSN_BRANCH( BVC, V(), 0 )
	},
	{	// 51
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( EOR, Eor_BeginInst )
	},
	{	// 52
		LSN_DIRECT_PAGE_INDIRECT_R( EOR, Eor_BeginInst )
	},
	{	// 53
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( EOR, Eor_BeginInst )
	},
	{	// 54
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,											&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<1>,									&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,											&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<1>,									&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
		},
		7, 7, LSN_AM_BLOCK_MOVE, 3, 3, LSN_I_MVN, "MVN", "Block Move (Negative)"
	},
	{	// 55
		LSN_DIRECT_PAGE_WITH_X_R( EOR, Eor_BeginInst )
	},
	{	// 56
		LSN_DIRECT_PAGE_WITH_X_RMW( LSR, Lsr )
	},
	{	// 57
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( EOR, Eor_BeginInst )
	},


	/** 58-5F */
	{	// 58
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Cli_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Cli_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_CLI, "CLI", "Implied"
	},
	{	// 59
		LSN_ABSOLUTE_INDEXED_Y_R( EOR, Eor_BeginInst )
	},
	{	// 5A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2<false, INT8_MIN, false, true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Y_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W, false, true>,										&CRicoh5A22::Push_Y_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W, false, true>,										&CRicoh5A22::Push_Y_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHY, "PHY", "Implied"
	},
	{	// 5B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tcd_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tcd_BeginInst,
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_TCD, "TCD", "Implied"
	},
	{	// 5C
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Bank_IncPc_Phi2<true>,
				&CRicoh5A22::Jsl_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Bank_IncPc_Phi2<true>,
				&CRicoh5A22::Jsl_BeginInst,
			},
		},
		4, 4, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_JML, "JML", "Absolute Long"
	},
	{	// 5D
		LSN_ABSOLUTE_INDEXED_X_R( EOR, Eor_BeginInst )
	},
	{	// 5E
		LSN_ABSOLUTE_INDEXED_X_RMW( LSR, Lsr )
	},
	{	// 5F
		LSN_ABSOLUTE_LONG_X_R( EOR, Eor_BeginInst )
	},


	/** 60-67 */
	{	// 60
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Rts_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Rts_BeginInst,
			},
		},
		6, 6, LSN_AM_IMPLIED, 1, 1, LSN_I_RTS, "RTS", "Implied"
	},
	{
		// 61
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( ADC, Adc_BeginInst )
	},
	{	// 62
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Per_IncPc,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true>,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Per_IncPc,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true>,
			},
		},
		6, 6, LSN_AM_PROGRAM_COUNTER_RELATIVE_LONG, 3, 3, LSN_I_PER, "PER", "Program Counter Relative Long"
	},
	{	// 63
		LSN_STACK_RELATIVE_R( ADC, Adc_BeginInst )
	},
	{	// 64
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::WriteBank0_Zero_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst,
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STZ, "STZ", "Direct (Write)"
	},
	{	// 65
		LSN_DIRECT_PAGE_R( ADC, Adc_BeginInst )
	},
	{	// 66
		LSN_DIRECT_PAGE_RMW( ROR, Ror )
	},
	{	// 67
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( ADC, Adc_BeginInst )
	},


	/** 68-6F */
	{	// 68
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, false, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, true>,
				&CRicoh5A22::Pla_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Pla_BeginInst,
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLA, "PLA", "Implied"
	},
	{	// 69
		LSN_IMMEDIATE( ADC, Adc_BeginInst<true> )
	},
	{	// 6A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::RorOnA_BeginInst<false>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::RorOnA_BeginInst<false>
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_ROR, "ROR", "Implied"
	},
	{	// 6B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Bank_Phi2<3, true>,
				&CRicoh5A22::Rtl_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, false, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Bank_Phi2<3, true>,
				&CRicoh5A22::Rtl_BeginInst,
			},
		},
		6, 6, LSN_AM_IMPLIED, 1, 1, LSN_I_RTL, "RTL", "Implied"
	},
	{	// 6C
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst,
			},
		},
		5, 5, LSN_AM_ABSOLUTE_INDIRECT, 3, 3, LSN_I_JMP, "JMP", "Absolute Indirect (Jump)"
	},
	{	// 6D
		LSN_ABSOLUTE_R( ADC, Adc_BeginInst )
	},
	{	// 6E
		LSN_ABSOLUTE_RMW( ROR, Ror )
	},
	{	// 6F
		LSN_ABSOLUTE_LONG_R( ADC, Adc_BeginInst )
	},


	/** 70-77 */
	{	// 70
		LSN_BRANCH( BVS, V(), 1 )
	},
	{	// 71
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( ADC, Adc_BeginInst )
	},
	{	// 72
		LSN_DIRECT_PAGE_INDIRECT_R( ADC, Adc_BeginInst )
	},
	{	// 73
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( ADC, Adc_BeginInst )
	},
	{	// 74
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_Zero_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst,
			},
		},
		4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_STZ, "STZ", "Direct, X (Write)"
	},
	{	// 75
		LSN_DIRECT_PAGE_WITH_X_R( ADC, Adc_BeginInst )
	},
	{	// 76
		LSN_DIRECT_PAGE_WITH_X_RMW( ROR, Ror )
	},
	{	// 77
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( ADC, Adc_BeginInst )
	},


	/** 78-7F */
	{	// 78
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Sei_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Sei_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_SEI, "SEI", "Implied"
	},
	{	// 79
		LSN_ABSOLUTE_INDEXED_Y_R( ADC, Adc_BeginInst )
	},
	{	// 7A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, false, false, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, true>,
				&CRicoh5A22::Ply_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Ply_BeginInst,
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLY, "PLY", "Implied"
	},
	{	// 7B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tdc_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Tdc_BeginInst,
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_TDC, "TDC", "Implied"
	},
	{	// 7C
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, false, false, true, true>,	&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2<LSN_FROM_P, true, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, false, false, true, true>,	&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2<LSN_FROM_P, true, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst,
			},
		},
		6, 6, LSN_AM_ABSOLUTE_INDEXED_INDIRECT, 3, 3, LSN_I_JMP, "JMP", "Absolute Indexed Indirect (Jump)"
	},
	{	// 7D
		LSN_ABSOLUTE_INDEXED_X_R( ADC, Adc_BeginInst )
	},
	{	// 7E
		LSN_ABSOLUTE_INDEXED_X_RMW( ROR, Ror )
	},
	{	// 7F
		LSN_ABSOLUTE_LONG_X_R( ADC, Adc_BeginInst )
	},


	/** 80-87 */
	{	// 80
		LSN_BRANCH( BRA, 0, 0 )
	},
	{	// 81
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_W( STA, Sta )
	},
	{
		// 82
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Brl_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Brl_BeginInst,
			},
		},
		4, 4, LSN_AM_PROGRAM_COUNTER_RELATIVE_LONG, 3, 3, LSN_I_BRL, "BRL", "Program Counter Relative Long"
	},
	{	// 83
		LSN_STACK_RELATIVE_W( STA, Sta )
	},
	{	// 84
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::WriteBank0_Y_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst,
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STY, "STY", "Direct (Write)"
	},
	{
		// 85
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::WriteBank0_A_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst,
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STA, "STA", "Direct (Write)"
	},
	{	// 86
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::WriteBank0_X_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst,
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STX, "STX", "Direct (Write)"
	},
	{	// 87
		LSN_DIRECT_PAGE_INDIRECT_LONG_W( STA, Sta )		
	},


	/** 88-8F */
	{	// 88
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Dey_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Dey_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_DEY, "DEY", "Implied"
	},
	{	// 89
		LSN_IMMEDIATE( BIT, Bit_BeginInst<true> )
	},
	{	// 8A
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Txa_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Txa_BeginInst,
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_TXA, "TXA", "Implied"
	},
	{	// 8B
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Db_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Db_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHB, "PHB", "Implied"
	},
	{	// 8C
		LSN_ABSOLUTE_W_XREG( STY, Sty<true> )
	},
	{	// 8D
		LSN_ABSOLUTE_W_MREG( STA, Sta<true> )
	},
	{	// 8E
		LSN_ABSOLUTE_W_XREG( STX, Stx<true> )
	},
	{	// 8F
		LSN_ABSOLUTE_LONG_W_MorX( STA, Sta<true>, true /** Skip if M. */ )
	},


	/** 90-97 */
	{	// 90
		LSN_BRANCH( BCC, C(), 0 )
	},
};

