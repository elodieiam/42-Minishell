/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:12:40 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/12 13:12:12 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: protect handlecommand
t_node	*handleoperator(t_data *data)
{
	t_node	*op_node;

	if (!data || !data->tokens)
		return (NULL);
	if (!data->tokens->next || (data->tokens->next->type > 3
			&& data->tokens->next->type < 8))
	{
		exit_line(data, errnl(2,
				"syntax error : wrong argument after operator"));
		return (NULL);
	}
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
	return (op_node);
}

int	add_pipenode(t_data *data, t_node *pipe_node)
{
	t_node	*current_node;

	if (!data->tree || data->tree->arguments || data->tree->subshell
		|| (data->tree->operand && data->tree->operand->optype == T_PIPE))
		return (add_nodeontop(pipe_node, &(data->tree)), 0);
	current_node = data->tree;
	while (current_node->operand->r_child && \
	!current_node->operand->r_child->arguments && \
	!current_node->operand->r_child->subshell)
		current_node = current_node->operand->r_child;
	pipe_node->operand->l_child = current_node->operand->r_child;
	current_node->operand->r_child = pipe_node;
	return (0);
}

//TODO: protect handlecommand
int	handlepipe(t_data *data)
{
	t_node	*pipe_node;

	if (!data->tokens->next)
		return (exit_line(data, errnl(2, \
			"minishell: syntax error near token 'newline'")));
	if (data->tokens->next->type > 3)
		return (exit_line(data, errnl(2, \
			"minishell: syntax error near token '|'")));
	pipe_node = new_node(0);
	if (!pipe_node || !pipe_node->operand)
	{
		if (pipe_node)
			free(pipe_node);
		return (MALLOC_ERR);
	}
	pipe_node->operand->optype = data->tokens->type;
	data->tokens = freengonextok(data->tokens);
	pipe_node->operand->r_child = handlecommand(data);
	if (!pipe_node->operand->r_child)
	{
		free(pipe_node->operand);
		return (free(pipe_node), MALLOC_ERR);
	}
	return (add_pipenode(data, pipe_node));
}
