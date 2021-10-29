#include "../GeneralInclude/Processor.h"

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

//-------- Assembler variables --------

enum Assembler_errors
{
    CANT_OPEN_FILE = 1,
};

const int MAX_SIZE_OF_CODE = 300;

//-------- Assembler functions ---------

size_t Assembler (Text* input, data_t* code);

int MakeBinaryFile (data_t* code, int size_of_code);