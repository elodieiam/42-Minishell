/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:04:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/19 15:24:49 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_rdlist	*get_rds(t_data *data, t_rdlist *res)
{
	t_rdlist	*rd;

	res = NULL;
	while (data->tokens && data->tokens->type > 6 && data->tokens->type < 11)
	{
		if (!data->tokens->next || data->tokens->next->type != T_WORD)
			return (free_rdlist(&res), NULL);
		rd = new_rd((data->tokens->type), data->tokens->next->string);
		if (!rd)
			return (free_rdlist(&res), NULL);
		rdlist_add_back(&(res), rd);
		data->tokens = freengonextok(data->tokens);
		data->tokens = freengonextok(data->tokens);
	}
	return (res);
}

t_node	*handlepar(t_data *data)
{
	t_rdlist	*rds;
	int			err;

	rds = NULL;
	err = 0;
	data->tokens = freengonextok(data->tokens);
	data->tmp_tree = NULL;
	while (data->tokens && data->tokens->type != T_CLPAR)
	{
		if (data->tokens->type == T_WORD || data->tokens->type == T_OPPAR)
			err = add_nodeontop(handlecommand(data), &(data->tmp_tree));
		else if (data->tokens->type > 4 && data->tokens->type < 7)
			err = add_nodeontop(handleoperator(data), &(data->tmp_tree));
		else if (data->tokens->type == T_PIPE)
			err = handlepipe(data);
		if (err)
			return (cherr_code(err), NULL);
	}
	if (data->tokens->type == T_CLPAR)
		data->tokens = freengonextok(data->tokens);
	if (data->tmp_tree)
		data->tmp_tree->subshell = 1;
	if (data->tokens && data->tokens->type > 6 && data->tokens->type < 11)
		data->tmp_tree->redirects = get_rds(data, rds);
	return (data->tmp_tree);
}
