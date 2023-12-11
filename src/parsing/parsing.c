/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/07 16:57:37 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_quotes(int *squotes, int *dquotes, char caracter)
{
	if (!*dquotes && caracter == 39)
	{
		if (*squotes)
			(*squotes)--;
		else
			(*squotes)++;
	}
	if (!*squotes && caracter == 34)
	{
		if (*dquotes)
			(*dquotes)--;
		else
			(*dquotes)++;
	}
}

int	check_word(char *str)
{
	int	squotes;
	int	dquotes;
	int	i;

	squotes = 0;
	dquotes = 0;
	i = -1;
	while (str[++i])
	{
		check_quotes(&squotes, &dquotes, str[i]);
	}
	return (dquotes + squotes);
}

int	add_nodeontop(t_node *node, t_node **head)
{
	if (!head || !node)
		return (1);
	if (!(node->is_command) && node->operand && !node->operand->l_child)
		node->operand->l_child = *head;
	*head = node;
	return (0);
}

int	parse(t_data *data)
{
	while (data->tokens)
	{
		if (data->tokens->type == 7)
			return (exit_line(data, errnl(2, "syntax error")), 1);
		if (data->tokens->type == T_WORD || data->tokens->type == T_OPPAR
			|| (data->tokens->type >= 8 && data->tokens->type <= 10))
		{
			if (add_nodeontop(handlecommand(data), &(data->tree)))
				return (1);
		}
		else if (data->tokens->type > 4 && data->tokens->type < 7)
		{
			if (add_nodeontop(handleoperator(data), &(data->tree)))
				return (1);
		}
		else if (data->tokens->type == T_PIPE)
			if (handlepipe(data))
				return (1);
	}
	return (0);
}
