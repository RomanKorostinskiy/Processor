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
        printf("In Function GetSizeOfFile: fp is nullptr");
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
        printf("In Function GetCode: Can't open file");
        return CANT_OPEN_FILE;
    }

    processor->sizeof_code = GetSizeOfFile (file_ptr);
    processor->code = (void*) calloc(processor->sizeof_code, sizeof(char*));

    if (fread (processor->code, sizeof(char), processor->sizeof_code, file_ptr) != processor->sizeof_code)
    {
        printf("In Function GetCode: Can't read code from file");
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
        switch (*((char*)processor->code + processor->ip))
        {
            case CMD_PUSH:
                StackPush (&processor->stack,
                           *(int*)((char*)processor->code + processor->ip + sizeof(char)));
                processor->ip += sizeof(char);
                processor->ip += sizeof(int);
                break;

            case CMD_POP:
                StackPop(&processor->stack); //TODO регистры
                processor->ip += sizeof(char);
                break;

            case CMD_ADD:
                StackPush(&processor->stack,
                          StackPop(&processor->stack) + StackPop(&processor->stack));
                processor->ip += sizeof(char);
                break;

            case CMD_SUB:
                var1 = StackPop(&processor->stack);
                var2 = StackPop(&processor->stack);

                StackPush(&processor->stack, var2 - var1);
                processor->ip += sizeof(char);
                break;

            case CMD_MUL:
                StackPush(&processor->stack,
                          StackPop(&processor->stack) * StackPop(&processor->stack));
                processor->ip += sizeof(char);
                break;

            case CMD_DIV:
                var1 = StackPop(&processor->stack);
                var2 = StackPop(&processor->stack);

                if (var1 == 0)
                {
                    printf("Сan't divide by zero");
                    return WRONG_DATA;
                }

                StackPush(&processor->stack, var2 / var1);
                processor->ip += sizeof(char);
                break;

            case CMD_OUT:
                printf("\n%d\n", StackPop(&processor->stack));
                processor->ip += sizeof(char);
                break;

            case CMD_IN:
                scanf("%d", &var1);
                StackPush(&processor->stack, var1);
                processor->ip += sizeof(char);
                break;

            case CMD_HLT:
                return 0;

            default:
                printf("In Function Processor: Default case is reached");
                return PROCESSOR_DEFAULT_CASE;
        }
    }
    printf("In Function Processor: Default case is reached");
    return PROCESSOR_DEFAULT_CASE;
}