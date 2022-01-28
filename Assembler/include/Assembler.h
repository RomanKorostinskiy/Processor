#pragma once

#include "../GeneralInclude/General.h"


//-------- Onegin variables --------

enum File_errors
{
    WRONG_INPUT_FILE = 1,
};

typedef struct String_t
{
    int len = 0;
    char *ptr = nullptr;
}String;

typedef struct Text_t
{
    char *input_file_name = nullptr;
    char *output_file_name = nullptr;
    char *buffer = nullptr;
    size_t num_of_strings = 0;
    String *strings = nullptr;
} Text;

//-------- Assembler variables --------

const size_t CMD_SIZE = 5;

const size_t TAG_SIZE = 50;

typedef struct Tags
{
    size_t adr = 0;
    char* name = nullptr;
}Tags;

const int SIZE_OF_TAG_TABLE = 300;

enum ScanCases
{
    CONS_REG_ADR = 1,
    CONS_REG     = 2,
    REG_ADR      = 3,
    REG          = 4,
    CONS_ADR     = 5,
    CONS         = 6,
    JMP          = 7,
    TAG          = 8,
    NO_ARGS      = 0,
};

enum Assembler_errors
{
    CANT_OPEN_FILE      = 1,
    WRONG_WRITE_TO_FILE = 2,
    PUSH_ARGS_ERROR     = 3,
    POP_ARGS_ERROR      = 4,
    CALL_ARGS_ERROR     = 5,
    WRONG_REGISTER      = -1,
    SYNTAX_ERROR        = -2,
};

const int MAX_SIZE_OF_CODE = 4096; //TODO придумать как считать размер кода

//--------- Onegin functions ---------

int ReadFromFile (Text *text);

size_t GetSizeOfFile (FILE* fp);

void WriteToFile (Text *text, FILE *fp);

FILE* OpenFileWrite (Text* text);

void CloseFile (FILE *fp);

void MakeString (Text *text);

size_t DeleteSpaces (char *array);

void MemoryFree (Text *text);

int GetFileNames (Text *text, int argc, char* argv[]);

//-------- Assembler functions ---------

size_t Assembler (Text* input, void* code);

int ScanCommand(char* string, char* command, char* tag_name, data_t* cons, char* reg);

int PushCase (void* code, int* num_of_commands, int scan_case, data_t cons, char reg);

int PopCase (void* code, int* num_of_commands, int scan_case, data_t cons, char reg);

int NoArgsCommands (void* code, int* num_of_commands, char* command);

int JumpCommand (void* code, int* num_of_commands, char* command);

int MakeBinaryFile (void* code, size_t sizeof_code, const char* file_name);