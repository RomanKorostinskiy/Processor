#include "../include/Assembler.h"

int main(int argc, char* argv[])
{
	Text input_text = {};

    if (GetFileNames(&input_text, argc, argv) == 1)
        return 1;

	void* code = nullptr;

	code = (void*) calloc(MAX_SIZE_OF_CODE, sizeof(char));

	ReadFromFile(&input_text);

	MakeString(&input_text);

//    WriteToFile(&input_text, OpenFileWrite(&input_text)); //Для проверки функций из Онегина

    size_t sizeof_code;

    for (int i = 0; i < 2; i++)
        sizeof_code = Assembler(&input_text, code);

//    printf("\nsizeof code: %ld\n", sizeof_code); //Тестовая печать

	MakeBinaryFile (code, sizeof_code, input_text.output_file_name);

	MemoryFree(&input_text);
	free(code);

    return 0;
}