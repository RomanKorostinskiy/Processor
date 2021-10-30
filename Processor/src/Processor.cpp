#include "../include/Processor.h"

int main(int argc, char* argv[])
{
	Stack stack = {};

	data_t* code = nullptr;
    char* code_file_name = nullptr;
    size_t sizeof_code = 0;

    if (GetFileNames(&code_file_name, argc, argv) == 1)
    {
        printf("Error: wrong name of file(s)");
        return 1;
    }

    sizeof_code = GetCode (&code, code_file_name);

    for (int i = 0; code[i] != 0; i++)
    {
        printf("\n%d", code[i]);
    }

    printf("\nsizeof code = %ld", sizeof_code);

//    Processor (code);
    free (code);

	return 0;
}
