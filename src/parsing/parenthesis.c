/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:04:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/19 22:56:33 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "parsing.h"
#include <minishell.h>

t_rdlist	*get_rds(t_data *data, t_rdlist *res)
{
	t_rdlist	*rd;

	res = NULL;
	while (data->tokens && data->tokens->type > 6 && data->tokens->type < 11)
	{
		if (!data->tokens->next || data->tokens->next->type != T_WORD)
			return (free_rdlist(&res), syntax_error(data, data->tokens->next), NULL);
		rd = new_rd((data->tokens->type), data->tokens->next->string);
		if (!rd)
			return (cherr_code(UNKNOWN_ERR), free_rdlist(&res), NULL);
		rdlist_add_back(&(res), rd);
		data->tokens = freengonextok(data->tokens);
		data->tokens = freengonextok(data->tokens);
	}
	return (res);
}

int	check_par(t_data *data)
{
	t_token	*curr;

	curr = data->tokens;
	while (curr && curr->type != T_CLPAR)
		curr = curr->next;
	if (!curr)
		return (syntax_error(data, data->tokens));
	if (curr == data->tokens->next)
		return (syntax_error(data, curr));
	return (0);
}

t_node	*handlepar(t_data *data)
{
	t_rdlist	*rds;
	int			err;

	rds = NULL;
	err = 0;
	if (check_par(data))
		return (NULL);
	data->tokens = freengonextok(data->tokens);
	data->tmp_tree = NULL;
	err = parse(data, &(data->tmp_tree));
	if (err)
		return (NULL);
	if (data->tokens->type == T_CLPAR)
		data->tokens = freengonextok(data->tokens);
	if (data->tmp_tree)
		data->tmp_tree->subshell = 1;
	if (data->tokens && data->tokens->type > 6 && data->tokens->type < 11)
	{
		data->tmp_tree->redirects = get_rds(data, rds);
		if (!data->tmp_tree->redirects)
			return (free_node(data->tmp_tree), NULL);
	}
	return (data->tmp_tree);
}
