/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdlist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:27:32 by taospa            #+#    #+#             */
/*   Updated: 2023/12/08 18:17:14 by elrichar         ###   ########.fr       */
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
	new_rd->files = malloc(sizeof(char *) * 2);
	if (!new_rd->files)
		return (free(new_rd), NULL);
	new_rd->files[0] = ft_strdup(file);
	new_rd->files[1] = NULL;
	if (!new_rd->files[0])
		return (free(new_rd), free(new_rd->files), NULL);
	new_rd->rdtype = rd_type;
	new_rd->fd = -1;
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
		free_dchartab((*list)->files);
		free(*list);
		*list = next_rd;
	}
	*list = NULL;
}
