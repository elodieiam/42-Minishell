/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:23:43 by taospa            #+#    #+#             */
/*   Updated: 2023/10/19 13:33:46 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*init_cmd_node(t_token *cmd_tok, int malloc_size)
{
	t_node	*res;
	t_token	*curr;
	int		arg_cpt;

	arg_cpt = 0;
	res = new_node(1);
	if (!res)
		return (NULL);
	res->command->arguments = malloc(malloc_size * sizeof(char *));
	if (!res->command->arguments)
		return (NULL);
	curr = cmd_tok;
	while (curr && curr->type != T_PIPE && curr->type != T_OR && curr->type != T_AND)
	{
		if (curr->type == T_WORD)
		{
			res->command->arguments[arg_cpt++] = ft_strdup(curr->string);
		}
		else if (curr->type > 6 && curr->type < 11)
		{
			rdlist_add_back(&(res->command->redirects), new_rd((curr->type), curr->next->string));
			curr = curr->next;
		}
		curr = curr->next;
	}
	res->command->arguments[arg_cpt] = NULL;
	return (res);
}

t_node	*handlecommand(t_data *data, t_token *current_tok)
{
	t_token	*curr;
	int		malloc_size;

	curr = current_tok;
	malloc_size = 0;
	while (curr && curr->type != T_PIPE && curr->type != T_OR && curr->type != T_AND)
	{
		if (curr->type == T_WORD)
			malloc_size++;
		else if (curr->type > 6 && curr->type < 11)
		{
			if (!curr->next || (curr->next && curr->next->type != T_WORD))
				exit_line(data, errnl(2, "syntax error, no file after redirection"));
			curr = curr->next;
		}
		curr = curr->next;
	}
	return (init_cmd_node(current_tok, malloc_size));
}


