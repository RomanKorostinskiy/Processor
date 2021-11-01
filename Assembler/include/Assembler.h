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

const size_t CMD_SIZE = 4;

enum Assembler_errors
{
    CANT_OPEN_FILE      = 1,
    WRONG_WRITE_TO_FILE = 2,
    PUSH_ARGS_ERROR     = 3,
    WRONG_REGISTER      = 4,
    SYNTAX_ERROR        = 5,
};

const int MAX_SIZE_OF_CODE = 1000; //TODO придумать как считать размер кода

//--------- Onegin functions ---------

int ReadFromFile (Text *text);

size_t GetSizeOfFile (FILE* fp);

void WriteToFile (Text *text, FILE *fp);

FILE* OpenFileWrite (Text* text);

void CloseFile (FILE *fp);

void MakeString (Text *text);

size_t DeleteSpaces (char *array);

void MemoryFree (Text *text);

int AlphabetOrderCMP (const void *arg1, const void *arg2);

void AlphabetOrderSort(Text *text);

int RhymeCMP (const void *arg1, const void *arg2);

void RhymeSort (Text *text);

int OriginalCMP (const void *arg1, const void *arg2);

void OriginalSort (Text *text);

int GetFileNames (Text *text, int argc, char* argv[]);

//-------- Assembler functions ---------

char SwitchReg (char reg);

size_t Assembler (Text* input, void* code);

int MakeBinaryFile (void* code, int sizeof_code, const char* file_name);