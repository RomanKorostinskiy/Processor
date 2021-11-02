#include "../include/Assembler.h"

char SwitchReg (char reg)
{
    switch (reg)
    {
        case 'a':
            return AX;
        case 'b':
            return BX;
        case 'c':
            return CX;
        case 'd':
            return DX;
        default:
            return WRONG_REGISTER;
    }
}

size_t Assembler (Text* input, void* code)
{
	char command[CMD_SIZE] = {0};

    int num_of_commands = 0;

	for (size_t i = 0; i < input->num_of_strings; i++)
	{
        data_t cons = 0;
        char reg = 0;

        int scan_ok = 0;
        int scan_case = 0;

        if (sscanf(input->strings[i].ptr, "%s [%d + %cx%n]", command, &cons, &reg, &scan_ok) == 3
            && scan_ok)
            scan_case = CONS_REG_ADR;
        else if (sscanf(input->strings[i].ptr, "%s %d + %cx%n", command, &cons, &reg, &scan_ok) == 3
            && scan_ok)
            scan_case = CONS_REG;
        else if(sscanf(input->strings[i].ptr, "%s [%cx]%n", command, &reg, &scan_ok) == 2
                && scan_ok)
            scan_case = REG_ADR;
        else if(sscanf(input->strings[i].ptr, "%s %cx%n", command, &reg, &scan_ok) == 2
                && scan_ok)
            scan_case = REG;
        else if(sscanf(input->strings[i].ptr, "%s [%d]%n", command, &cons, &scan_ok) == 2
                && scan_ok)
            scan_case = CONS_ADR;
        else if(sscanf(input->strings[i].ptr, "%s %d%n", command, &cons, &scan_ok) == 2
                && scan_ok)
            scan_case = CONS;
        else if(sscanf(input->strings[i].ptr, "%s%n", command, &scan_ok) == 1
                && scan_ok)
            scan_case = NO_ARGS;
        else
        {
            printf("In Function Assembler: Unknown command format at line %ld", i + 1);
            return SYNTAX_ERROR;
        }
		//push
		if(strcmp("push", command) == 0)
		{
            if (scan_case == CONS_REG_ADR)
            {
                *((char*)code + num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_CONS | ARG_RAM);
                num_of_commands += sizeof(char);

                *(int*)((char*)code + num_of_commands) = cons;
                num_of_commands += sizeof(int);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            else if (scan_case == CONS_REG)
            {
                *((char*)code + num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_CONS);
                num_of_commands += sizeof(char);

                *(int*)((char*)code + num_of_commands) = cons;
                num_of_commands += sizeof(int);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            else if (scan_case == REG_ADR)
            {
                *((char *) code + num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_RAM);
                num_of_commands += sizeof(char);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            else if (scan_case == REG)
            {
                *((char *) code + num_of_commands) = (char) (CMD_PUSH | ARG_REG);
                num_of_commands += sizeof(char);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            else if (scan_case == CONS_ADR)
            {
                *((char *) code + num_of_commands) = (char) (CMD_PUSH | ARG_CONS | ARG_RAM);
                num_of_commands += sizeof(char);

                *(int*)((char*)code + num_of_commands) = cons;
                num_of_commands += sizeof(int);
            }
            else if (scan_case == CONS)
            {
                *((char *) code + num_of_commands) = (char) (CMD_PUSH | ARG_CONS);
                num_of_commands += sizeof(char);

                *(int*)((char*)code + num_of_commands) = cons;
                num_of_commands += sizeof(int);
            }
            else
            {
                printf("In Function Assembler: No push arguments at line %ld", i + 1);
                return PUSH_ARGS_ERROR;
            }
        }
		//pop
		else if(strcmp("pop", command) == 0)
		{
            if (scan_case == CONS_REG_ADR)
            {
                *((char *) code + num_of_commands) = (char) (CMD_POP | ARG_REG | ARG_CONS | ARG_RAM) ;
                num_of_commands += sizeof(char);

                *(int*)((char*)code + num_of_commands) = cons;
                num_of_commands += sizeof(int);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            if (scan_case == REG_ADR)
            {
                *((char *) code + num_of_commands) = (char) (CMD_POP | ARG_REG | ARG_RAM);
                num_of_commands += sizeof(char);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            if (scan_case == REG)
            {
                *((char *) code + num_of_commands) = (char) (CMD_POP | ARG_REG);
                num_of_commands += sizeof(char);

                if (SwitchReg(reg) == WRONG_REGISTER)
                {
                    printf("In Function Assembler: Wrong register at line %ld", i + 1);
                    return WRONG_REGISTER;
                }

                *((char *) code + num_of_commands) = SwitchReg(reg);
                num_of_commands += sizeof(char);
            }
            if (scan_case == CONS_ADR)
            {
                *((char *) code + num_of_commands) = (char) (CMD_POP | ARG_CONS | ARG_RAM);
                num_of_commands += sizeof(char);

                *(int*)((char*)code + num_of_commands) = cons;
                num_of_commands += sizeof(int);
            }
		}
		//add
		else if(strcmp("add", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_ADD;
            num_of_commands += sizeof(char);
		}
		//sub
		else if(strcmp("sub", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_SUB;
            num_of_commands += sizeof(char);
		}
		//mul
		else if(strcmp("mul", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_MUL;
            num_of_commands += sizeof(char);
		}
		//div
		else if(strcmp("div", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_DIV;
            num_of_commands += sizeof(char);
		}
		//out
		else if(strcmp("out", command) == 0)
		{
            *((char*)code + num_of_commands) = (char)CMD_OUT;
            num_of_commands += sizeof(char);
		}
        //in
        else if(strcmp("in", command) == 0)
        {
            *((char*)code + num_of_commands) = (char)CMD_IN;
            num_of_commands += sizeof(char);
        }
		//hlt
        else if (strcmp("hlt", command) == 0)
        {
            *((char*)code + num_of_commands) = (char)CMD_HLT;
            num_of_commands += sizeof(char);
        }
		else
        {
            printf("In Function Assembler: Unknown command name at line %ld", i + 1);
            return SYNTAX_ERROR;
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