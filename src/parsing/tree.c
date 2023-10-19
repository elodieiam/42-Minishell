/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:38:44 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/19 11:55:12 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*new_node(int is_command)
{
	t_node	*node;

	node = malloc (sizeof(t_node));
	if (!node)
		return (NULL);
	if (is_command)
	{
		node->is_command = 1;
		node->command = malloc(sizeof(t_command));
		if (!node->command)
			return (NULL);
		node->command->arguments = NULL;
		node->command->redirects = NULL;
	}
	else
	{
		node->is_command = 0;
		node->operand = malloc(sizeof(t_command));
		if (!node->operand)
			return (NULL);
		node->operand->l_child = NULL;
		node->operand->r_child = NULL;
		node->operand->optype = 0;
	}
	return (node);
}

void	print_tree(t_node *node, int depth)
{
	if (!node)
		return ;
	while (depth--)
		printf("\t");
	if (node->is_command && node->command->arguments)
		printf("%s\n", node->command->arguments[0]);
	else if (!node->is_command)
	{
		print_tree(node->operand->r_child, depth + 1);
		printf("%s\n", tta(node->operand->optype));
		print_tree(node->operand->l_child, depth + 1);
	}
}
