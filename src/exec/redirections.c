/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/11 14:16:10 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirections(t_data *data, t_node *node)
{
	if (!node->command->redirects && node->command->arguments)
		return (2);
	if (node->command->redirects && !node->command->arguments)
	{
		close(node->command->redirects->fd);
		unlink(node->command->redirects->heredoc_name);
		return (0);
	}
	else if (node->command->redirects && node->command->arguments)
	{
		close(node->command->redirects->fd);
		if (exec_child_heredoc(data, node))
			return (1);
	}
	return (0);
}
