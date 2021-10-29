#include "Processor.h"

int GetCode (data_t* code);

data_t Processor (Stack* stack, Text* input);

int main()
{
	Stack stack = {};

	data_t* code = nullptr;

	code = (data_t*) calloc(MAX_SIZE_OF_CODE, sizeof(data_t));

	GetCode (code);

	for (int i = 0; code[i] != 0; i++)
	{
		printf("\n%d", code[i]);
	}

	return 0;

	MemoryFree(&input_text); //TODO убивать структуру
}

//-------- Calc functions ---------

int GetCode (data_t* code)
{
	FILE*  = nullptr;

	code = fopen ("code.bin", "rb");

	if (code == nullptr)
		return CANT_OPEN_FILE;

	size_t sizeof_code = GetSizeOfFile (code);

	fread (code, sizeof(data_t), sizeof_code, code);

	return 0;
}

data_t Processor (Stack* stack, Text* input)
{
	char command[5];
	data_t param;

	// for (size_t i = 0; i < input->num_of_strings; i++)
	// {
	// 	sscanf(input->strings[i].ptr, "%s %d", command, &param);

	// 	//push
	// 	if(strcmp("push", command) == 0)
	// 	{
	// 		StackPush(stack, param);

	// 		printf("\npush: %d\n", stack->data[stack->size - 1]);
	// 	}
	// 	//pop
	// 	if(strcmp("pop", command) == 0)
	// 	{
	// 		StackPop(stack);
	// 	}
	// 	//add
	// 	if(strcmp("add", command) == 0)
	// 	{
	// 		StackPush(stack, StackPop(stack) + StackPop(stack));

	// 		printf("\nadd: %d\n", stack->data[stack->size - 1]);
	// 	}
	// 	//sub
	// 	if(strcmp("sub", command) == 0)
	// 	{
	// 		StackPush(stack, (-1)*(StackPop(stack) - StackPop(stack))); //TODO проблемка с порядком вычетания: StackPush(stack, (-1)*(StackPop(stack) - StackPop(stack)));

	// 		printf("\nsub: %d\n", stack->data[stack->size - 1]);
	// 	}
	// 	//mul
	// 	if(strcmp("mul", command) == 0)
	// 	{
	// 		StackPush(stack, StackPop(stack) * StackPop(stack));

	// 		printf("\nmul: %d\n", stack->data[stack->size - 1]);
	// 	}
	// 	//out
	// 	if(strcmp("out", command) == 0)
	// 	{
	// 		return StackPop(stack);
	// 	}
	// }

	return 0;
}