/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:04:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/23 19:22:01 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*handlepar(t_data *data)
{
	t_token	*curr;
	t_node	*tree;

	curr = data->tokens;
	if (!curr && curr->type != T_OPPAR)
		return (NULL);
	while (curr)
	{
		curr = curr->next;
	}
	return (tree);
}
