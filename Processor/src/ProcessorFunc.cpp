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
    file_ptr = fopen(file_name, "rb");

    size_t sizeof_code = GetSizeOfFile (file_ptr) / sizeof(data_t);
    *code = (data_t*) calloc(sizeof_code, sizeof(data_t));

    if (fread (*code, sizeof(data_t), sizeof_code, file_ptr) != sizeof_code)
    {
        printf("In Function GetCode: Can't read code from file");
        return CANT_READ_FROM_FILE;
    }

    return sizeof_code;
}

//data_t Processor (Stack* stack, Text* input)
//{
//    data_t param;
//
//    // for (size_t i = 0; i < input->num_of_strings; i++)
//    // {
//    // 	sscanf(input->strings[i].ptr, "%s %d", command, &param);
//
//    // 	//push
//    // 	if(strcmp("push", command) == 0)
//    // 	{
//    // 		StackPush(stack, param);
//
//    // 		printf("\npush: %d\n", stack->data[stack->size - 1]);
//    // 	}
//    // 	//pop
//    // 	if(strcmp("pop", command) == 0)
//    // 	{
//    // 		StackPop(stack);
//    // 	}
//    // 	//add
//    // 	if(strcmp("add", command) == 0)
//    // 	{
//    // 		StackPush(stack, StackPop(stack) + StackPop(stack));
//
//    // 		printf("\nadd: %d\n", stack->data[stack->size - 1]);
//    // 	}
//    // 	//sub
//    // 	if(strcmp("sub", command) == 0)
//    // 	{
//    // 		StackPush(stack, (-1)*(StackPop(stack) - StackPop(stack))); //TODO проблемка с порядком вычетания: StackPush(stack, (-1)*(StackPop(stack) - StackPop(stack)));
//
//    // 		printf("\nsub: %d\n", stack->data[stack->size - 1]);
//    // 	}
//    // 	//mul
//    // 	if(strcmp("mul", command) == 0)
//    // 	{
//    // 		StackPush(stack, StackPop(stack) * StackPop(stack));
//
//    // 		printf("\nmul: %d\n", stack->data[stack->size - 1]);
//    // 	}
//    // 	//out
//    // 	if(strcmp("out", command) == 0)
//    // 	{
//    // 		return StackPop(stack);
//    // 	}
//    // }
//
//    return 0;
//}