/*
 * PPDL helper routines
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

/* systemc */
DEF_HELPER_FLAGS_1(next_context, 0, void, i64)
DEF_HELPER_FLAGS_1(wait_for_gdb, 0, void, i64)

/* gdb */
DEF_HELPER_FLAGS_1(gdb_handling, 0, void, env)

/* tracer */
DEF_HELPER_FLAGS_2(tracer, 0, void, env, i32)

/* exception */
DEF_HELPER_FLAGS_2(exception, 0, void, env, i32)

/* debug */
DEF_HELPER_FLAGS_1(print_value, 0, void, i64)
DEF_HELPER_FLAGS_1(print, 0, void, env)
DEF_HELPER_FLAGS_0(debug, 0, void)

/* messages */
DEF_HELPER_FLAGS_3(error_message, 0, void, env, i64, i64)

/* sign64 */
DEF_HELPER_FLAGS_1(sign64, 0, s64, i64)

/* memory */
DEF_HELPER_FLAGS_2(mem_ld64, 0, i64, env, i64)
DEF_HELPER_FLAGS_2(mem_ld32, 0, i64, env, i64)
DEF_HELPER_FLAGS_3(mem_st64, 0, void, env, i64, i64)
DEF_HELPER_FLAGS_3(mem_st32, 0, void, env, i64, i64)

/* bitfield */
DEF_HELPER_FLAGS_4(set_bitfield, 0, i64, i64, i64, i64, i64)
DEF_HELPER_FLAGS_3(get_bitfield, 0, i64, i64, i64, i64)

#include "arglist_helper.h" // автоматически сгенерированное определение helper'ов для ARGLIST'ов

#include "func_helper.h" // автоматически сгенерированное определение helper'ов для FUNCTIONS
