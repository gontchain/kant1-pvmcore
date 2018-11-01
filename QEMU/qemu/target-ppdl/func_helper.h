DEF_HELPER_FLAGS_1(MakeCall, 0, i64, env)
DEF_HELPER_FLAGS_1(GetInputData, 0, i64, env)
DEF_HELPER_FLAGS_2(SaveToStorageStub, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(CallDataCopy, 0, i64, env)
DEF_HELPER_FLAGS_1(MakeCallCode, 0, i64, env)
DEF_HELPER_FLAGS_1(DelegateCall, 0, i64, env)
DEF_HELPER_FLAGS_1(GetElfSizeStub, 0, i64, env)
DEF_HELPER_FLAGS_1(Pop, 0, i64, env)
DEF_HELPER_FLAGS_1(MSizeOp, 0, i64, env)
DEF_HELPER_FLAGS_2(DupOp, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(GetDifficulty, 0, i64, env)
DEF_HELPER_FLAGS_1(Return, 0, i64, env)
DEF_HELPER_FLAGS_2(ArithmStub, 0, i64, env, i64)
DEF_HELPER_FLAGS_2(MloadInst, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(GetOrigin, 0, i64, env)
DEF_HELPER_FLAGS_1(GetGasPrice, 0, i64, env)
DEF_HELPER_FLAGS_1(CallValue, 0, i64, env)
DEF_HELPER_FLAGS_1(GetGasLimit, 0, i64, env)
DEF_HELPER_FLAGS_2(PushInst, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(KeccakAlgStub, 0, i64, env)
DEF_HELPER_FLAGS_1(ExtCodeCopy, 0, i64, env)
DEF_HELPER_FLAGS_1(GetTimeStamp, 0, i64, env)
DEF_HELPER_FLAGS_1(CodeCopy, 0, i64, env)
DEF_HELPER_FLAGS_1(BlockChainHash, 0, i64, env)
DEF_HELPER_FLAGS_1(GetSingleBlockFromStack, 0, i64, env)
DEF_HELPER_FLAGS_2(SwapOp, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(CreateAccount, 0, i64, env)
DEF_HELPER_FLAGS_2(CompareStub, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(GetNumber, 0, i64, env)
DEF_HELPER_FLAGS_1(GetBalance, 0, i64, env)
DEF_HELPER_FLAGS_1(GetAddress, 0, i64, env)
DEF_HELPER_FLAGS_1(PcOp, 0, i64, env)
DEF_HELPER_FLAGS_3(LogInst, 0, i64, env, i64, i64)
DEF_HELPER_FLAGS_2(LoadFromStorageStub, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(ExtCodeSize, 0, i64, env)
DEF_HELPER_FLAGS_1(GetCodeSize, 0, i64, env)
DEF_HELPER_FLAGS_2(PushSingleBlockToStack, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(CallDataSize, 0, i64, env)
DEF_HELPER_FLAGS_1(GetCaller, 0, i64, env)
DEF_HELPER_FLAGS_2(USEGAS, 0, i64, env, i64)
DEF_HELPER_FLAGS_1(StopExec, 0, i64, env)
DEF_HELPER_FLAGS_1(GetCoinBase, 0, i64, env)
DEF_HELPER_FLAGS_2(MStoreInst, 0, i64, env, i64)DEF_HELPER_FLAGS_2(input_data_get, 0, i64, env, i64)
DEF_HELPER_FLAGS_3(input_data_set, 0, void, env, i64, i64)
DEF_HELPER_FLAGS_2(log_bus_get, 0, i64, env, i64)
DEF_HELPER_FLAGS_3(log_bus_set, 0, void, env, i64, i64)
DEF_HELPER_FLAGS_2(data_bus_get, 0, i64, env, i64)
DEF_HELPER_FLAGS_3(data_bus_set, 0, void, env, i64, i64)
DEF_HELPER_FLAGS_2(gas_available_get, 0, i64, env, i64)
DEF_HELPER_FLAGS_3(gas_available_set, 0, void, env, i64, i64)
DEF_HELPER_FLAGS_2(stack_arr_get, 0, i64, env, i64)
DEF_HELPER_FLAGS_3(stack_arr_set, 0, void, env, i64, i64)