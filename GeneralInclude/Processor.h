#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>

#define INT_DATA

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
	CMD_OUT  = 7,
};
