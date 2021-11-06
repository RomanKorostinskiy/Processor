#include "../include/Disasm.h"

int main(int argc, char* argv[])
{
    Disasm disasm = {};

    if (GetFileNames(&disasm, argc, argv) == 1)
    {
        printf("Error: wrong name of file(s)");
        return 1;
    }

    GetCode(&disasm);

    Disassembler(&disasm);

    free(disasm.code);
    return 0;
}