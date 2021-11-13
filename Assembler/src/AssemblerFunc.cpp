#include "../include/Assembler.h"

int MakeBinaryFile (void* code, size_t sizeof_code, const char* file_name)
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

size_t Assembler (Text* input, void* code)
{
    char command[CMD_SIZE] = {0};
    char tag_name[TAG_SIZE] = {0};

    int num_of_commands = 0;

    static Tags* tag_table = (Tags*) calloc(SIZE_OF_TAG_TABLE, sizeof(Tags));
    static size_t num_of_tags = 0;
    static int asm_call_num = 1;
    assert(tag_table);


    for (size_t line = 0; line < input->num_of_strings; line++)
    {
        data_t cons = 0;
        char reg = 0;

        int scan_case = 0;

        //scanning commands
        if ((scan_case = ScanCommand(input->strings[line].ptr, command, tag_name, &cons, &reg))
            == SYNTAX_ERROR)
        {
            printf("In Function Assembler: Unknown command format at line %ld\n", line + 1);
            return SYNTAX_ERROR;
        }

       //commands with no args
       if (scan_case == NO_ARGS)
        {
            if (NoArgsCommands (code, &num_of_commands, command) == SYNTAX_ERROR)
            {
                printf("In Function Assembler: Unknown command name at line %ld\n", line + 1);
                return SYNTAX_ERROR;
            }
        }
        //tag
        else if(scan_case == TAG)
        {
            int  tag_place = 0;

            while (num_of_tags > 0 && tag_place < num_of_tags)
            {
                if (strcmp(tag_name, tag_table[tag_place].name) == 0) //TODO валгринд ругается на strcmp
                    break;

                tag_place++;
            }

            if (tag_place == num_of_tags)
            {
                tag_table[num_of_tags].adr = num_of_commands;

                size_t tag_len = strlen(tag_name);
                tag_table[num_of_tags].name = (char *) calloc(tag_len, sizeof(char));
                memcpy(tag_table[num_of_tags].name, tag_name, tag_len);

                num_of_tags++;
            }
        }
        //jump
        else if (scan_case == JMP)
        {
            size_t  tag_place = 0;

            while(num_of_tags > 0 && tag_place < num_of_tags)
            {
                if (strcmp(tag_name, tag_table[tag_place].name) == 0) //TODO валгринд ругается на strcmp
                    break;

                tag_place++;
            }

            JumpCommand (code, &num_of_commands, command);

            if (tag_place < num_of_tags)
            {
                *(size_t*)((char*)code + num_of_commands) = tag_table[tag_place].adr;
                num_of_commands += sizeof(size_t);
            }
            else if (tag_place == num_of_tags)
            {
                if (asm_call_num == 1)
                {
                    *(size_t*)((char*)code + num_of_commands) = -1;
                    num_of_commands += sizeof(size_t);
                }
                else if (asm_call_num > 1)
                {
                    printf("In Function Assembler: Wrong Call/Jump argument at line %ld", line);
                    return CALL_ARGS_ERROR;
                }
            }
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
        else
        {
            printf("In Function Assembler: Unknown command name at line %ld\n", line + 1);
            return SYNTAX_ERROR;
        }
    }

    if (asm_call_num > 1)
    {
        for (int i = 0; i < num_of_tags; i++)
            free(tag_table[i].name);

        free(tag_table);
    }

    asm_call_num++;

    return num_of_commands;

}

int ScanCommand(char* string, char* command, char* tag_name, data_t* cons, char* reg)
{
    int scan_case = 0;
    int scan_ok = 0;

    char* comment_place = nullptr;

    if ((comment_place = strchr(string, ';')) != nullptr) //TODO строка add\t считывается как add, хотя массив команд на 4 символа, почему?
        *comment_place = '\0';

    if (sscanf(string, "%s [%lf + %cx%n]", command, cons, reg, &scan_ok) == 3
        && scan_ok)
        scan_case = CONS_REG_ADR;
    else if (sscanf(string, "%s %lf + %cx%n", command, cons, reg, &scan_ok) == 3
             && scan_ok)
        scan_case = CONS_REG;
    else if(sscanf(string, "%s [%cx]%n", command, reg, &scan_ok) == 2
            && scan_ok)
        scan_case = REG_ADR;
    else if(sscanf(string, "%s %cx%n", command, reg, &scan_ok) == 2
            && scan_ok)
        scan_case = REG;
    else if(sscanf(string, "%s [%lf]%n", command, cons, &scan_ok) == 2
            && scan_ok)
        scan_case = CONS_ADR;
    else if(sscanf(string, "%s %lf%n", command, cons, &scan_ok) == 2
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

        *(data_t*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(data_t);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == CONS_REG)
    {
        *((char*)code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_CONS);
        *num_of_commands += sizeof(char);

        *(data_t*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(data_t);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG | ARG_RAM);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_REG);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == CONS_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_CONS | ARG_RAM);
        *num_of_commands += sizeof(char);

        *(data_t*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(data_t);
    }
    else if (scan_case == CONS)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_PUSH | ARG_CONS);
        *num_of_commands += sizeof(char);

        *(data_t*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(data_t);
    }
    else
        return PUSH_ARGS_ERROR;

    return 0;
}

