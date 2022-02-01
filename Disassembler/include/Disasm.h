#pragma once

#include "../GeneralInclude/Proc_General.h"

typedef struct Disasm
{
    void*  code             = nullptr;
    char*  code_file_name   = nullptr;
    char*  disasm_file_name = nullptr;

    size_t sizeof_code   = 0;
    size_t ip             = 0; //instruction pointer
}Disasm;

enum Disasm_errors
{
    CANT_OPEN_FILE            = 1,
    WRONG_WRITE_TO_FILE       = 2,
    CANT_READ_FROM_FILE       = 3,
    DISASSEMBLER_DEFAULT_CASE = 4,
    WRONG_DATA                = 5,
};

int GetFileNames (Disasm* disasm, int argc, char* argv[]);

int GetCode (Disasm* disasm);

size_t GetSizeOfFile (FILE* fp);

int Disassembler (Disasm* disasm);

int PrintPush (Disasm* disasm, FILE* fp, int type);

int PrintPop (Disasm* disasm, FILE* fp, int type);

int PrintNoArgsCommands (Disasm* disasm, FILE* fp, int cmd);

int PrintJumpCommands (Disasm* disasm, FILE* fp, int cmd);

