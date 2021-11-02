#include "../include/Assembler.h"

size_t Assembler (Text* input, void* code)
{
    char command[CMD_SIZE] = {0};
    char tag_name[TAG_SIZE] = {0};

    int num_of_commands = 0;

    Tags* tag_table = nullptr;
    tag_table = (Tags*) calloc(SIZE_OF_TAG_TABLE, sizeof(Tags));
    int num_of_tag = 0;

    assert(tag_table);

    for (size_t line = 0; line < input->num_of_strings; line++)
    {
        data_t cons = 0;
        char reg = 0;

        int scan_case = 0;

        if ((scan_case = ScanCommand(input->strings[line].ptr, command, tag_name, &cons, &reg))
            == SYNTAX_ERROR)
        {
            printf("In Function Assembler: Unknown command format at line %ld\n", line + 1);
            return SYNTAX_ERROR;
        }

        //tag
        if(scan_case == TAG)
        {
            tag_table[num_of_tag].adr = num_of_commands;

            size_t tag_len = strlen(tag_name);
            tag_table[num_of_tag].name = (char*) calloc(tag_len, sizeof(char));
            memcpy(tag_table[num_of_tag].name, tag_name, tag_len);

            num_of_tag++;
        }
        //push
        else if(strcmp("push", command) == 0)
        {
            int errors = 0;
            errors = PushCase(code, &num_of_commands, scan_case, cons, reg);

            if (errors == WRONG_REGISTER)
            {
                printf("In Function Assembler: Wrong push register at line %ld\n", line + 1);
                return WRONG_REGISTER;
            }
            if (errors == PUSH_ARGS_ERROR)
            {
                printf("In Function Assembler: Wrong push argument at line %ld\n", line + 1);
                return PUSH_ARGS_ERROR;
            }
        }
        //pop
        else if(strcmp("pop", command) == 0)
        {
            int errors = 0;
            errors = PopCase(code, &num_of_commands, scan_case, cons, reg);

            if (errors == WRONG_REGISTER)
            {
                printf("In Function Assembler: Wrong pop register at line %ld\n", line + 1);
                return WRONG_REGISTER;
            }
            if (errors == POP_ARGS_ERROR)
            {
                printf("In Function Assembler: Wrong pop argument at line %ld\n", line + 1);
                return POP_ARGS_ERROR;
            }
        }
        //add
        else if(strcmp("add", command) == 0) //TODO обернуть все безаргументные команды в одну функцию
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
        else if(strcmp("hlt", command) == 0)
        {
            *((char*)code + num_of_commands) = (char)CMD_HLT;
            num_of_commands += sizeof(char);
        }
        else if (scan_case == JMP)
        {
            int  tag_place = 0;

            while(tag_place < num_of_tag)
            {
                if (strcmp(tag_name, tag_table[tag_place].name) == 0) //TODO валгринд ругается на strcmp (в случае когда метка после jmp не ругается)
                    break;

                tag_place++;
            }

            if(strcmp("jmp", command) == 0) //TODO обернуть всё это в функцию
            {
                *((char*)code + num_of_commands) = CMD_JMP;
                num_of_commands += sizeof(char);
            }
            if(strcmp("jae", command) == 0)
            {
                *((char*)code + num_of_commands) = CMD_JMP;
                num_of_commands += sizeof(char);
            }
            if(strcmp("jb", command) == 0)
            {
                *((char*)code + num_of_commands) = CMD_JMP;
                num_of_commands += sizeof(char);
            }
            if(strcmp("jbe", command) == 0)
            {
                *((char*)code + num_of_commands) = CMD_JMP;
                num_of_commands += sizeof(char);
            }
            if(strcmp("je", command) == 0)
            {
                *((char*)code + num_of_commands) = CMD_JMP;
                num_of_commands += sizeof(char);
            }
            if(strcmp("jne", command) == 0)
            {
                *((char*)code + num_of_commands) = CMD_JMP;
                num_of_commands += sizeof(char);
            }

            if (tag_place < num_of_tag)
            {
                *((char*)code + num_of_commands) = (char)tag_table[tag_place].adr;
                num_of_commands += sizeof(char);
            }
            else if (tag_place == num_of_tag) //TODO сделать таблицу доступной при втором проходе
            {
                *((char*)code + num_of_commands) = -1;
                num_of_commands += sizeof(char);
            }
        }
        else
        {
            printf("In Function Assembler: Unknown command name at line %ld\n", line + 1);
            return SYNTAX_ERROR;
        }
    }

    for (int i = 0; i < num_of_tag; i++)
        free(tag_table[i].name);

    free(tag_table);

    return num_of_commands;
}

