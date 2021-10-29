#include "../include/Assembler.h"

int main(int argc, char* argv[])
{
	Text input_text = {};

    if (GetFileNames(&input_text, argc, argv) == 1)
    {
        printf("Error: wrong name of file(s)");
        return 1;
    }

	data_t* code = nullptr;

	code = (data_t*) calloc(MAX_SIZE_OF_CODE, sizeof(data_t));

	ReadFromFile(&input_text);

	MakeString(&input_text);

	size_t sizeof_code = Assembler(&input_text, code);

	MakeBinaryFile (code, sizeof_code);

	//---------------------------------
	for (int i = 0; code[i] != 0; i++)
	{
		printf("\n%d", code[i]);
	}
	printf("\nsizeof code = %ld\n", sizeof_code);
	//---------------------------------

	MemoryFree(&input_text);
	free(code);

    return 0;
}