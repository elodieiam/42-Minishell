/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/15 14:06:39 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirections(t_data *data, t_node *node)
{
	t_rdlist	*curr_rd;

	curr_rd = node->redirects;
	while (curr_rd)
	{
		if (curr_rd->rdtype == T_DOPCHEV)
		{
			close(node->redirects->fd);
			if (exec_child_heredoc(data, node))
				return (1);
			unlink(node->redirects->heredoc_name);
		}
		curr_rd = curr_rd->next;
	}
	return (0);
}
