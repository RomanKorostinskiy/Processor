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

    GetCode (&processor, code_file_name);

//    for (int i = 0; i < processor.sizeof_code; i++) //Тестовые распечатки
//    {
//        printf("\n%x", *((char*)processor.code + i));
//    }
//
//    printf("\nsizeof code = %ld\n", processor.sizeof_code);

    Processor (&processor);

    StackDtor(&processor.stack);
    free (processor.code);


	return 0;
}
