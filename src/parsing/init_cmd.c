/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:23:43 by taospa            #+#    #+#             */
/*   Updated: 2023/10/19 22:35:38 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*init_cmd_node(t_token **tokens, int malloc_size)
{
	t_node	*res;
	int		arg_cpt;

	arg_cpt = 0;
	res = new_node(1);
	printf("newnode = %p\n", res);
	if (!res)
		return (NULL);
	res->command->arguments = malloc(malloc_size * sizeof(char *));
	if (!res->command->arguments)
		return (NULL);
	while ((*tokens) && (*tokens)->type != T_PIPE && (*tokens)->type != T_OR && (*tokens)->type != T_AND)
	{
		if ((*tokens)->type == T_WORD)
			res->command->arguments[arg_cpt++] = ft_strdup((*tokens)->string);
		else if ((*tokens)->type > 6 && (*tokens)->type < 11)
		{
			rdlist_add_back(&(res->command->redirects),
				new_rd(((*tokens)->type), (*tokens)->next->string));
			(*tokens) = freengonextok((*tokens));
		}
		(*tokens) = freengonextok((*tokens));
	}
	res->command->arguments[arg_cpt] = NULL;
	return (res);
}

t_node	*handlecommand(t_data *data)
{
	t_token	*curr;
	int		malloc_size;

	curr = data->tokens;
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
	return (init_cmd_node(&(data->tokens), ++malloc_size));
}


