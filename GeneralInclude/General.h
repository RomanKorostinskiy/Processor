#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>

#define FLOAT_DATA

#ifdef FLOAT_DATA
typedef double data_t;
#endif

#ifdef INT_DATA
typedef int data_t;
#endif

enum Commands
{
	CMD_HLT	 = 0,
	CMD_PUSH = 1,
	CMD_POP  = 2,
	CMD_ADD  = 3,
	CMD_SUB  = 4,
	CMD_MUL  = 5,
	CMD_DIV  = 6,
    CMD_SQRT = 7,
	CMD_OUT  = 8,
    CMD_IN   = 9,
    CMD_JMP  = 10,
    CMD_JA   = 11,
    CMD_JAE  = 12,
    CMD_JB   = 13,
    CMD_JBE  = 14,
    CMD_JE   = 15,
    CMD_JNE  = 16,
    CMD_CALL = 17,
    CMD_RET  = 18,

};

enum Arguments
{
    ARG_CONS  = 32,
    ARG_REG   = 64,
    ARG_RAM   = 128,
    ARGS_NO   = 0,
};

const size_t RAM_SIZE = 1024;