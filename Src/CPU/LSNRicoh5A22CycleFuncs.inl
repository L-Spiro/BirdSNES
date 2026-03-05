#define LSN_STACK_RELATIVE_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC } }, 4, 4, LSN_AM_STACK_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative (Read)"
#define LSN_STACK_RELATIVE_W( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst } }, 4, 4, LSN_AM_STACK_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative (Write)"

#define LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( NAME, FUNC )									{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 7, 7, LSN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative Indirect Indexed (Read)"
#define LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_W( NAME, FUNC, SKIPIFM )							{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_StackOffset_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::BeginInst } }, 7, 7, LSN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Stack Relative Indirect Indexed (Write)"

#define LSN_DIRECT_PAGE_R( NAME, FUNC, SKIPIFM )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC } }, 3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_ ## NAME, #NAME, "Direct (Read)"
#define LSN_DIRECT_PAGE_RMW( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::SkipIfM_Phi2, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst } }, 5, 5, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_ ## NAME, #NAME, "Direct (Read/Modify/Write)"

#define LSN_DIRECT_PAGE_WITH_X_R( NAME, FUNC, SKIPIFM )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC } }, 4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct, X (Read)"
#define LSN_DIRECT_PAGE_WITH_X_RMW( NAME, FUNC )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_High_To_AddrOrPtr_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::Null<LSN_R, false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::WriteBank0_Operand_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::Null<LSN_R, false, false, true> } }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct, X (Read/Modify/Write)"

#define LSN_DIRECT_PAGE_INDIRECT_R( NAME, FUNC )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect (Read)"
#define LSN_DIRECT_PAGE_INDIRECT_W( NAME, FUNC, SKIPIFM )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_P, true, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst } }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect (Write)"

#define LSN_DIRECT_PAGE_INDIRECT_LONG_R( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Long (Read)"
#define LSN_DIRECT_PAGE_INDIRECT_LONG_W( NAME, FUNC )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::BeginInst } }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Long (Write)"

#define LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( NAME, FUNC )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indexed Indirect (d,x) (Read)"
#define LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_W( NAME, FUNC )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_P, true, true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>, &CRicoh5A22::Add_X_D_PtrOrAddr_To_AddrOrPtr_IncPc<LSN_TO_A>, &CRicoh5A22::SkipOnDL_Phi2, &CRicoh5A22::Fix_PtrOrAddr_From_AddrOrPtr_High<LSN_TO_A>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst } }, 6, 6, LSN_AM_DIRECT_PAGE_INDEXED_INDIRECT_X, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indexed Indirect (d,x) (Write)"

#define LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( NAME, FUNC )										{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 5, 5, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Indexed (d),y (Read)"
#define LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_W( NAME, FUNC, SKIPIFM )								{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_TO_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst } }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Indexed (d),y (Write)"

#define LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( NAME, FUNC )									{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_W, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>, &CRicoh5A22::Null<LSN_W, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A, true>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y, 2, 2, LSN_I_ ## NAME, #NAME, "Direct Indirect Indexed Long [d],y (Read)"
//#define LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_W( NAME, FUNC, SKIPIFM )					

#define LSN_IMMEDIATE( NAME, FUNC, SKIPIFM )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_High_IncPc<true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, true>, &CRicoh5A22::FUNC } }, 2, 2, LSN_AM_IMMEDIATE, 2, 2, LSN_I_ ## NAME, #NAME, "Immediate"

#define LSN_ABSOLUTE_R( NAME, FUNC, SKIPIFM )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC } }, 4, 4, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Read)"
#define LSN_ABSOLUTE_RMW( NAME, FUNC )															{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_High_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_DB_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst<false, false, true> } }, 6, 6, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Read/Modify/Write)"
#define LSN_ABSOLUTE_W( NAME, FUNC, SKIPIFM )													{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_DB_Phi2<LSN_TO_A, true, false>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_DB_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false, true>, &CRicoh5A22::BeginInst } }, 4, 4, LSN_AM_ABSOLUTE, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute (Write)"

#define LSN_ABSOLUTE_LONG_R( NAME, FUNC, SKIPIFM )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_A, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::FUNC } }, 5, 5, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long (Read)"
#define LSN_ABSOLUTE_LONG_W( NAME, FUNC, SKIPIFM )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_A, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_N, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>, &CRicoh5A22::BeginInst },}, 5, 5, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long (Write)"

#define LSN_ABSOLUTE_LONG_X_R( NAME, FUNC )														{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Bank_IncPc_Phi2, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false, false>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 5, 5, LSN_AM_ABSOLUTE_LONG_X, 4, 4, LSN_I_ ## NAME, #NAME, "Absolute Long, X (Read)"
//#define LSN_ABSOLUTE_LONG_X_W( NAME, FUNC, SKIPIFM )										

#define LSN_ABSOLUTE_INDEXED_X_R( NAME, FUNC, SKIPIFM )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 4, 4, LSN_AM_IMPLIED, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, X (Read)"
#define LSN_ABSOLUTE_INDEXED_X_RMW( NAME, FUNC )												{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, false>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Null_Phi2<true>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_TO_P>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst<false, false, true> }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, false>, &CRicoh5A22::Null<LSN_W>, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, false>, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>, &CRicoh5A22::BeginInst<false, false, true> } }, 7, 7, LSN_AM_IMPLIED, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, X (Read/Modiy/Write)"
#define LSN_ABSOLUTE_INDEXED_X_W( NAME, FUNC, SKIPIFM )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::BeginInst } }, 5, 5, LSN_AM_IMPLIED, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, X (Write)"

