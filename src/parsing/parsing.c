/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/19 13:33:42 by tsaint-p         ###   ########.fr       */
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

int	parse(t_data *data)
{
	int		parenth;
	t_token	*current_tok;
	
	parenth = 0;
	current_tok = data->tokens;
	while (current_tok)
	{
		handlepar(current_tok, &parenth);
		if (current_tok->type == T_WORD)
			handlecommand(data, current_tok);
		current_tok = current_tok->next;
	}
	if (parenth)
		return (printf("wrong parenthesis patern\n"));
	return (0);
}
