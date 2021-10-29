#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>

//-------- Stack variables ---------

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
	CANT_OPEN_FILE = 1,
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

//-------- Assembler variables --------

typedef int data_t;

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

const int MAX_SIZE_OF_CODE = 300;

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

//-------- Asembler functions ---------

size_t Assembler (Text* input, data_t* code);

int MakeBinaryFile (data_t* code, int size_of_code);
