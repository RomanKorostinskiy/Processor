#include "Processor.h"

int ReadFromFile (Text *text)
{
	text->input_file_name = (char*) calloc(20, sizeof(char));
	printf("Enter name of input file: "); //TODO починить ввод файла с клавиатуры
	scanf("%s", text->input_file_name);

	FILE *fp = NULL;

	fp = fopen(text->input_file_name, "r");

	if (fp == NULL)
		return WRONG_INPUT_FILE;

	text->size_of_input_file = GetSizeOfFile(fp); //TODO автоматически определять размер файла

	text->buffer = (char*) calloc(text->size_of_input_file, sizeof(char));

	int sz = fread(text->buffer, sizeof(char), text->size_of_input_file, fp);
	text->buffer[sz] = EOF;

	fclose(fp);

	return 0;
}

FILE* OpenFileWrite ()
{
	char *file_name = (char*) calloc(20, sizeof(char));

	printf("Enter name of output file: "); //TODO починить ввод файла с клавиатуры
	scanf("%s", file_name);

	FILE *fp = fopen(file_name, "w");

	if (!fp)
		return NULL;

	return fp;
}

size_t GetSizeOfFile (FILE* fp)
{
	fseek(fp, 0, SEEK_END); //переводим указатель на конец файла
	int size_of_file = ftell(fp); //считаем количество байт на которое указатель отстоит от начала файла
	rewind(fp); //возвращает указатель на начало файла

	return size_of_file + 1;
}

void WriteToFile (Text *text, FILE *fp)
{
	assert(fp != NULL);

	static int counter = 1;

	fseek(fp, 0, SEEK_END);

	for (size_t i = 0; i < text->num_of_strings; i++)
		fprintf(fp, "%s\n", text->strings[i].ptr);
	counter++;
}

void CloseFile (FILE *fp)
{
	assert(fp != NULL);

	fclose(fp);
}

void MakeString (Text *text)
{
	text->num_of_strings = DeleteSpaces(text->buffer);

	text->strings = (String*) calloc(text->num_of_strings, 
		sizeof(String));

	char *string_ptr = text->buffer;
	char *newline_pos = NULL;
	int string_ctr = 0;

	while ((newline_pos = strchr (string_ptr, '\n')) || 
		(newline_pos = strchr (string_ptr, EOF)))
	{
		if((long unsigned int)string_ctr >= text->num_of_strings) 
		{
			*newline_pos = '\0';
			break;
		}
		*newline_pos = '\0';

		text->strings[string_ctr].ptr = string_ptr;
		text->strings[string_ctr].len = newline_pos - string_ptr + 1;

		string_ptr = newline_pos + 1;

		string_ctr++;
	}
}

size_t DeleteSpaces (char *array)
{	
	int i, j;
	int is_newline = true;
	int is_space = true;
	int num_of_strings = 0;
	for (i = 0, j = 0; array[i] != EOF; i++)
	{
		if (array[i] == '\n')
		{
			if(!is_newline && array[i + 1] != '\0')
			{
				array[j++] = array[i];
				is_newline = true;
				num_of_strings++;
			}
			else
				continue;
		}

		else if (isspace(array[i]))
		{
			if (!is_space && !is_newline)
			{
				array[j++] = array[i];
				is_space = true;
			}
			else
				continue;
		}
		else if (array[i] != '\0')
		{
			array[j++] = array[i];
			is_newline = false;
			is_space = false;
		}
	}
	array[j] = '\n';
	return num_of_strings + 1;
}

void MemoryFree (Text *text)
{
	free(text->buffer);
	free(text->strings);
}