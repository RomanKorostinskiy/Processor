#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>

// #define DEBUG //#ifndef #endif

//-------- Stack variables ---------

enum Stack_errors
{
	STK_IS_NULL_PTR  = 1,
	STK_OVERFL       = 2,
	STK_UNDERFL      = 3,
	STK_DESTROYED    = 4,
	DATA_IS_NULL_PTR = 5,
};

typedef int data_t;

extern const int *UNAVAILABLE_ADR;
extern const int START_CAPACITY;

typedef struct Stack_t
{
	int capacity = 0;
	data_t* data = nullptr;
	int size = 0;
} Stack;

//-------- Text variables ---------

enum File_errors
{
	WRONG_INPUT_FILE = 6,
};

typedef struct String_t
{
	int len = 0;
	char *ptr = nullptr;
}String;

typedef struct Text_t
{
	char *input_file_name = nullptr;
	size_t size_of_input_file = 0;
	char *buffer = nullptr;
	size_t num_of_strings = 0;
	String *strings = nullptr;
} Text;

//-------- Stack functions ---------

int StackCtor (Stack* stack, int capacity = START_CAPACITY);

int StackDtor (Stack* stack);

int StackPush (Stack* stack, int value);

int StackPop (Stack* stack);

data_t* StackResize (Stack* stack);

int StackTest__ (Stack* stack);

int StackError (Stack* stack);

//-------- Text functions ---------

int ReadFromFile (Text *text);

size_t GetSizeOfFile (FILE* fp);

void WriteToFile (Text *text, FILE *fp);

FILE* OpenFileWrite ();

void CloseFile (FILE *fp);

void MakeString (Text *text);

size_t DeleteSpaces (char *array);

void MemoryFree (Text *text);
