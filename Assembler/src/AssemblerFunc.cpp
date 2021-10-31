#include "../include/Assembler.h"

size_t Assembler (Text* input, void* code)
{
	char command[CMD_SIZE];

	data_t cons = 0;
//    char reg = 0;
//    int scan = 0;

	int num_of_commands = 0;

	for (size_t i = 0; i < input->num_of_strings; i++)
	{
//        scan = sscanf(input->strings[i].ptr, "%s %d%c", command, &cons, &reg);
        sscanf(input->strings[i].ptr, "%s %d", command, &cons);
		//push
		if(strcmp("push", command) == 0)
		{
//            if (scan == 2)
//            {
//                if(reg != 0)
//                {
//                    *((char*)code + num_of_commands) = (char) (CMD_PUSH | ARG_REG);
//                }
//            }
            *((char*)code + num_of_commands) = (char) CMD_PUSH;
            num_of_commands += sizeof(char);

            *(int*)((char*)code + num_of_commands) = cons;
            num_of_commands += sizeof(int);
		}
		//pop
		if(strcmp("pop", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_POP;
            num_of_commands += sizeof(char);
		}
		//add
		if(strcmp("add", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_ADD;
            num_of_commands += sizeof(char);
		}
		//sub
		if(strcmp("sub", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_SUB;
            num_of_commands += sizeof(char);
		}
		//mul
		if(strcmp("mul", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_MUL;
            num_of_commands += sizeof(char);
		}
		//div
		if(strcmp("div", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_DIV;
            num_of_commands += sizeof(char);
		}
		//out
		if(strcmp("out", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_OUT;
            num_of_commands += sizeof(char);
		}
        //in
        if(strcmp("in", command) == 0)
        {
            *((char*)code + num_of_commands) = (char)CMD_IN;
            num_of_commands += sizeof(char);
        }
		//hlt
		if(strcmp("hlt", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_HLT;
            num_of_commands += sizeof(char);
		}
	}

	return num_of_commands;
}

int MakeBinaryFile (void* code, int sizeof_code, const char* file_name)
{
	FILE* file_ptr = nullptr;

	file_ptr = fopen(file_name, "wb");

	if (file_ptr == nullptr)
    {
        printf("In Function MakeBinaryFile: Can't open file");
        return CANT_OPEN_FILE;
    }

	if (fwrite(code, sizeof(char), sizeof_code, file_ptr) != sizeof_code)
    {
        printf("In Function MakeBinaryFile: Wrong write of code");
        return WRONG_WRITE_TO_FILE;
    }

	return 0;
}