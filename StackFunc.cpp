#include "Processor.h"

const int *UNAVAILABLE_ADR = (int*) 1;
const int START_CAPACITY = 1;

int StackCtor (Stack* stack, int capacity) //TODO аргумент по умолчанию
{

	stack->capacity = capacity;

	stack->data = (data_t*) calloc (capacity, sizeof(data_t)); //TODO проверка возвращаемого значения calloc

	stack->size = 0;

	return 0;
}

int StackDtor (Stack* stack)
{
	if(stack == NULL)
		return STK_IS_NULL_PTR;

	// if(stack->size == -1)
	// 	return STK_DESTROYED; //проверется в error

	memset (stack->data, 0xF0F0F0F0, stack->capacity);
	free(stack->data);

	stack->size = -1;

	stack->data = (data_t*) UNAVAILABLE_ADR;

	return 0;
}

int StackPush (Stack* stack, int value)
{
	if(stack == nullptr)
		return STK_IS_NULL_PTR;

	if (stack->size == stack->capacity)
	{
		stack->data = StackResize(stack);
	}

	stack->data[stack->size++] = value;

	return 0;
}

int StackPop (Stack* stack)
{
	if(!stack) //
		return STK_IS_NULL_PTR;

	if(stack->size == -1)
		return STK_DESTROYED;

	if(stack->size <= 0)
		return 	STK_UNDERFL;

	int value;
	
	if (stack->size * 2 == stack->capacity) //TODO придумать константу вместо 2
	{
		stack->data = StackResize(stack);
	}

	value = stack->data[--stack->size];

	stack->data[stack->size] = 0;

	return value;
}

data_t* StackResize (Stack* stack)
{
	//проверки

	data_t* new_adress = stack->data;

	if (stack->size >= stack->capacity)
	{
		stack->capacity *= 2;

		new_adress = (data_t*) realloc(stack->data, //TODO проверка возвращаемого значения realloc
			(stack->capacity) * sizeof(data_t));
	}
	else if (stack->size * 2 == stack->capacity)
	{
		stack->capacity /= 2;

		new_adress = (data_t*) realloc(stack->data, 
			(stack->capacity) * sizeof(data_t));
	}

	return new_adress;
}

int StackTest__ (Stack *stack)
{
	if(stack == NULL)
		return STK_IS_NULL_PTR;

	FILE* fp = fopen("Test.txt", "w");

	int element = 0;
	int n_of_tests = 10, prblm_sz = 8;

	fprintf(fp, "\n\n\tPush and Pop\n\n");

	for (int i = 0; i < n_of_tests; i++) //Пуш и поп n элементов около size = 0
 	{
		fprintf(fp, "\n#%d\n", i + 1);
		fprintf(fp, "Before Actions | capacity: %d, size: %d;\n", 
			stack->capacity, stack->size);

		StackPush(stack, i);
		fprintf(fp, "After Push     | capacity: %d, size: %d;\n", 
			stack->capacity, stack->size);

		element = StackPop(stack);
		fprintf(fp, "After Pop      | capacity: %d, size: %d;\n", 
			stack->capacity, stack->size);

		fprintf(fp, "Push Elem = %d , Pop Elem = %d\n", i, element);
	}

  	fprintf(fp, "\n\n\tPush and Pop in problem size\n\n");

 	for (int i = 0; i < prblm_sz; i++) //Пуш элементов до problem size
 	{
 		StackPush(stack, i);	
 	}

  	for (int i = 0; i < n_of_tests; i++) //Пуш и поп n элементов около problem size
 	{
		fprintf(fp, "\n#%d\n", i + 1);
 		fprintf(fp, "Before Actions | capacity: %d, size: %d;\n",
  			stack->capacity, stack->size);

 		StackPush(stack, i);
  		fprintf(fp, "After Push     | capacity: %d, size: %d;\n", 
  			stack->capacity, stack->size);

		element = StackPop(stack);
		fprintf(fp, "After Pop      | capacity: %d, size: %d;\n", 
			stack->capacity, stack->size);

		fprintf(fp, "Push Elem = %d , Pop Elem = %d\n", i, element);
 	}


   	fprintf(fp, "\n\n\tPop all\n\n");
 	for (int i = 0; i < n_of_tests; i++) //Поп n элементов подряд
	{
		fprintf(fp, "\n#%d\n", i + 1);
		fprintf(fp, "Before Actions | capacity: %d, size: %d;\n", 
			stack->capacity, stack->size);

		element = StackPop(stack);
		fprintf(fp, "After Pop      | capacity: %d, size: %d;\n", 
			stack->capacity, stack->size);

		fprintf(fp, "Pop Elem = %d\n", element);
 	}

	return 0;
}

int StackError (Stack* stack)
{
	if (!stack)
		return STK_IS_NULL_PTR;

	if (!stack->data)
		return DATA_IS_NULL_PTR;

	if (stack->size == -1)
		return STK_DESTROYED;

	if(stack->size < 0)
		return 	STK_UNDERFL;

	if(stack->size > stack->capacity)
		return 	STK_OVERFL;

	return 0;
}