#include "monty.h"
#include <stdio.h>

/**
 * read_file - reads a bytecode file and runs commands
 * @filename: pathname to file
 * @stack: pointer to the top of the stack
 *
 */
void read_file(char *filename, stack_t **stack)
{
	char *buffer = NULL;
	char *line;
	size_t len = 0;
	int line_count = 1;
	instruct_func s;
	int check;
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: can't open file %s\n", filename);
		error_exit(stack);
	}
	while (getline(&buffer, &len, file) != -1)
	{
		line = parse_line(buffer);
		if (line == NULL || line[0] == '#')
		{
			line_count++;
			continue;
		}
		s = get_op_func(line);
		if (s == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_count, line);
		}
		s(stack, line_count);
		line_count++;
	}
	free(buffer);
	check = fclose(file);
	if (check == -1)
		exit(-1);
}

/**
 * get_op_func - check opcode and retturns the correct function
 * @str: the opcode
 *
 * Return: function or NULL on failure
 */
instruct_func get_op_func(char *str)
{
	int i;

	instruction_t instruct[] = {
		{"push", _push},
		{"pall", _pall},
		{NULL, NULL}
	};

	i = 0;
	while (instruct[i].f != NULL && strcmp(instruct[i].opcode, str) != 0)
		i++;
	return (instruct[i].f);
}

/**
 * parse_line - parses a line for an opcode and arguments
 * @line: the line to be parsed
 *
 * Return: the opcode or NULL on failure
 */
char *parse_line(char *line)
{
	char *op_code;

	op_code = strtok(line, "\n");
	if (op_code == NULL)
		return (NULL);
	return (op_code);
}