#define LSN_ABSOLUTE_INDEXED_Y_R( NAME, FUNC, SKIPIFM )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_High_Phi2<LSN_FROM_P, true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, true>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Read_PtrOrAddr_And_Bank_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::FUNC } }, 4, 4, LSN_AM_ABSOLUTE_INDEXED_Y, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, Y (Read)"
#define LSN_ABSOLUTE_INDEXED_Y_W( NAME, FUNC, SKIPIFM )											{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, SKIPIFM, true, !SKIPIFM>, &CRicoh5A22::Null<LSN_R>, &CRicoh5A22::Write_Operand_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_P, true>, &CRicoh5A22::BeginInst }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>, &CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false>, &CRicoh5A22::Null_Phi2, &CRicoh5A22::FUNC, &CRicoh5A22::Write_Operand_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>, &CRicoh5A22::BeginInst }}, 5, 5, LSN_AM_ABSOLUTE_INDEXED_Y, 3, 3, LSN_I_ ## NAME, #NAME, "Absolute, Y (Write)"

#define LSN_BRANCH( NAME, COND, VALUE )															{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Branch_Cycle1<COND, VALUE>, &CRicoh5A22::Branch_Cycle1_Phi2, &CRicoh5A22::Branch_Cycle2, &CRicoh5A22::Branch_Cycle2_Phi2, &CRicoh5A22::Branch_Cycle3_Native }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Branch_Cycle1<COND, VALUE>, &CRicoh5A22::Branch_Cycle1_Phi2, &CRicoh5A22::Branch_Cycle2, &CRicoh5A22::Branch_Cycle2_Phi2, &CRicoh5A22::Branch_Cycle3, &CRicoh5A22::Branch_Cycle3_Phi2, &CRicoh5A22::Branch_Cycle4 } }, 2, 2, LSN_AM_RELATIVE, 2, 2, LSN_I_ ## NAME, #NAME, "Relative"

#define LSN_IMPLIED_2( NAME, FUNC )																{ { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_Discard_Phi2<true>, &CRicoh5A22::FUNC }, { /* BeginInst() */ &CRicoh5A22::Fetch_Opcode_IncPc_Phi2, &CRicoh5A22::Null<LSN_R, true>, &CRicoh5A22::Fetch_Operand_Discard_Phi2<true>, &CRicoh5A22::FUNC }, }, 2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_ ## NAME, #NAME, "Implied"

