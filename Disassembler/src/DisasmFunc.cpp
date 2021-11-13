#include "../include/Disasm.h"

int GetFileNames (Disasm* disasm, int argc, char* argv[])
{
    if (argc == 3)
    {
        disasm->code_file_name   = argv[1];
        disasm->disasm_file_name = argv[2];

        return 0;
    }
    else
        return 1;
}

size_t GetSizeOfFile (FILE* fp)
{
    if (fp == nullptr)
    {
        printf("In Function GetSizeOfFile: fp is nullptr\n");
        return 0;
    }

    fseek(fp, 0, SEEK_END); //переводим указатель на конец файла
    size_t size_of_file = ftell(fp); //считаем количество байт на которое указатель отстоит от начала файла
    rewind(fp); //возвращает указатель на начало файла

    return size_of_file;
}

int GetCode (Disasm* disasm)
{
    FILE* file_ptr = nullptr;

    if ((file_ptr = fopen(disasm->code_file_name, "rb")) == nullptr)
    {
        printf("In Function GetCode: Can't open file\n");
        return CANT_OPEN_FILE;
    }

    disasm->sizeof_code = GetSizeOfFile (file_ptr);
    disasm->code = (void*)calloc(disasm->sizeof_code, sizeof(char*));

    if (fread (disasm->code, sizeof(char), disasm->sizeof_code, file_ptr) != disasm->sizeof_code)
    {
        printf("In Function GetCode: Can't read code from file\n");
        return CANT_READ_FROM_FILE;
    }

    fclose(file_ptr);

    return 0;
}

FILE* OpenDisasmFile (char* file_name)
{
    FILE* fp = fopen(file_name, "w");

    if (!fp)
    {
        printf("In Function OpenDisasmFile: Can't open a file");
        return nullptr;
    }

    return fp;
}

int Disassembler (Disasm* disasm)
{
    FILE* disasm_file_ptr = OpenDisasmFile (disasm->disasm_file_name);

    while(disasm->ip < disasm->sizeof_code)
    {
        data_t var1 = 0;
        data_t var2 = 0;
        data_t arg = 0;

        int cmd = *((char *) disasm->code + disasm->ip) & 0x1F;
        int type = *((char *) disasm->code + disasm->ip) & 0xE0;

        switch (cmd)
        {
            case CMD_PUSH:
                disasm->ip += sizeof(char);
                PrintPush(disasm, disasm_file_ptr, type);
                break;

            case CMD_POP:
                disasm->ip += sizeof(char);
                PrintPop(disasm, disasm_file_ptr, type);
                break;

            case CMD_ADD:  case CMD_SUB: case CMD_MUL: case CMD_DIV:
            case CMD_SQRT: case CMD_OUT: case CMD_IN:  case CMD_RET:
            case CMD_HLT:
                PrintNoArgsCommands(disasm, disasm_file_ptr, cmd);
                break;

            case CMD_JMP: case CMD_JA: case CMD_JAE: case CMD_JB:
            case CMD_JBE: case CMD_JE: case CMD_JNE: case CMD_CALL:
                PrintJumpCommands(disasm, disasm_file_ptr, cmd);
                break;

            default:
                printf("In Function Disassembler: default case is reached\n");
                return DISASSEMBLER_DEFAULT_CASE;
        }
    }

    fclose(disasm_file_ptr);

    return DISASSEMBLER_DEFAULT_CASE;
}

