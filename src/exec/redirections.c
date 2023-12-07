/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/07 15:41:16 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	only_red_exec(t_node *node)
{
	if (node->command->redirects->rdtype == 9
		&& node->command->redirects->files[0])
		if (exec_simple_heredoc(node->command->redirects->files[0]))
			return (1);
	return (0);
}

int	handle_redirections(t_data *data, t_node *node)
{
	(void)data;
	if (node->command->redirects && !node->command->arguments)
		if (only_red_exec(node))
			return (1);
	// else if (node->command->redirects && node->command->arguments)
	// 	if (red_and_command_exec(data, node))
	// 		return (1);
	return (0);
}
