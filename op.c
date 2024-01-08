#include "monty.h"

/**
 * handle_file - opens a file and read
 * @file_name: the file namepath
 */
void handle_file(char *file_name)
{
	FILE *fd = fopen(file_name, "r");
	int line_number = 1, sp_line = 0;
	char *line = NULL;
	size_t len = 0;

	if (fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file_name);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fd) != -1)
	{
		sp_line = split(line, line_number, sp_line);
		line_number++;
	}

	free(line);
	fclose(fd);
}

/**
 * split - Separates each line into tokens to determine
 * which function to call
 * @line: line from the file
 * @line_number: line number
 * @sp_line:  storage sp_line. If 0 Nodes will be entered as a stack.
 * Return: sp_line
 */
int split(char *line, int line_number, int sp_line)
{
	char *opcode, *value;
	const char *delim = "$\n ";

	if (line == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	opcode = strtok(line, delim);
	if (opcode == NULL)
		return (sp_line);

	value = strtok(NULL, delim);

	fun_found(opcode, value, line_number, sp_line);

	return (sp_line);
}
