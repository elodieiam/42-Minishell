/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:38:44 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/29 17:22:40 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->arguments)
		free_args(&(node->arguments));
	if (node->redirects)
		free_rdlist(&(node->redirects));
	if (node->operand)
	{
		if (node->operand->r_child)
			free_node(node->operand->r_child);
		if (node->operand->l_child)
			free_node(node->operand->l_child);
		free (node->operand);
	}
	free(node);
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
	node->arguments = NULL;
	node->redirects = NULL;
	node->parent = NULL;
	node->subshell = 0;
	if (is_command)
	{
		node->operand = NULL;
		return (node);
	}
	node->operand = malloc(sizeof(t_operand));
	if (!node->operand)
		return (free(node), NULL);
	node->operand->l_child = NULL;
	node->operand->r_child = NULL;
	node->operand->optype = 0;
	return (node);
}
