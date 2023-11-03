/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:38:44 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/03 13:51:53 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->is_command)
	{
		free_args(&(node->command->arguments));
		free_rdlist(&(node->command->redirects));
		free(node->command);
		free(node);
	}
	else
	{
		free_node(node->operand->r_child);
		free_node(node->operand->l_child);
		free(node->operand);
		free(node);
	}
	return (1);
}

void	free_tree(t_data *data)
{
	if (!data->tree)
		return ;
	free_node(data->tree);
	data->tree = NULL;
}

t_node	*new_node(int is_command)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->is_command = is_command;
	if (is_command)
	{
		node->operand = NULL;
		node->command = malloc(sizeof(t_command));
		if (!node->command)
			return (NULL);
		node->command->arguments = NULL;
		node->command->redirects = NULL;
		return (node);
	}
	node->command = NULL;
	node->operand = malloc(sizeof(t_operand));
	if (!node->operand)
		return (NULL);
	node->operand->l_child = NULL;
	node->operand->r_child = NULL;
	node->operand->optype = 0;
	node->subshell = 0;
	return (node);
}
