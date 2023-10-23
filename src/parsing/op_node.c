/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:12:40 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/23 16:48:25 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node		*handleoperator(t_data *data)
{
	t_node	*op_node;

	if (!data || !data->tokens)
		return (NULL);
	if (!data->tokens->next || data->tokens->next->type > 3)
	{
		exit_line(data, errnl(2,
			"syntax error : wrong argument after operator"));
		return (NULL);
	}
	op_node = new_node(0);
	if (!op_node || !op_node->operand)
		return (NULL);
	op_node->operand->optype = data->tokens->type;
	data->tokens = freengonextok(data->tokens);
	op_node->operand->r_child = handlecommand(data);
	return (op_node);
}
