#include "../include/Processor.h"

int main(int argc, char* argv[])
{
	Processor_t processor = {};
    StackCtor(&processor.stack);

    char* code_file_name = nullptr;

    if (GetFileNames(&code_file_name, argc, argv) == 1)
    {
        printf("Error: wrong name of file(s)");
        return 1;
    }

    processor.sizeof_code = GetCode (&processor.code, code_file_name);

    for (int i = 0; i < processor.sizeof_code; i++)
    {
        printf("\n%d", processor.code[i]);
    }

    printf("\nsizeof code = %ld\n", processor.sizeof_code);

    Processor (&processor);

    StackDtor(&processor.stack);
    free (processor.code);


	return 0;
}
