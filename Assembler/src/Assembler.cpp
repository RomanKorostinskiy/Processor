#include "../include/Assembler.h"

int main(int argc, char* argv[])
{
	Text input_text = {};

    if (GetFileNames(&input_text, argc, argv) == 1)
    {
        printf("Error: wrong name of file(s)");
        return 1;
    }

	void* code = nullptr;

	code = (void*) calloc(MAX_SIZE_OF_CODE, sizeof(char));

	ReadFromFile(&input_text);

	MakeString(&input_text);

	size_t sizeof_code = Assembler(&input_text, code);

    printf("%ld", sizeof_code);

	MakeBinaryFile (code, sizeof_code, input_text.output_file_name);

	MemoryFree(&input_text);
	free(code);

    return 0;
}