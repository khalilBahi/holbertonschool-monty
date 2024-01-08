#include "monty.h"
/**
 * fun_found - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @line_number: line number
 * @sp_line:  storage sp_line. If 0 Nodes will be entered as a stack
 */
void fun_found(char *opcode, char *value, int line_number, int sp_line)
{
	int i;
	int kk;

	// Initialize the array of function names and pointers to functions
	instruction_t op_list[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"add", _add},
		{"swap", _swap},
		{"nop", _nop},
		{NULL, NULL}};
	// Loop through the function list and find the matching function
	for (kk = 1, i = 0; op_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, op_list[i].opcode) == 0)
		{
			// Call the function and pass the required parameters
			check_op(op_list[i].f, opcode, value, line_number, sp_line);
			kk = 0;
		}
	}

	// If no matching function is found, print an error message and exit the program
	if (kk == 1)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}
