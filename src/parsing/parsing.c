/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/28 13:14:27 by tsaint-p         ###   ########.fr       */
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

void	add_nodeontop(t_node *node, t_node **head)
{
	if (!head || !node)
		return ;
	if (!(node->is_command) && node->operand)
		node->operand->l_child = *head;
	*head = node;
}

//TODO: check return value of malloc using functions
int	parse(t_data *data)
{
	while (data->tokens && data->tokens->type != T_CLPAR)
	{
		if (data->tokens->type == T_WORD || data->tokens->type == T_OPPAR)
			add_nodeontop(handlecommand(data), &(data->tree));
		else if (data->tokens->type > 4 && data->tokens->type < 7)
			add_nodeontop(handleoperator(data), &(data->tree));
		else if (data->tokens->type == T_PIPE)
			handlepipe(data);
		else
			data->tokens = freengonextok(data->tokens);
	}
	return (0);
}
