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

size_t GetCode (data_t** code, const char* file_name)
{
    FILE* file_ptr = nullptr;

    if ((file_ptr = fopen(file_name, "rb")) == nullptr)
    {
        printf("In Function GetCode: Can't open file");
        return CANT_OPEN_FILE;
    }

    size_t sizeof_code = GetSizeOfFile (file_ptr) / sizeof(data_t);
    *code = (data_t*) calloc(sizeof_code, sizeof(data_t));

    if (fread (*code, sizeof(data_t), sizeof_code, file_ptr) != sizeof_code)
    {
        printf("In Function GetCode: Can't read code from file");
        return CANT_READ_FROM_FILE;
    }

    fclose(file_ptr);

    return sizeof_code;
}

int Processor (Processor_t* processor)
{
    while(processor->ip < processor->sizeof_code)
    {
        int pop1 = 0;
        int pop2 = 0;
        switch (processor->code[processor->ip])
        {
            case CMD_PUSH:
                StackPush (&processor->stack, processor->code[++processor->ip]);
                processor->ip++;
                break;

            case CMD_POP:
                StackPop(&processor->stack); //TODO регистры
                processor->ip++;
                break;

            case CMD_ADD:
                StackPush(&processor->stack,
                          StackPop(&processor->stack) + StackPop(&processor->stack));
                processor->ip++;
                break;

            case CMD_SUB:
                pop1 = StackPop(&processor->stack);
                pop2 = StackPop(&processor->stack);

                StackPush(&processor->stack, pop2 - pop1);
                processor->ip++;
                break;

            case CMD_MUL:
                StackPush(&processor->stack,
                          StackPop(&processor->stack) * StackPop(&processor->stack));
                processor->ip++;
                break;

            case CMD_DIV:
                pop1 = StackPop(&processor->stack);
                pop2 = StackPop(&processor->stack);

                if (pop1 == 0)
                {
                    printf("Сan't divide by zero");
                    return WRONG_DATA;
                }

                StackPush(&processor->stack, pop2 / pop1);
                processor->ip++;
                break;

            case CMD_OUT:
                printf("\n%d\n", StackPop(&processor->stack));
                processor->ip++;
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