CRicoh5A22::LSN_INSTR CRicoh5A22::m_iInstructionSet[256] = {									/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null_RorW<true>,													&CRicoh5A22::Push_Pb_Brk_Phi2<0>,
				&CRicoh5A22::Null_RorW,															&CRicoh5A22::Push_Pc_High_Brk_Phi2<-1>,
				&CRicoh5A22::Null_RorW,															&CRicoh5A22::Push_Pc_Low_Brk_Phi2<-2>,
				&CRicoh5A22::SelectBrkVectors<false>,											&CRicoh5A22::Push_S_Brk_Phi2<-3>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,														&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null_RorW<true>,													&CRicoh5A22::Push_Pc_High_Brk_Phi2<0>,
				&CRicoh5A22::Null_RorW,															&CRicoh5A22::Push_Pc_Low_Brk_Phi2<-1>,
				&CRicoh5A22::SelectBrkVectors<false>,											&CRicoh5A22::Push_S_Brk_Phi2<-2>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,														&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
		},
		8, 7, LSN_AM_IMPLIED, 2, 2, LSN_I_BRK, "BRK", "Implied"
	},
	{
		// 01
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( ORA, Ora_BeginInst )
	},
	{	// 02
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Push_Pb_Phi2<0, false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Push_Pc_High_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Push_Pc_Low_Phi2<-2>,
				&CRicoh5A22::SelectCopVectors<false>,											&CRicoh5A22::Push_S_Phi2<-3>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,														&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Push_Pc_Low_Phi2<-1>,
				&CRicoh5A22::SelectCopVectors<false>,											&CRicoh5A22::Push_S_Phi2<-2>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::CopyVectorToPc_L_Phi2,
				&CRicoh5A22::SetBrkFlags,														&CRicoh5A22::CopyVectorToPc_H_Phi2<false>,
				&CRicoh5A22::Brk_BeginInst
			}
		},
		8, 7, LSN_AM_IMPLIED, 2, 2, LSN_I_COP, "COP", "Implied"
	},
	{	// 03
		LSN_STACK_RELATIVE_R( ORA, Ora_BeginInst )
	},
	{	// 04
		LSN_DIRECT_PAGE_RMW( TSB, Tsb )
	},
	{	// 05
		LSN_DIRECT_PAGE_R( ORA, Ora_BeginInst, true )
	},
	{	// 06
		LSN_DIRECT_PAGE_RMW( ASL, Asl )
	},
	{	// 07
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( ORA, Ora_BeginInst )
	},


	/** 08-0F */
	{	// 08
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Php,																&CRicoh5A22::Push_Operand_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Php,																&CRicoh5A22::Push_Operand_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>,
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHP, "PHP", "Implied"
	},
	{	// 09
		LSN_IMMEDIATE( ORA, Ora_BeginInst<true>, true )
	},
	{	// 0A
		LSN_IMPLIED_2( ASL, AslOnA_BeginInst<false> )
	},
	{	// 0B
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_D_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_D_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_D_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_D_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PHD, "PHD", "Implied"
	},
	{	// 0C
		LSN_ABSOLUTE_RMW( TSB, Tsb )
	},
	{	// 0D
		LSN_ABSOLUTE_R( ORA, Ora_BeginInst, true )
	},
	{	// 0E
		LSN_ABSOLUTE_RMW( ASL, Asl )
	},
	{	// 0F
		LSN_ABSOLUTE_LONG_R( ORA, Ora_BeginInst, true )
	},


	/** 10-17 */
	{	// 10
		LSN_BRANCH( BPL, N(), 0 )
	},
	{	// 11
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( ORA, Ora_BeginInst )
	},
	{	// 12
		LSN_DIRECT_PAGE_INDIRECT_R( ORA, Ora_BeginInst )
	},
	{	// 13
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( ORA, Ora_BeginInst )
	},
	{	// 14
		LSN_DIRECT_PAGE_RMW( TRB, Trb )
	},
	{	// 15
		LSN_DIRECT_PAGE_WITH_X_R( ORA, Ora_BeginInst, true )
	},
	{	// 16
		LSN_DIRECT_PAGE_WITH_X_RMW( ASL, Asl )
	},
	{	// 17
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( ORA, Ora_BeginInst )
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
		LSN_ABSOLUTE_INDEXED_Y_R( ORA, Ora_BeginInst, true )
	},
	{	// 1A
		LSN_IMPLIED_2( INC, IncOnA_BeginInst )
	},
	{	// 1B
		LSN_IMPLIED_2( TCS, Tcs_BeginInst )
	},
	{	// 1C
		LSN_ABSOLUTE_RMW( TRB, Trb )
	},
	{	// 1D
		LSN_ABSOLUTE_INDEXED_X_R( ORA, Ora_BeginInst, true )
	},
	{	// 1E
		LSN_ABSOLUTE_INDEXED_X_RMW( ASL, Asl )
	},
	{	// 1F
		LSN_ABSOLUTE_LONG_X_R( ORA, Ora_BeginInst )
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
				&CRicoh5A22::Jsr_Absolute_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_DecPc_Phi2<false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Push_Pc_Low_Phi2<-1, true>,
				&CRicoh5A22::Jsr_Absolute_BeginInst
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Push_Pb_Brk_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_Discard_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Push_Pc_High_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Push_Pc_Low_Phi2<-2, true>,
				&CRicoh5A22::Jsl_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Push_Pb_Brk_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_Discard_Phi2<0>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Push_Pc_High_Phi2<-1, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Push_Pc_Low_Phi2<-2, true, true>,
				&CRicoh5A22::Jsl_BeginInst
			},
		},
		8, 8, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_JSL, "JSL", "Absolute Long"
	},
	{	// 23
		LSN_STACK_RELATIVE_R( AND, And )
	},
	{	// 24
		LSN_DIRECT_PAGE_R( BIT, Bit_BeginInst, true )
	},
	{	// 25
		LSN_DIRECT_PAGE_R( AND, And, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true>,
				&CRicoh5A22::Plp_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Plp_BeginInst
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLP, "PLP", "Implied"
	},
	{	// 29
		LSN_IMMEDIATE( AND, And<true>, true )
	},
	{	// 2A
		LSN_IMPLIED_2( ROL, RolOnA_BeginInst<false> )
	},
	{	// 2B
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, true>,
				&CRicoh5A22::Pld_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, true, true>,
				&CRicoh5A22::Pld_BeginInst
			},
		},
		5, 5, LSN_AM_IMPLIED, 1, 1, LSN_I_PLD, "PLD", "Implied"
	},
	{	// 2C
		LSN_ABSOLUTE_R( BIT, Bit_BeginInst, true )
	},
	{	// 2D
		LSN_ABSOLUTE_R( AND, And, true )
	},
	{	// 2E
		LSN_ABSOLUTE_RMW( ROL, Rol )
	},
	{	// 2F
		LSN_ABSOLUTE_LONG_R( AND, And, true )
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
		LSN_DIRECT_PAGE_WITH_X_R( BIT, Bit_BeginInst, true )
	},
	{	// 35
		LSN_DIRECT_PAGE_WITH_X_R( AND, And, true )
	},
	{	// 36
		LSN_DIRECT_PAGE_WITH_X_RMW( ROL, Rol )
	},
	{	// 37
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( AND, And )
	},


	/** 38-3F */
	{	// 38
		LSN_IMPLIED_2( SEC, Sec_BeginInst )
	},
	{	// 39
		LSN_ABSOLUTE_INDEXED_Y_R( AND, And, true )
	},
	{	// 3A
		LSN_IMPLIED_2( DEC, DecOnA_BeginInst )
	},
	{	// 3B
		LSN_IMPLIED_2( TSC, Tsc_BeginInst )
	},
	{	// 3C
		LSN_ABSOLUTE_INDEXED_X_R( BIT, Bit_BeginInst, true )
	},
	{	// 3D
		LSN_ABSOLUTE_INDEXED_X_R( AND, And, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Copy_Operand_To_Status_Mask<0>,									&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Bank_Phi2<3, true>,
				&CRicoh5A22::Rti_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Copy_Operand_To_Status_Mask<M() | X()>,							&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, true>,
				&CRicoh5A22::Rti_BeginInst
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, true>,
				&CRicoh5A22::Wdm_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, true>,
				&CRicoh5A22::Wdm_BeginInst
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,												&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<-1>,										&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,												&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<-1>,										&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
		},
		7, 7, LSN_AM_BLOCK_MOVE, 3, 3, LSN_I_MVP, "MVP", "Block Move (Positive)"
	},
	{	// 45
		LSN_DIRECT_PAGE_R( EOR, Eor_BeginInst, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2<true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_A_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W, false, true>,											&CRicoh5A22::Push_A_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_A_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHA, "PHA", "Implied"
	},
	{	// 49
		LSN_IMMEDIATE( EOR, Eor_BeginInst<true>, true )
	},
	{	// 4A
		LSN_IMPLIED_2( LSR, LsrOnA_BeginInst<false> )
	},
	{	// 4B
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Pb_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Pb_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHK, "PHK", "Implied"
	},
	{	// 4C
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
		},
		3, 3, LSN_AM_ABSOLUTE, 3, 3, LSN_I_JMP, "JMP", "Absolute"
	},
	{	// 4D
		LSN_ABSOLUTE_R( EOR, Eor_BeginInst, true )
	},
	{	// 4E
		LSN_ABSOLUTE_RMW( LSR, Lsr )
	},
	{	// 4F
		LSN_ABSOLUTE_LONG_R( EOR, Eor_BeginInst, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,												&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<1>,										&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Copy_Operand_To_Db,												&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Read_X_And_Bank_To_Operand_Low_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Write_Operand_Low_To_Y_And_DB_Phi2,
				&CRicoh5A22::MvX_Adjust_And_SetRepeat<1>,										&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::BeginInst<true, false>,
			},
		},
		7, 7, LSN_AM_BLOCK_MOVE, 3, 3, LSN_I_MVN, "MVN", "Block Move (Negative)"
	},
	{	// 55
		LSN_DIRECT_PAGE_WITH_X_R( EOR, Eor_BeginInst, true )
	},
	{	// 56
		LSN_DIRECT_PAGE_WITH_X_RMW( LSR, Lsr )
	},
	{	// 57
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( EOR, Eor_BeginInst )
	},


	/** 58-5F */
	{	// 58
		LSN_IMPLIED_2( CLI, Cli_BeginInst )
	},
	{	// 59
		LSN_ABSOLUTE_INDEXED_Y_R( EOR, Eor_BeginInst, true )
	},
	{	// 5A
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, false, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Y_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W, false, true>,											&CRicoh5A22::Push_Y_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W, false, true>,											&CRicoh5A22::Push_Y_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHY, "PHY", "Implied"
	},
	{	// 5B
		LSN_IMPLIED_2( TCD, Tcd_BeginInst )
	},
	{	// 5C
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Bank_IncPc_Phi2<true>,
				&CRicoh5A22::Jsl_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Bank_IncPc_Phi2<true>,
				&CRicoh5A22::Jsl_BeginInst
			},
		},
		4, 4, LSN_AM_ABSOLUTE_LONG, 4, 4, LSN_I_JML, "JML", "Absolute Long"
	},
	{	// 5D
		LSN_ABSOLUTE_INDEXED_X_R( EOR, Eor_BeginInst, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Rts_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Rts_BeginInst
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Per_IncPc,															&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true>,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Per_IncPc,															&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_Zero_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STZ, "STZ", "Direct (Write)"
	},
	{	// 65
		LSN_DIRECT_PAGE_R( ADC, Adc_BeginInst, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, false, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, true>,
				&CRicoh5A22::Pla_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Pla_BeginInst
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLA, "PLA", "Implied"
	},
	{	// 69
		LSN_IMMEDIATE( ADC, Adc_BeginInst<true>, true )
	},
	{	// 6A
		LSN_IMPLIED_2( ROR, RorOnA_BeginInst<false> )
	},
	{	// 6B
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Bank_Phi2<3, true>,
				&CRicoh5A22::Rtl_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<1, false, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<2, false, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Bank_Phi2<3, true>,
				&CRicoh5A22::Rtl_BeginInst
			},
		},
		6, 6, LSN_AM_IMPLIED, 1, 1, LSN_I_RTL, "RTL", "Implied"
	},
	{	// 6C
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_A, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
		},
		5, 5, LSN_AM_ABSOLUTE_INDIRECT, 3, 3, LSN_I_JMP, "JMP", "Absolute Indirect (Jump)"
	},
	{	// 6D
		LSN_ABSOLUTE_R( ADC, Adc_BeginInst, true )
	},
	{	// 6E
		LSN_ABSOLUTE_RMW( ROR, Ror )
	},
	{	// 6F
		LSN_ABSOLUTE_LONG_R( ADC, Adc_BeginInst, true )
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
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_Zero_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_STZ, "STZ", "Direct, X (Write)"
	},
	{	// 75
		LSN_DIRECT_PAGE_WITH_X_R( ADC, Adc_BeginInst, true )
	},
	{	// 76
		LSN_DIRECT_PAGE_WITH_X_RMW( ROR, Ror )
	},
	{	// 77
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( ADC, Adc_BeginInst )
	},


	/** 78-7F */
	{	// 78
		LSN_IMPLIED_2( SEI, Sei_BeginInst )
	},
	{	// 79
		LSN_ABSOLUTE_INDEXED_Y_R( ADC, Adc_BeginInst, true )
	},
	{	// 7A
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, false, false, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, true>,
				&CRicoh5A22::Ply_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Ply_BeginInst
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLY, "PLY", "Implied"
	},
	{	// 7B
		LSN_IMPLIED_2( TDC, Tdc_BeginInst )
	},
	{	// 7C
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, false, false, true, true>,	&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2<LSN_FROM_P, true, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, false, false, true, true>,	&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2<LSN_FROM_P, true, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
		},
		6, 6, LSN_AM_ABSOLUTE_INDEXED_INDIRECT, 3, 3, LSN_I_JMP, "JMP", "Absolute Indexed Indirect (a,x) (Jump)"
	},
	{	// 7D
		LSN_ABSOLUTE_INDEXED_X_R( ADC, Adc_BeginInst, true )
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Brl_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Brl_BeginInst
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
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_Y_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STY, "STY", "Direct (Write)"
	},
	{
		// 85
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_A_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STA, "STA", "Direct (Write)"
	},
	{	// 86
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_X_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		3, 3, LSN_AM_DIRECT_PAGE, 2, 2, LSN_I_STX, "STX", "Direct (Write)"
	},
	{	// 87
		LSN_DIRECT_PAGE_INDIRECT_LONG_W( STA, Sta )		
	},


	/** 88-8F */
	{	// 88
		LSN_IMPLIED_2( DEY, Dey_BeginInst )
	},
	{	// 89
		LSN_IMMEDIATE( BIT, Bit_BeginInst<true>, true )
	},
	{	// 8A
		LSN_IMPLIED_2( TXA, Txa_BeginInst )
	},
	{	// 8B
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Db_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Db_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHB, "PHB", "Implied"
	},
	{	// 8C
		LSN_ABSOLUTE_W( STY, Sty<true>, false )
	},
	{	// 8D
		LSN_ABSOLUTE_W( STA, Sta<true>, true )
	},
	{	// 8E
		LSN_ABSOLUTE_W( STX, Stx<true>, false )
	},
	{	// 8F
		LSN_ABSOLUTE_LONG_W( STA, Sta<true>, true /** Skip if M. */ )
	},


	/** 90-97 */
	{	// 90
		LSN_BRANCH( BCC, C(), 0 )
	},
	{	// 91
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_W( STA, Sta, true )
	},
	{	// 92
		LSN_DIRECT_PAGE_INDIRECT_W( STA, Sta, true )
	},
	{	// 93
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_W( STA, Sta, true )
	},
	{	// 94
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_Y_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_Y_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_STY, "STY", "Direct, X (Write)"
	},
	{	// 95
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_A_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_X_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_A_Low_To_AddrOrPtr_SkipIfM_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		4, 4, LSN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, LSN_I_STA, "STA", "Direct, X (Write)"
	},
	{	// 96
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_Y_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::WriteBank0_X_High_To_AddrOrPtr_Phi2<LSN_TO_A, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_Y_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::WriteBank0_X_Low_To_AddrOrPtr_SkipIfX_Phi2<LSN_TO_A, false, true>,
				&CRicoh5A22::BeginInst
			},
		},
		4, 4, LSN_AM_DIRECT_PAGE_INDEXED_Y, 2, 2, LSN_I_STX, "STX", "Direct, Y (Write)"
	},
	{	// 97
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_W, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A>,
				&CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false, false>, &CRicoh5A22::Write_A_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, true, true, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Write_A_High_To_AddrOrPtr_And_Bank_Phi2<LSN_TO_P, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_W, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,				&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_Low_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_AddrOrPtr_High_Phi2<LSN_TO_P, true>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_Phi2<LSN_FROM_A, true>,
				&CRicoh5A22::Add_Y_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, true, false, false>, &CRicoh5A22::Write_A_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_TO_P, false, true>,
				&CRicoh5A22::BeginInst
			}
		},
		6, 6, LSN_AM_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y, 2, 2, LSN_I_STA, "STA", "Direct Indirect Indexed Long [d],y (Write)"
	},


	/** 98-9F */
	{	// 98
		LSN_IMPLIED_2( TYA, Tya_BeginInst )
	},
	{	// 99
		LSN_ABSOLUTE_INDEXED_Y_W( STA, Sta, true )
	},
	{	// 9A
		LSN_IMPLIED_2( TXS, Txs_BeginInst )
	},
	{	// 9B
		LSN_IMPLIED_2( TXY, Txy_BeginInst )
	},
	{	// 9C
		LSN_ABSOLUTE_W( STZ, Stz<true>, true )
	},
	{	// 9D
		LSN_ABSOLUTE_INDEXED_X_W( STA, Sta, true )
	},
	{	// 9E
		LSN_ABSOLUTE_INDEXED_X_W( STZ, Stz, true )
	},
	{	// 9F
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false, false>, &CRicoh5A22::Write_A_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, true, true, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Write_A_High_To_AddrOrPtr_And_Bank_Phi2<LSN_FROM_P, true>,
				&CRicoh5A22::BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Bank_IncPc_Phi2,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, true, true, false, false>, &CRicoh5A22::Write_A_Low_To_AddrOrPtr_And_Bank_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, true>,
				&CRicoh5A22::BeginInst
			}
		}, 5, 5, LSN_AM_ABSOLUTE_LONG_X, 4, 4, LSN_I_STA, "STA", "Absolute Long, X (Write)"
	},


	/** A0-A7 */
	{	// A0
		LSN_IMMEDIATE( LDY, Ldy_BeginInst<true>, false )
	},
	{	// A1
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( LDA, Lda_BeginInst )
	},
	{	// A2
		LSN_IMMEDIATE( LDX, Ldx_BeginInst<true>, false )
	},
	{	// A3
		LSN_STACK_RELATIVE_R( LDA, Lda_BeginInst )
	},
	{	// A4
		LSN_DIRECT_PAGE_R( LDY, Ldy_BeginInst, false )
	},
	{	// A5
		LSN_DIRECT_PAGE_R( LDA, Lda_BeginInst, true )
	},
	{	// A6
		LSN_DIRECT_PAGE_R( LDX, Ldx_BeginInst, false )
	},
	{	// A7
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( LDA, Lda_BeginInst )
	},


	/** A8-AF */
	{	// A8
		LSN_IMPLIED_2( TAY, Tay_BeginInst )
	},
	{	// A9
		LSN_IMMEDIATE( LDA, Lda_BeginInst<true>, true )
	},
	{	// AA
		LSN_IMPLIED_2( TAX, Tax_BeginInst )
	},
	{	// AB
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2< false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Bank_Phi2<0, true>,
				&CRicoh5A22::Plb_BeginInst,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2< false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,											&CRicoh5A22::Read_Stack_To_Bank_Phi2<0, true>,
				&CRicoh5A22::Plb_BeginInst,
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLB, "PLB", "Implied"
	},
	{	// AC
		LSN_ABSOLUTE_R( LDY, Ldy_BeginInst, false )
	},
	{	// AD
		LSN_ABSOLUTE_R( LDA, Lda_BeginInst, true )
	},
	{	// AE
		LSN_ABSOLUTE_R( LDX, Ldx_BeginInst, false )
	},
	{	// AF
		LSN_ABSOLUTE_LONG_R( LDA, Lda_BeginInst, true )
	},


	/** B0-B7 */
	{	// B0
		LSN_BRANCH( BCS, C(), 1 )
	},
	{	// B1
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( LDA, Lda_BeginInst )
	},
	{	// B2
		LSN_DIRECT_PAGE_INDIRECT_R( LDA, Lda_BeginInst )
	},
	{	// B3
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( LDA, Lda_BeginInst )
	},
	{	// B4
		LSN_DIRECT_PAGE_WITH_X_R( LDY, Ldy_BeginInst, false )
	},
	{	// B5
		LSN_DIRECT_PAGE_WITH_X_R( LDA, Lda_BeginInst, true )
	},
	{	// B6
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_Y_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true, true>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_A, true>,
				&CRicoh5A22::Ldx_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<false>,
				&CRicoh5A22::Null<LSN_N, true>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_Y_D_Operator_To_AddrOrPtr_IncPc_SkipOnDl<LSN_TO_A, false, true>, &CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, true>,
				&CRicoh5A22::Ldx_BeginInst
			},
		},
		4, 4, LSN_AM_DIRECT_PAGE_INDEXED_Y, 2, 2, LSN_I_LDX, "LDX", "Direct, Y (Read)"
	},
	{	// B7
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( LDA, Lda_BeginInst )
	},


	/** B8-BF */
	{	// B8
		LSN_IMPLIED_2( CLV, Clv_BeginInst )
	},
	{	// B9
		LSN_ABSOLUTE_INDEXED_Y_R( LDA, Lda_BeginInst, true )
	},
	{	// BA
		LSN_IMPLIED_2( TSX, Tsx_BeginInst )
	},
	{	// BB
		LSN_IMPLIED_2( TYX, Tyx_BeginInst )
	},
	{	// BC
		LSN_ABSOLUTE_INDEXED_X_R( LDY, Ldy_BeginInst, false )
	},
	{	// BD
		LSN_ABSOLUTE_INDEXED_X_R( LDA, Lda_BeginInst, true )
	},
	{	// BE
		LSN_ABSOLUTE_INDEXED_Y_R( LDX, Ldx_BeginInst, false )
	},
	{	// BF
		LSN_ABSOLUTE_LONG_X_R( LDA, Lda_BeginInst )
	},


	/** C0-C7 */
	{	// C0
		LSN_IMMEDIATE( CPY, Cpy_BeginInst<true>, false )
	},
	{	// C1
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( CMP, Cmp_BeginInst )
	},
	{	// C2
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Rep_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false, false>,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Rep_BeginInst
			}
		},
		3, 3, LSN_AM_IMMEDIATE, 2, 2, LSN_I_REP, "REP", "Immediate"
	},
	{	// C3
		LSN_STACK_RELATIVE_R( CMP, Cmp_BeginInst )
	},
	{	// C4
		LSN_DIRECT_PAGE_R( CPY, Cpy_BeginInst, false )
	},
	{	// C5
		LSN_DIRECT_PAGE_R( CMP, Cmp_BeginInst, true )
	},
	{	// C6
		LSN_DIRECT_PAGE_RMW( DEC, Dec )
	},
	{	// C7
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( CMP, Cmp_BeginInst )
	},


	/** C8-CF */
	{	// C8
		LSN_IMPLIED_2( INY, Iny_BeginInst )
	},
	{	// C9
		LSN_IMMEDIATE( CMP, Cmp_BeginInst<true>, true )
	},
	{	// CA
		LSN_IMPLIED_2( DEX, Dex_BeginInst )
	},
	{	// CB
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_Discard_Phi2<false>,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null,																&CRicoh5A22::Wai_Phi2,
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_Operand_Discard_Phi2<false>,
				&CRicoh5A22::Null<LSN_N>,														&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null,																&CRicoh5A22::Wai_Phi2,
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_WAI, "WAI", "Implied"
	},
	{	// CC
		LSN_ABSOLUTE_R( CPY, Cpy_BeginInst, false )
	},
	{	// CD
		LSN_ABSOLUTE_R( CMP, Cmp_BeginInst, true )
	},
	{	// CE
		LSN_ABSOLUTE_RMW( DEC, Dec )
	},
	{	// CF
		LSN_ABSOLUTE_LONG_R( CMP, Cmp_BeginInst, true )
	},


	/** D0-D7 */
	{	// D0
		LSN_BRANCH( BNE, Z(), 0 )
	},
	{	// D1
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( CMP, Cmp_BeginInst )
	},
	{	// D2
		LSN_DIRECT_PAGE_INDIRECT_R( CMP, Cmp_BeginInst )
	},
	{	// D3
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( CMP, Cmp_BeginInst )
	},
	{	// D4
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, false, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_LowByteWrap_Phi2<LSN_FROM_A, false>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipOnDl_Phi2<true>,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Add_D_And_Operand_To_AddrOrPtr_IncPc<LSN_TO_A, true>,			&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_A, false, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_LowByteWrap_Phi2<LSN_FROM_A, false>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		6, 6, LSN_AM_DIRECT_PAGE_INDIRECT, 2, 2, LSN_I_PEI, "PEI", "Direct Page Indirect"
	},
	{	// D5
		LSN_DIRECT_PAGE_WITH_X_R( CMP, Cmp_BeginInst, true )
	},
	{	// D6
		LSN_DIRECT_PAGE_WITH_X_RMW( DEC, Dec )
	},
	{	// D7
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( CMP, Cmp_BeginInst )
	},


	/** D8-DF */
	{	// D8
		LSN_IMPLIED_2( CLD, Cld_BeginInst )
		//{
		//	{
		//		/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
		//		&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
		//		&CRicoh5A22::Cld_BeginInst
		//	},
		//	{
		//		/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
		//		&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
		//		&CRicoh5A22::Cld_BeginInst
		//	},
		//},
		//2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_CLD, "CLD", "Implied"
	},
	{	// D9
		LSN_ABSOLUTE_INDEXED_Y_R( CMP, Cmp_BeginInst, true )
	},
	{	// DA
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2<false, INT8_MIN, false, true>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_X_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W, false, true>,										&CRicoh5A22::Push_X_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_W, false, true>,										&CRicoh5A22::Push_X_Low_Phi2<0, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_PHX, "PHX", "Implied"
	},
	{	// DB
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Stp_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Stp_BeginInst
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_STP, "STP", "Implied"
	},
	{	// DC
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_LowByteWrap_Phi2<LSN_FROM_P, true>,
				&CRicoh5A22::Jml_Absolute_Indirect_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_Low_SkipIfM_SkipIfX_Phi2<LSN_FROM_P, false, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_Operand_High_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::ReadBank0_PtrOrAddr_To_Bank_LowByteWrap_Phi2<LSN_FROM_P, true>,
				&CRicoh5A22::Jml_Absolute_Indirect_BeginInst,
			},
		},
		6, 6, LSN_AM_ABSOLUTE_INDIRECT_LONG, 3, 3, LSN_I_JML, "JML", "Absolute Indirect Long (Jump)"
	},
	{	// DD
		LSN_ABSOLUTE_INDEXED_X_R( CMP, Cmp_BeginInst, true )
	},
	{	// DE
		LSN_ABSOLUTE_INDEXED_X_RMW( DEC, Dec )
	},
	{	// DF
		LSN_ABSOLUTE_LONG_X_R( CMP, Cmp_BeginInst )
	},


	/** E0-E7 */
	{	// E0
		LSN_IMMEDIATE( CPX, Cpx_BeginInst<true>, false )
	},
	{	// E1
		LSN_DIRECT_PAGE_INDEXED_INDIRECT_X_R( SBC, Sbc_BeginInst<false> )
	},
	{	// E2
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false, false>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Sep_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Sep_BeginInst,
			},
		},
		3, 3, LSN_AM_IMMEDIATE, 2, 2, LSN_I_SEP, "SEP", "Immediate"
	},
	{	// E3
		LSN_STACK_RELATIVE_R( SBC, Sbc_BeginInst<false> )
	},
	{	// E4
		LSN_DIRECT_PAGE_R( CPX, Cpx_BeginInst, false )
	},
	{	// E5
		LSN_DIRECT_PAGE_R( SBC, Sbc_BeginInst<false>, true )
	},
	{	// E6
		LSN_DIRECT_PAGE_RMW( INC, Inc )
	},
	{	// E7
		LSN_DIRECT_PAGE_INDIRECT_LONG_R( SBC, Sbc_BeginInst<false> )
	},


	/** E8-EF */
	{	// E8
		LSN_IMPLIED_2( INX, Inx_BeginInst )
	},
	{	// E9
		LSN_IMMEDIATE( SBC, Sbc_BeginInst<true>, true )
	},
	{	// EA
		LSN_IMPLIED_2( NOP, Nop_BeginInst )
	},
	{	// EB
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Xba_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_N, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, INT8_MIN, true>,
				&CRicoh5A22::Xba_BeginInst
			},
		},
		3, 3, LSN_AM_IMPLIED, 1, 1, LSN_I_XBA, "XBA", "Implied"
	},
	{	// EC
		LSN_ABSOLUTE_R( CPX, Cpx_BeginInst, false )
	},
	{	// ED
		LSN_ABSOLUTE_R( SBC, Sbc_BeginInst<false>, true )
	},
	{	// EE
		LSN_ABSOLUTE_RMW( INC, Inc )
	},
	{	// EF
		LSN_ABSOLUTE_LONG_R( SBC, Sbc_BeginInst<false>, true )
	},


	/** F0-F7 */
	{	// F0
		LSN_BRANCH( BEQ, Z(), 1 )
	},
	{	// F1
		LSN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( SBC, Sbc_BeginInst<false> )
	},
	{	// F2
		LSN_DIRECT_PAGE_INDIRECT_R( SBC, Sbc_BeginInst<false> )
	},
	{	// F3
		LSN_STACK_RELATIVE_INDIRECT_INDEXED_Y_R( SBC, Sbc_BeginInst<false> )
	},
	{	// F4
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Null<LSN_W, true>,												&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_IncPc_SkipIfM_SkipIfX_Phi2<false, false>,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_High_IncPc<false>,
				&CRicoh5A22::Null<LSN_W, true>,												&CRicoh5A22::Push_Operand_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,													&CRicoh5A22::Push_Operand_Low_Phi2<-1, true>,
				&CRicoh5A22::BeginInst<false, true, true>
			},
		},
		5, 5, LSN_AM_ABSOLUTE, 3, 3, LSN_I_PEA, "PEA", "Absolute (Push)"
	},
	{	// F5
		LSN_DIRECT_PAGE_WITH_X_R( SBC, Sbc_BeginInst<false>, true )
	},
	{	// F6
		LSN_DIRECT_PAGE_WITH_X_RMW( INC, Inc )
	},
	{	// F7
		LSN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( SBC, Sbc_BeginInst<false> )
	},


	/** F8-FF */
	{	// F8
		//LSN_IMPLIED_2( NOP, Nop_BeginInst )
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Sed_BeginInst
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Fetch_Operand_Discard_Phi2<true>,
				&CRicoh5A22::Sed_BeginInst
			},
		},
		2, 2, LSN_AM_IMPLIED, 1, 1, LSN_I_SED, "SED", "Implied"
	},
	{	// F9
		LSN_ABSOLUTE_INDEXED_Y_R( SBC, Sbc_BeginInst<false>, true )
	},
	{	// FA
		{
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, false, false, true>,
				&CRicoh5A22::Null<LSN_R>,													&CRicoh5A22::Read_Stack_To_Operand_High_Phi2<1, true>,
				&CRicoh5A22::Plx_BeginInst,
			},
			{
				/* BeginInst() */															&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,												&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_N>,													&CRicoh5A22::Null_Phi2<false, 1>,
				&CRicoh5A22::Null<LSN_R, false, true>,										&CRicoh5A22::Read_Stack_To_Operand_Low_SkipIfM_SkipIfX_Phi2<0, true, true>,
				&CRicoh5A22::Plx_BeginInst,
			},
		},
		4, 4, LSN_AM_IMPLIED, 1, 1, LSN_I_PLX, "PLX", "Implied"
	},
	{	// FB
		LSN_IMPLIED_2( XCE, Xce_BeginInst )
	},
	{	// FC
		{
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_W, true>,													&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Pc_Low_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R, false, true>,																																		
																								&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, false, false, true, true>,	&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2<LSN_FROM_P, true, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
			{
				/* BeginInst() */																&CRicoh5A22::Fetch_Opcode_IncPc_Phi2,
				&CRicoh5A22::Null<LSN_R, true>,													&CRicoh5A22::Fetch_PtrOrAddr_Low_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Null<LSN_W, true>,													&CRicoh5A22::Push_Pc_High_Phi2<0>,
				&CRicoh5A22::Null<LSN_W>,														&CRicoh5A22::Push_Pc_Low_Phi2<-1>,
				&CRicoh5A22::Null<LSN_R, false, true>,															
																								&CRicoh5A22::Fetch_PtrOrAddr_High_IncPc_Phi2<LSN_TO_P>,
				&CRicoh5A22::Add_X_PtrOrAddr_BankOverflow_PageSkip<LSN_TO_P, false, false, false, true, true>,	&CRicoh5A22::Null_Phi2,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_Low_SkipIfM_Phi2<LSN_FROM_P, false>,
				&CRicoh5A22::Null<LSN_R>,														&CRicoh5A22::Read_PtrOrAddr_And_Bank_To_AddrOrPtr_High_Phi2<LSN_FROM_P, true, true>,
				&CRicoh5A22::Jmp_Absolute_BeginInst
			},
		},
		8, 8, LSN_AM_ABSOLUTE_INDEXED_INDIRECT, 3, 3, LSN_I_JSR, "JSR", "Absolute Indexed Indirect (a,x) (Jump)"
	},
	{	// FD
		LSN_ABSOLUTE_INDEXED_X_R( SBC, Sbc_BeginInst<false>, true )
	},
	{	// FE
		LSN_ABSOLUTE_INDEXED_X_RMW( INC, Inc )
	},
	{	// FF
		LSN_ABSOLUTE_LONG_X_R( SBC, Sbc_BeginInst<false> )
	},
};
