/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:27:02 by elrichar          #+#    #+#             */
/*   Updated: 2023/10/18 17:11:06 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		*tokens = current->next;
		free (current->string);
		free(current);
		current = *tokens;
	}
	*tokens = NULL;
}
