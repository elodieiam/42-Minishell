/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pidlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:18:10 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/12 19:09:08 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pidlist	*append_pid(t_pidlist **head, int new_pid)
{
	t_pidlist	*res;
	t_pidlist	*curr;

	if (!head)
		return (NULL);
	res = malloc(sizeof(t_pidlist));
	if (!res)
		return (NULL);
	res->pid = new_pid;
	res->next = NULL;
	if (!*head)
	{
		*head = res;
		return (res);
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = res;
	return (res);
}

int	pop_pid(t_pidlist **pidlist_head)
{
	int			res;
	t_pidlist	*tmp;

	if (!pidlist_head || !*pidlist_head)
		return (-1);
	tmp = *pidlist_head;
	*pidlist_head = (*pidlist_head)->next;
	res = tmp->pid;
	free(tmp);
	return (res);
}

void	free_pidlist(t_pidlist **pidlist)
{
	t_pidlist	*tmp;

	if (!pidlist)
		return ;
	tmp = *pidlist;
	while (*pidlist)
	{
		tmp = *pidlist;
		(*pidlist) = (*pidlist)->next;
		free(tmp);
	}
}
