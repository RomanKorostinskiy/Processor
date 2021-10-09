#include "Processor.h"

int Calc (Stack* stack, Text* input);

int main()
{
	Text input_text = {};

	Stack stack = {};

	ReadFromFile(&input_text);

	MakeString(&input_text);

	FILE* output_file = OpenFileWrite(); //////

	if (!output_file)
	{
		printf("Output file ERROR\n"); //////
		return 1;
	}

	WriteToFile(&input_text, output_file);

	CloseFile(output_file);

	StackCtor(&stack);

	printf("\nResult: %d\n", Calc(&stack, &input_text));

	StackDtor(&stack);

	return 0;

	MemoryFree(&input_text); //TODO убивать структуру

}

//-------- Calc functions ---------

data_t Calc (Stack* stack, Text* input)
{
	char command[5];
	data_t param;

	for (size_t i = 0; i < input->num_of_strings; i++)
	{
		sscanf(input->strings[i].ptr, "%s %d", command, &param);

		//push
		if(strcmp("push", command) == 0)
		{
			StackPush(stack, param);

			printf("\npush: %d\n", stack->data[stack->size - 1]);
		}
		//pop
		if(strcmp("pop", command) == 0)
		{
			StackPop(stack);
		}
		//add
		if(strcmp("add", command) == 0)
		{
			StackPush(stack, StackPop(stack) + StackPop(stack));

			printf("\nadd: %d\n", stack->data[stack->size - 1]);
		}
		//sub
		if(strcmp("sub", command) == 0)
		{
			StackPush(stack, (-1)*(StackPop(stack) - StackPop(stack))); //TODO проблемка с порядком вычетания: StackPush(stack, (-1)*(StackPop(stack) - StackPop(stack)));

			printf("\nsub: %d\n", stack->data[stack->size - 1]);
		}
		//mul
		if(strcmp("mul", command) == 0)
		{
			StackPush(stack, StackPop(stack) * StackPop(stack));

			printf("\nmul: %d\n", stack->data[stack->size - 1]);
		}
		//out
		if(strcmp("out", command) == 0)
		{
			return StackPop(stack);
		}
	}

	return 0;
}