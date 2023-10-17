/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/17 18:24:28 by tsaint-p         ###   ########.fr       */
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

t_node	*init_cmd_node(t_token *cmd_tok, int malloc_size)
{
	t_node	*res;

	res = new_node(1);
	if (!res)
		return (NULL);
	node->
}

t_node	*handlecommand(t_data *data, t_token *current_tok)
{
	t_token	*curr;
	int		malloc_size;
	t_node	*cmd_node;

	curr = current_tok;
	malloc_size = 0;
	while (curr && curr->type != T_PIPE && curr->type != T_OR && curr->type != T_AND)
	{
		if (curr->type == T_WORD)
			malloc_size++;
		if (curr->type > 6 && curr->type < 11)
		{
			if (curr->next && curr->next->type != T_WORD)
				//exit (syntax error near curr->string)
			curr = curr->next;
		}
		curr = curr->next;
	}
	return (init_cmd_node(current_tok, malloc_size));
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