int ScanCommand(char* string, char* command, char* tag_name, data_t* cons, char* reg)
{
    int scan_case = 0;
    int scan_ok = 0;

    if (sscanf(string, "%s [%d + %cx%n]", command, cons, reg, &scan_ok) == 3
        && scan_ok)
        scan_case = CONS_REG_ADR;
    else if (sscanf(string, "%s %d + %cx%n", command, cons, reg, &scan_ok) == 3
             && scan_ok)
        scan_case = CONS_REG;
    else if(sscanf(string, "%s [%cx]%n", command, reg, &scan_ok) == 2
            && scan_ok)
        scan_case = REG_ADR;
    else if(sscanf(string, "%s %cx%n", command, reg, &scan_ok) == 2
            && scan_ok)
        scan_case = REG;
    else if(sscanf(string, "%s [%d]%n", command, cons, &scan_ok) == 2
            && scan_ok)
        scan_case = CONS_ADR;
    else if(sscanf(string, "%s %d%n", command, cons, &scan_ok) == 2
            && scan_ok)
        scan_case = CONS;
    else if(sscanf(string, "%s %s%n", command, tag_name,  &scan_ok) == 2
            && scan_ok)
        scan_case = JMP;
    else if(sscanf(string, ":%s%n", tag_name, &scan_ok) == 1
            && scan_ok)
        scan_case = TAG;
    else if(sscanf(string, "%s%n", command, &scan_ok) == 1
            && scan_ok)
        scan_case = NO_ARGS;
    else
        return SYNTAX_ERROR;

    return scan_case;
}

int PushCase (void* code, int* num_of_commands, int scan_case, data_t cons, char reg)
{
    if (scan_case == CONS_REG_ADR)
    {
        *((char*)code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_CONS | ARG_RAM);
        *num_of_commands += sizeof(char);

        *(int*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(int);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == CONS_REG)
    {
        *((char*)code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_CONS);
        *num_of_commands += sizeof(char);

        *(int*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(int);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_RAM);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == CONS_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_CONS | ARG_RAM);
        *num_of_commands += sizeof(char);

        *(int*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(int);
    }
    else if (scan_case == CONS)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_CONS);
        *num_of_commands += sizeof(char);

        *(int*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(int);
    }
    else
        return PUSH_ARGS_ERROR;

    return 0;
}

int PopCase (void* code, int* num_of_commands, int scan_case, data_t cons, char reg)
{
    if (scan_case == CONS_REG_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_REG | ARG_CONS | ARG_RAM) ;
        *num_of_commands += sizeof(char);

        *(int*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(int);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_REG | ARG_RAM);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_REG);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 3)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == CONS_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_CONS | ARG_RAM);
        *num_of_commands += sizeof(char);

        *(int*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(int);
    }
    else
        return POP_ARGS_ERROR;

    return 0;
}

int MakeBinaryFile (void* code, int sizeof_code, const char* file_name)
{
	FILE* file_ptr = nullptr;

	file_ptr = fopen(file_name, "wb");

	if (file_ptr == nullptr)
    {
        printf("In Function MakeBinaryFile: Can't open file\n");
        return CANT_OPEN_FILE;
    }

	if (fwrite(code, sizeof(char), sizeof_code, file_ptr) != sizeof_code)
    {
        printf("In Function MakeBinaryFile: Wrong write of code\n");
        return WRONG_WRITE_TO_FILE;
    }

	return 0;
}