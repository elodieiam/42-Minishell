/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/03 19:06:19 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	srch_builtin(t_data *data, t_node *node)
{
	size_t	len;

	if (!node || !node->is_command)
		return (0);
	len = ft_strlen(node->command->arguments[0]);
	//printf("arg[0] = |%s|\n", node->command->arguments[0]);
	if (!ft_strncmp(node->command->arguments[0], "exit", 5))
	{
		exec_exit(data, node);
		return (1);
	}
	return (0);
}

int	exec_command(t_data *data, t_node *node)
{
	srch_builtin(data, node);
	// if (!srch_builtin(data, node))
	// 	srch_path(data, node);
	return (0);
}
int	exec(t_data *data)
{
	if (data->tree->is_command)
		exec_command(data, data->tree);	
	return (0);
}