int PopCase (void* code, int* num_of_commands, int scan_case, data_t cons, char reg)
{
    if (scan_case == CONS_REG_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_REG | ARG_CONS | ARG_RAM);
        *num_of_commands += sizeof(char);

        *(data_t*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(data_t);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_REG | ARG_RAM);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == REG)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_REG);
        *num_of_commands += sizeof(char);

        if (reg - 'a' < 0 || reg - 'a' > 7)
            return WRONG_REGISTER;
        *((char *) code + *num_of_commands) = (char)(reg - 'a');
        *num_of_commands += sizeof(char);
    }
    else if (scan_case == CONS_ADR)
    {
        *((char *) code + *num_of_commands) = (char) (CMD_POP | ARG_CONS | ARG_RAM);
        *num_of_commands += sizeof(char);

        *(data_t*)((char*)code + *num_of_commands) = cons;
        *num_of_commands += sizeof(data_t);
    }
    else
        return POP_ARGS_ERROR;

    return 0;
}

int NoArgsCommands (void* code, int* num_of_commands, char* command)
{
        //add
    if(strcmp("add", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_ADD;
        *num_of_commands += sizeof(char);
    }
        //sub
    else if(strcmp("sub", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_SUB;
        *num_of_commands += sizeof(char);
    }
        //mul
    else if(strcmp("mul", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_MUL;
        *num_of_commands += sizeof(char);
    }
        //div
    else if(strcmp("div", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_DIV;
        *num_of_commands += sizeof(char);
    }
        //sqrt
    else if(strcmp("sqrt", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_SQRT;
        *num_of_commands += sizeof(char);
    }
        //out
    else if(strcmp("out", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_OUT;
        *num_of_commands += sizeof(char);
    }
        //in
    else if(strcmp("in", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_IN;
        *num_of_commands += sizeof(char);
    }
        //pop
    else if(strcmp("pop", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_POP;
        *num_of_commands += sizeof(char);
    }
        //ret
    else if(strcmp("ret", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_RET;
        *num_of_commands += sizeof(char);
    }
        //hlt
    else if(strcmp("hlt", command) == 0)
    {
        *((char*)code + *num_of_commands) = (char)CMD_HLT;
        *num_of_commands += sizeof(char);
    }
    else
        return SYNTAX_ERROR;

    return 0;
}

int JumpCommand (void* code, int* num_of_commands, char* command)
{
    if(strcmp("jmp", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JMP;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("ja", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JA;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("jae", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JAE;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("jb", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JB;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("jbe", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JBE;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("je", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JE;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("jne", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_JNE;
        *num_of_commands += sizeof(char);
    }
    else if(strcmp("call", command) == 0)
    {
        *((char*)code + *num_of_commands) = CMD_CALL;
        *num_of_commands += sizeof(char);
    }

    return 0;
}