/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdlist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:27:32 by taospa            #+#    #+#             */
/*   Updated: 2023/11/30 15:59:19 by tsaint-p         ###   ########.fr       */
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
		return (free(new_rd), NULL);
	new_rd->rdtype = rd_type;
	return (new_rd);
}

void	rdlist_add_back(t_rdlist **list, t_rdlist *new_rd)
{
	if (!list)
		return ;
	if (!*list)
		*list = new_rd;
	else
	{
		while ((*list)->next)
		{
			*list = (*list)->next;
		}
		(*list)->next = new_rd;
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
		free(*list);
		*list = next_rd;
	}
	*list = NULL;
}
