#include "../include/Assembler.h"

size_t Assembler (Text* input, data_t* code)
{
	char command[5];

	data_t param = 0;

	int num_of_commands = 0;

	for (size_t i = 0; i < input->num_of_strings; i++)
	{
		sscanf(input->strings[i].ptr, "%s %d", command, &param);

		//push
		if(strcmp("push", command) == 0)
		{
			code[num_of_commands++] = CMD_PUSH;

			code[num_of_commands++] = param;
		}
		//pop
		if(strcmp("pop", command) == 0)
		{
			code[num_of_commands++] = CMD_POP;
		}
		//add
		if(strcmp("add", command) == 0)
		{
			code[num_of_commands++] = CMD_ADD;
		}
		//sub
		if(strcmp("sub", command) == 0)
		{
			code[num_of_commands++] = CMD_SUB;
		}
		//mul
		if(strcmp("mul", command) == 0)
		{
			code[num_of_commands++] = CMD_MUL;
		}
		//div
		if(strcmp("div", command) == 0)
		{
			code[num_of_commands++] = CMD_DIV;
		}
		//out
		if(strcmp("out", command) == 0)
		{
			code[num_of_commands++] = CMD_OUT;
		}
		//hlt
		if(strcmp("hlt", command) == 0)
		{
			code[num_of_commands++] = CMD_HLT;
		}
	}

	return num_of_commands;
}

int MakeBinaryFile (data_t* code, int sizeof_code)
{
	FILE* output = nullptr;

	output = fopen("code.bin", "wb");

	if (output == nullptr)
		return CANT_OPEN_FILE;

	fwrite(code, sizeof(data_t), sizeof_code, output);

	return 0;
}