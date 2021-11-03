#include "../include/Processor.h"

int GetFileNames (char** file_name, int argc, char* argv[])
{
    if (argc == 2)
    {
        *file_name = argv[1];

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

int GetCode (Processor_t* processor, const char* file_name)
{
    FILE* file_ptr = nullptr;

    if ((file_ptr = fopen(file_name, "rb")) == nullptr)
    {
        printf("In Function GetCode: Can't open file\n");
        return CANT_OPEN_FILE;
    }

    processor->sizeof_code = GetSizeOfFile (file_ptr);
    processor->code = (void*) calloc(processor->sizeof_code, sizeof(char*));

    if (fread (processor->code, sizeof(char), processor->sizeof_code, file_ptr) != processor->sizeof_code)
    {
        printf("In Function GetCode: Can't read code from file\n");
        return CANT_READ_FROM_FILE;
    }

    fclose(file_ptr);

    return 0;
}

int Processor (Processor_t* processor)
{
    while(processor->ip < processor->sizeof_code)
    {
        int var1 = 0;
        int var2 = 0;
        int arg = 0;

        int cmd = *((char*)processor->code + processor->ip) & 0x1F;
        int type = *((char*)processor->code + processor->ip) & 0xE0;

        switch (cmd)
        {
            case CMD_PUSH:
                processor->ip += sizeof(char);

                if((type & ARG_CONS) != 0)
                {
                    arg += *(int*)((char*)processor->code + processor->ip);
                    processor->ip += sizeof(int);
                }
                if((type & ARG_REG) != 0)
                {
                    arg += processor->REGS[*(char*)((char*)processor->code + processor->ip)];
                    processor->ip += sizeof(char);
                }
                if((type & ARG_RAM) != 0)
                    arg = processor->RAM[arg];

                StackPush (&processor->stack, arg);
                break;

            case CMD_POP:
                processor->ip += sizeof(char);

                if(type == 0)
                    StackPop(&processor->stack);
                else if((type & ARG_RAM) == 0 && (type & ARG_REG) != 0 )
                {
                    processor->REGS[*(char*)((char*)processor->code + processor->ip)] = StackPop(&processor->stack);
                    processor->ip += sizeof(char);
                }
                else if((type & ARG_RAM) != 0)
                {
                    if((type & ARG_CONS) != 0)
                    {
                        arg += *(int*)((char*)processor->code + processor->ip);
                        processor->ip += sizeof(int);
                    }
                    if((type & ARG_REG) != 0)
                    {
                        arg += processor->REGS[*(char*)((char*)processor->code + processor->ip)];
                        processor->ip += sizeof(char);
                    }

                    processor->RAM[arg] = StackPop(&processor->stack);
                }

                break;

            case CMD_ADD:
                StackPush(&processor->stack,
                          StackPop(&processor->stack) + StackPop(&processor->stack));
                processor->ip += sizeof(char);
                break;

            case CMD_SUB:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                StackPush(&processor->stack, var1 - var2);
                processor->ip += sizeof(char);
                break;

            case CMD_MUL:
                StackPush(&processor->stack,
                          StackPop(&processor->stack) * StackPop(&processor->stack));
                processor->ip += sizeof(char);
                break;

            case CMD_DIV:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                if (var2 == 0)
                {
                    printf("Сan't divide by zero\n");
                    return WRONG_DATA;
                }

                StackPush(&processor->stack, var1 / var2);
                processor->ip += sizeof(char);
                break;

            case CMD_OUT:
                printf("out: %d\n", StackPop(&processor->stack));
                processor->ip += sizeof(char);
                break;

            case CMD_IN:
                scanf("%d", &var1);
                StackPush(&processor->stack, var1);
                processor->ip += sizeof(char);
                break;

            case CMD_JMP:
                processor->ip += sizeof(char);

                processor->ip = *(int*)((char*)processor->code + processor->ip);
                break;

            case CMD_JA:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                processor->ip += sizeof(char);

                if (var1 > var2)
                    processor->ip = *(int *) ((char *) processor->code + processor->ip);
                else
                    processor->ip += sizeof(int);

                StackPush(&processor->stack, var1);
                StackPush(&processor->stack, var2);
                break;

            case CMD_JAE:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                processor->ip += sizeof(char);

                if (var1 >= var2)
                    processor->ip = *(int *) ((char *) processor->code + processor->ip);
                else
                    processor->ip += sizeof(int);

                StackPush(&processor->stack, var1);
                StackPush(&processor->stack, var2);
                break;

            case CMD_JB:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                processor->ip += sizeof(char);

                if (var1 < var2)
                    processor->ip = *(int *) ((char *) processor->code + processor->ip);
                else
                    processor->ip += sizeof(int);

                StackPush(&processor->stack, var1);
                StackPush(&processor->stack, var2);
                break;

            case CMD_JBE:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                processor->ip += sizeof(char);

                if (var1 <= var2)
                    processor->ip = *(int *) ((char *) processor->code + processor->ip);
                else
                    processor->ip += sizeof(int);

                StackPush(&processor->stack, var1);
                StackPush(&processor->stack, var2);
                break;

            case CMD_JE:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                processor->ip += sizeof(char);

                if (var1 == var2)
                    processor->ip = *(int *) ((char *) processor->code + processor->ip);
                else
                    processor->ip += sizeof(int);

                StackPush(&processor->stack, var1);
                StackPush(&processor->stack, var2);
                break;

            case CMD_JNE:
                var2 = StackPop(&processor->stack);
                var1 = StackPop(&processor->stack);

                processor->ip += sizeof(char);

                if (var1 != var2)
                    processor->ip = *(int *) ((char *) processor->code + processor->ip);
                else
                    processor->ip += sizeof(int);

                StackPush(&processor->stack, var1);
                StackPush(&processor->stack, var2);
                break;

            case CMD_CALL:
                processor->ip += sizeof(char);
                StackPush(&processor->stack, (data_t)(processor->ip + sizeof(int)));

                processor->ip = *(int*)((char*)processor->code + processor->ip);
                break;

            case CMD_RET:
                processor->ip = StackPop(&processor->stack);
                break;

            case CMD_HLT:
                return 0;

            default:
                printf("In Function Processor: Default case is reached\n");
                return PROCESSOR_DEFAULT_CASE;
        }
    }

    return PROCESSOR_DEFAULT_CASE;
}