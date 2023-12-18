/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdlist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:27:32 by taospa            #+#    #+#             */
/*   Updated: 2023/12/18 12:28:42 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_rdlist	*new_rd(t_toktype rd_type, char *file)
{
	t_rdlist	*new_rd;

	new_rd = malloc(sizeof(t_rdlist));
	if (!new_rd)
		return (NULL);
	new_rd->next = NULL;
	new_rd->file = ft_strdup(file);
	if (!new_rd->file)
		return (free(new_rd->file), free(new_rd), NULL);
	new_rd->rdtype = rd_type;
	new_rd->heredoc_name = NULL;
	new_rd->fd = -1;
	return (new_rd);
}

void	rdlist_add_back(t_rdlist **list, t_rdlist *new_rd)
{
	t_rdlist	*curr;

	if (!list)
		return ;
	if (!*list)
		*list = new_rd;
	else
	{
		curr = *list;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = new_rd;
		new_rd->next = NULL;
	}
}

void	free_rdlist(t_rdlist **list)
{
	t_rdlist	*next_rd;

	if (!list || !*list)
		return ;
	while (*list)
	{
		next_rd = (*list)->next;
		free((*list)->file);
		if ((*list)->heredoc_name)
			free((*list)->heredoc_name);
		free(*list);
		*list = next_rd;
	}
	*list = NULL;
}
