/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/23 19:01:18 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handlepar(t_token *token, int *parenth)
{
	if (token->type == T_OPPAR )
		(*parenth)++;
	if (token->type == T_CLPAR)
		(*parenth)--;
	return ;
}

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

void	add_nodeontop(t_node *node, t_data *data)
{
	if (!data || !node)
		return ;
	if (!(node->is_command) && node->operand)
		node->operand->l_child = data->tree;
	data->tree = node;
}

int	parse(t_data *data)
{
	int		parenth;
	
	parenth = 0;
	while (data->tokens)
	{
		handlepar(data->tokens, &parenth);
		if (data->tokens->type == T_WORD || data->tokens->type == T_OPPAR)
			add_nodeontop(handlecommand(data), data);
		else if (data->tokens->type > 3 && data->tokens->type < 7)
			add_nodeontop(handleoperator(data), data);
		else
			data->tokens = freengonextok(data->tokens);
	}
	if (parenth)
		return (exit_line(data, errnl(2, "wrong parenthesis patern\n")));
	return (0);
}
