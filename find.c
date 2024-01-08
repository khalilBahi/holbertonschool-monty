#include "monty.h"
/**
 * fun_found - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @line_number: line number
 * @sp_line:  storage sp_line
 */
void fun_found(char *opcode, char *value, int line_number, int sp_line)
{
	int i, kk;

	instruction_t opc_list[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"add", _add},
		{"swap", _swap},
		{"nop", _nop},
		{NULL, NULL}};

	for (kk = 1, i = 0; opc_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, opc_list[i].opcode) == 0)
		{
			check_op(opc_list[i].f, opcode, value, line_number, sp_line);
			kk = 0;
		}
	}

	if (kk == 1)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}
