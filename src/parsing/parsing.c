/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/22 15:06:21 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_word(t_data *data, t_token *toklist)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (toklist->string[i])
	{
		if (quote && quote == toklist->string[i])
			quote = 0;
		else if (toklist->string[i] == 39 || toklist->string[i] == 34)
			quote = toklist->string[i];
		i++;
	}
	if (quote)
	{
		toklist = toklist->next;
		return (syntax_error(data, toklist));
	}
	return (0);
}

int	add_nodeontop(t_node *node, t_node **head)
{
	if (!head || !node)
		return (g_err_code);
	if (*head && !(node->arguments) && node->operand && !node->operand->l_child)
	{
		(*head)->parent = node;
		node->operand->l_child = *head;
	}
	*head = node;
	return (0);
}

int	parse(t_data *data, t_node **tree)
{
	while (data->tokens && data->tokens->type != T_CLPAR)
	{
		if (data->tokens->type == T_WORD || data->tokens->type == T_OPPAR
			|| (data->tokens->type >= 7 && data->tokens->type <= 10))
		{
			if (add_nodeontop(handlecommand(data), tree))
				return (g_err_code);
		}
		else if (data->tokens->type == T_OR || data->tokens->type == T_AND)
		{
			if (!*tree)
				return (syntax_error(data, data->tokens));
			if (add_nodeontop(handleoperator(data), tree))
				return (g_err_code);
		}
		else if (data->tokens->type == T_PIPE)
		{
			if (!*tree)
				return (syntax_error(data, data->tokens));
			if (handlepipe(data, tree))
				return (g_err_code);
		}
	}
	return (0);
}