int PrintPush (Disasm* disasm, FILE* fp, int type)
{
    switch (type)
    {
        case ARG_CONS:
            fprintf(fp, "push %0.f\n", *(data_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(data_t);
            break;

        case ARG_REG:
            fprintf(fp, "push %cx\n", *(char*)((char*)disasm->code + disasm->ip) + 'a');
            disasm->ip += sizeof(char);
            break;

        case ARG_CONS | ARG_REG:
            fprintf(fp, "push %0.f + %cx\n", *(data_t*)((char*)disasm->code + disasm->ip),
                    *(char*)((char*)disasm->code + disasm->ip + sizeof(data_t)) + 'a');
            disasm->ip += sizeof(data_t);
            disasm->ip += sizeof(char);
            break;

        case ARG_RAM | ARG_CONS:
            fprintf(fp, "push [%0.f]\n", *(data_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(data_t);
            break;

        case ARG_RAM | ARG_REG:
            fprintf(fp, "push [%cx]\n", *(char*)((char*)disasm->code + disasm->ip) + 'a');
            disasm->ip += sizeof(char);
            break;

        case ARG_RAM | ARG_CONS | ARG_REG:
            fprintf(fp, "push [%0.f + %cx]\n", *(data_t*)((char*)disasm->code + disasm->ip),
                    *(char*)((char*)disasm->code + disasm->ip + sizeof(data_t)) + 'a');
            disasm->ip += sizeof(data_t);
            disasm->ip += sizeof(char);
            break;

        default:
            printf("In Function PrintPush: default case is reached\n");
            return DISASSEMBLER_DEFAULT_CASE;
    }

    return 0;
}

int PrintPop (Disasm* disasm, FILE* fp, int type)
{
    switch (type)
    {
        case ARG_REG:
            fprintf(fp, "pop %cx\n", *(char*)((char*)disasm->code + disasm->ip) + 'a');
            disasm->ip += sizeof(char);
            break;

        case ARG_RAM | ARG_CONS:
            fprintf(fp, "pop [%0.f]\n", *(data_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(data_t);
            break;

        case ARG_RAM | ARG_REG:
            fprintf(fp, "pop [%cx]\n", *(char*)((char*)disasm->code + disasm->ip) + 'a');
            disasm->ip += sizeof(char);
            break;

        case ARG_RAM | ARG_CONS | ARG_REG:
            fprintf(fp, "pop [%0.f + %cx]\n", *(data_t*)((char*)disasm->code + disasm->ip),
                    *(char*)((char*)disasm->code + disasm->ip + sizeof(data_t)) + 'a');
            disasm->ip += sizeof(data_t);
            disasm->ip += sizeof(char);
            break;

        case NO_ARGS:
            fprintf(fp, "pop\n");
            break;

        default:
            printf("In Function PrintPop: default case is reached\n");
            return DISASSEMBLER_DEFAULT_CASE;
    }

    return 0;
}

int PrintNoArgsCommands (Disasm* disasm, FILE* fp, int cmd)
{
    switch (cmd)
    {
        case CMD_ADD:
            fprintf(fp, "add\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_SUB:
            fprintf(fp, "sub\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_MUL:
            fprintf(fp, "mul\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_DIV:
            fprintf(fp, "div\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_SQRT:
            fprintf(fp, "sqrt\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_OUT:
            fprintf(fp, "out\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_IN:
            fprintf(fp, "in\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_RET:
            fprintf(fp, "ret\n");
            disasm->ip += sizeof(char);
            break;

        case CMD_HLT:
            fprintf(fp, "hlt\n");
            disasm->ip += sizeof(char);
            break;

        default:
            printf("In Function PrintNoArgsCommands: default case is reached\n");
            return DISASSEMBLER_DEFAULT_CASE;
    }

    return 0;
}

int PrintJumpCommands (Disasm* disasm, FILE* fp, int cmd)
{
    switch (cmd)
    {
        case CMD_JMP:
            fprintf(fp, "jmp ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_JA:
            fprintf(fp, "ja ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_JAE:
            fprintf(fp, "jae ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_JB:
            fprintf(fp, "jb ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_JBE:
            fprintf(fp, "jbe ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_JE:
            fprintf(fp, "je");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_JNE:
            fprintf(fp, "jne ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        case CMD_CALL:
            fprintf(fp, "call ");
            disasm->ip += sizeof(char);
            fprintf(fp, "%ld\n", *(size_t*)((char*)disasm->code + disasm->ip));
            disasm->ip += sizeof(size_t);
            break;

        default:
            printf("In Function PrintJumpCommands: default case is reached\n");
            return DISASSEMBLER_DEFAULT_CASE;
    }

    return 0;
}