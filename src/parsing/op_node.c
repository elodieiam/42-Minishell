/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:12:40 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/03 16:34:06 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*handleoperator(t_data *data)
{
	t_node	*op_node;

	if (!data->tokens->next || \
		(data->tokens->next->type > 2 && data->tokens->next->type < 7))
		return (syntax_error(data, data->tokens->next), NULL);
	op_node = new_node(0);
	if (!op_node || !op_node->operand)
	{
		if (op_node)
			free(op_node);
		return (NULL);
	}
	op_node->operand->optype = data->tokens->type;
	data->tokens = freengonextok(data->tokens);
	op_node->operand->r_child = handlecommand(data);
	if (!op_node->operand->r_child)
		return (NULL);
	op_node->operand->r_child->parent = op_node;
	return (op_node);
}

int	add_pipenode(t_data *data, t_node *pipe_node, t_node **tree)
{
	t_node	*current_node;

	if (!data->tree || !data->tree->operand || data->tree->subshell
		|| (data->tree->operand && data->tree->operand->optype == T_PIPE))
		return (add_nodeontop(pipe_node, tree), 0);
	current_node = *tree;
	while (current_node->operand->r_child && \
	!current_node->operand->r_child->arguments && \
	!current_node->operand->r_child->subshell)
		current_node = current_node->operand->r_child;
	pipe_node->operand->l_child = current_node->operand->r_child;
	current_node->operand->r_child = pipe_node;
	return (0);
}

int	handlepipe(t_data *data, t_node **tree)
{
	t_node	*pipe_node;

	if (!data->tokens->next || \
		(data->tokens->next->type > 2 && data->tokens->next->type < 7))
		return (syntax_error(data, data->tokens->next));
	pipe_node = new_node(0);
	if (!pipe_node)
		return (exit_line(data, UNKNOWN_ERR));
	pipe_node->operand->optype = data->tokens->type;
	data->tokens = freengonextok(data->tokens);
	pipe_node->operand->r_child = handlecommand(data);
	if (!pipe_node->operand->r_child)
		return (free(pipe_node->operand), free(pipe_node), g_err_code);
	pipe_node->operand->r_child->parent = pipe_node;
	return (add_pipenode(data, pipe_node, tree));
}
