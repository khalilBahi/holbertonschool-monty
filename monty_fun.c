#include "monty.h"
/**
 * check_op - Calls the required function
 * @func: Pointer to the function that is about to be called
 * @op: string representing the opcode
 * @value: string representing a numeric value
 * @line_number: line numeber for the instruction
 * @sp_line: sp_line specifier. If 0 Nodes will be entered as a stack
 */
void check_op(op_cmd cmd, char *op, char *value, int line_number, int sp_line)
{
	stack_t *node;
	int i, val;

	val = 1;
	if (strcmp(op, "push") == 0)
	{
		if (value != NULL && value[0] == '-')
		{
			value += 1;
			val = -1;
		}
		if (value == NULL)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
		for (i = 0; value[i] != '\0'; i++)
		{
			if (isdigit(value[i]) == 0)
			{
				fprintf(stderr, "L%d: usage: push integer\n", line_number);
				exit(EXIT_FAILURE);
			}
		}
		node = create_node(atoi(value) * val);
		if (sp_line == 0)
			cmd(&node, line_number);
		if (sp_line == 1)
			add_node(&node);
	}
	else
		cmd(&head, line_number);
}

/**
 * add_to_stack - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @line_number:unuseful variable in this function.
 */
void _push(stack_t **new_node, __attribute__((unused)) unsigned int line_number)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}

/**
 * print_all - Adds a node to the stack.
 * @stack: Pointer to a pointer to top node of the stack.
 * @line_number: line number of  the opcode.
 */
void _pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	(void)line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
/**
 * print_one - Prints the top node of the stack.
 * @stack: Pointer to a pointer to top node of the stack.
 * @line_number: the line number of of the opcode.
 */
void _pint(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}
/**
 * remove_top - removes the top element of the stack.
 * @stack: Pointer to a pointer to top node of the stack.
 * @line_number:  the line number of of the opcode.
 */
void _pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * swap_nodes - Swaps the top two elements of the stack.
 * @stack: Pointer to a pointer  to top node of the stack.
 * @line_number:  the line number of of the opcode.
 */
void _swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
}
/**
 * add_nodes - Add node the top two elements of the stack.
 * @stack: Pointer to a pointer  to top node of the stack.
 * @line_number:  the line number of of the opcode.
 */
void _add(stack_t **stack, unsigned int line_number)
{
	int sum;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack) = (*stack)->next;
	sum = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * do_nothing - Does nothing.
 * @stack: unuseful variable in this function.
 * @line_number: unuseful variable in this function.
 */
void _nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
