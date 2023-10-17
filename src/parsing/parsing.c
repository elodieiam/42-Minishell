/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/17 12:24:51 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handlepar(t_token *token, int *parenth)
{
	if (token->type == T_OPPAR )
		(*parenth)++;
	if (token->type == T_CLPAR)
		(*parenth)--;
	return ;
	
}
void	handlewords(t_data *data, t_token *current_tok)
{
	int	squotes;
	int	dquotes;

	squotes = 0;
	dquotes = 0;
	
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
		handlewords(data, current_tok);
		current_tok = current_tok->next;
	}
	return (0);
}