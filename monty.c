#include "monty.h"
stack_t *head = NULL;

/**
 * main - Entry point for Monty program
 * @ac: number of commandline arguments
 * @av: arry of arguments
 * Return:  Aalways 0.
 */
int main(int ac, char **av)
{
	if (ac < 2 || ac > 2)
		err(1);
	open_file(av[1]);
	free_nodes();
	return (0);
}

/**
 * free_nodes - Frees nodes in the stack.
 */
void free_nodes(void)
{
	stack_t *tmp;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/**
 * create_node - Creates a new node.
 * @n: number of node.
 * Return: Upon sucess a pointer to the node. Otherwise NULL.
 */
stack_t *create_node(int n)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
		err(4);
	new->next = NULL;
	new->prev = NULL;
	new->n = n;
	return (new);
}
