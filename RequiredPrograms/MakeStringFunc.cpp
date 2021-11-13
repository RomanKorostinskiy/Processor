#include "../include/Assembler.h"

int GetFileNames (Text *text, int argc, char* argv[])
{
    if (argc == 3)
    {
        text->input_file_name = argv[1];
        text->output_file_name = argv[2];

        return 0;
    }
    else
        return 1;
}

int ReadFromFile (Text *text)
{

	FILE *fp = nullptr;

	fp = fopen(text->input_file_name, "r");

	if (fp == nullptr)
    {
        printf("In Function ReadFromFile: Wrong input file");
        return WRONG_INPUT_FILE;
    }

	size_t size_of_file = GetSizeOfFile(fp);

	text->buffer = (char*) calloc(size_of_file, sizeof(char));

	size_t sz = fread(text->buffer, sizeof(char), size_of_file, fp);
	text->buffer[sz] = EOF;

	fclose(fp);

	return 0;
}

FILE* OpenFileWrite (Text* text)
{

	FILE *fp = fopen(text->output_file_name, "w");

	if (!fp)
		return nullptr;

	return fp;
}

size_t GetSizeOfFile (FILE* fp)
{
	fseek(fp, 0, SEEK_END); //переводим указатель на конец файла
	size_t size_of_file = ftell(fp); //считаем количество байт на которое указатель отстоит от начала файла
	rewind(fp); //возвращает указатель на начало файла

	return size_of_file + 1;
}

void WriteToFile (Text *text, FILE *fp)
{
	assert(fp != nullptr);

	fseek(fp, 0, SEEK_END);

	for (size_t i = 0; i < text->num_of_strings; i++)
		fprintf(fp, "%s\n", text->strings[i].ptr);
}

void CloseFile (FILE *fp)
{
	assert(fp != nullptr);

	fclose(fp);
}

void MakeString (Text *text)
{
	text->num_of_strings = DeleteSpaces(text->buffer);

	text->strings = (String*) calloc(text->num_of_strings, 
		sizeof(String));

	char *string_ptr = text->buffer;
	char *newline_pos = nullptr;
	int string_ctr = 0;

	while ((newline_pos = strchr (string_ptr, '\n')) ||
		(newline_pos = strchr (string_ptr, EOF)))
	{
		*newline_pos = '\0';

		text->strings[string_ctr].ptr = string_ptr;
		text->strings[string_ctr].len = newline_pos - string_ptr + 1;

		string_ptr = newline_pos + 1;

		string_ctr++;

        if((long unsigned int)string_ctr >= text->num_of_strings)
        {
            *newline_pos = '\0';
            break;
        }
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
			if(!is_newline && array[i + 1] != '\n' && array[i + 1] != EOF)
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
		else
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