/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/12 12:20:18 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirections(t_data *data, t_node *node)
{
	if (!node->redirects && node->arguments)
		return (2);
	if (node->redirects && !node->arguments)
	{
		close(node->redirects->fd);
		unlink(node->redirects->heredoc_name);
		return (0);
	}
	else if (node->redirects && node->arguments)
	{
		close(node->redirects->fd);
		if (exec_child_heredoc(data, node))
			return (1);
	}
	return (0);
}
