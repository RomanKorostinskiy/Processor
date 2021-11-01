#pragma once

#include "../GeneralInclude/General.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>

//--------- Stack variables ---------

enum Stack_errors
{
    STK_IS_NULL_PTR  = 1,
    DATA_IS_NULL_PTR = 2,
    STK_DESTROYED    = 4,
    STK_OVERFL       = 8,
    STK_UNDERFL      = 16,
    STK_DOUBLE_CTED  = 32,
    STRCT_CANARY_BAD = 64,
    DATA_CANARY_BAD  = 128,
    HASH_BAD         = 256,
};

#define INT_DATA

#ifdef FLOAT_DATA
typedef double data_t;
#endif

#ifdef INT_DATA
typedef int data_t;
#endif

typedef size_t canary_t;
typedef size_t hash_t;


extern const int     START_CAPACITY;
extern const int     CAPACITY_STEP;
extern const size_t  CANARY_CONSTANT;
extern const data_t* UNAVAILABLE_ADR;

typedef struct Stack_t
{
    canary_t canary_left = 0;

    int      capacity = 0;
    data_t*  data = nullptr;
    int      size = 0;

    hash_t   hash = 0;

    canary_t canary_right = 0;
} Stack;

//--------- Processor variables ---------

typedef struct Processor_t
{
    Stack stack = {};

    data_t REGS[4] = {0};

//    data_t RAM[RAM_SIZE] = {0};

    void* code = nullptr;
    int ip = 0;
    size_t sizeof_code = 0;
}Processor_t;

enum Processor_errors
{
    CANT_OPEN_FILE         = 1,
    WRONG_WRITE_TO_FILE    = 2,
    CANT_READ_FROM_FILE    = 3,
    PROCESSOR_DEFAULT_CASE = 4,
    WRONG_DATA             = 5,
};


//--------- Stack defines --------------

#define STACK_CTOR_CHECK()                              \
do                                                      \
{                                                       \
    errors = 0;                                         \
                                                        \
    StackCtorCheck(stack);                              \
                                                        \
    StackDump(stack, __FILE__, __FUNCTION__);           \
                                                        \
    if (errors != 0)                                    \
    {                                                   \
        return 1;                                       \
    }                                                   \
} while (0)


#define STACK_ERROR_CHECK()                             \
do                                                      \
{                                                       \
    errors = 0;                                         \
                                                        \
	StackErrorCheck(stack);	                            \
                                                        \
    StackDump(stack, __FILE__, __FUNCTION__);           \
                                                        \
    if (errors != 0)                                    \
    {                                                   \
        return 1;                                       \
    }                                                   \
} while (0)

#define STACK_RESIZE_ERROR_CHECK()                      \
do                                                      \
{                                                       \
    errors = 0;                                         \
                                                        \
	StackErrorCheck(stack);	                            \
                                                        \
    StackDump(stack, __FILE__, __FUNCTION__);           \
                                                        \
    if (errors != 0)                                    \
    {                                                   \
        return nullptr;	                                \
    }                                                   \
} while (0)


#define STACK_POP_ERROR_CHECK()                         \
do                                                      \
{                                                       \
    errors = 0;                                         \
                                                        \
	StackErrorCheck(stack);				                \
                                                        \
    if (stack->size <= 0)                               \
    {                                                   \
        errors |= STK_UNDERFL;                          \
    }                                                   \
                                                        \
    StackDump(stack, __FILE__, __FUNCTION__);           \
                                                        \
    if (errors != 0)                                    \
    {                                                   \
		return (data_t) 0xBEDABEDA;	                    \
    }                                                   \
} while (0)

#define STACK_DTOR_ERROR_CHECK()                        \
do                                                      \
{                                                       \
    errors = 0;                                         \
                                                        \
	StackDtorCheck(stack);	                            \
                                                        \
    StackDump(stack, __FILE__, __FUNCTION__);           \
                                                        \
    if (errors != 0)                                    \
    {                                                   \
        return 1;	                                    \
    }                                                   \
} while (0)

//--------- Stack functions ---------

int StackCtor (Stack* stack, int capacity = START_CAPACITY);

int StackDtor (Stack* stack);

int StackPush (Stack* stack, data_t value);

data_t StackPop (Stack* stack);

data_t* StackResize (Stack* stack);

size_t StackHash (Stack* stack);

int StackErrorCheck (Stack* stack);

int StackCtorCheck(Stack* stack);

int StackDtorCheck (Stack* stack);

void StackDump (Stack* stack, const char* current_file, const char* current_function);

int StackTestInt (Stack* stack);

int StackTestFloat (Stack* stack);

//--------- Processor functions ---------

int GetFileNames (char** file_name, int argc, char* argv[]);

size_t GetSizeOfFile (FILE* fp);

int GetCode (Processor_t* processor, const char* file_name);

int Processor (Processor_t* processor);