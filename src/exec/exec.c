/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/07 16:26:08 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	srch_builtin(t_data *data, t_node *node)
{
	if (!node || !node->is_command || !node->command->arguments)
		return (0);
	if (!ft_strncmp(node->command->arguments[0], "exit", 5))
	{
		exec_exit(data, node);
		return (1);
	}
	if (!ft_strncmp(node->command->arguments[0], "echo", 5))
	{
		exec_echo(node);
		return (1);
	}
	return (0);
}

int	exec_command(t_data *data, t_node *node)
{
	int	err_code;

	err_code = srch_builtin(data, node);
	if (!err_code)
		err_code = execute(data, node);
	return (err_code);
}

int	exec(t_data *data)
{
	if (!data->tree)
		return (data->err_code);
	if (data->tree->is_command)
		data->err_code = exec_command(data, data->tree);
	return (data->err_code);
}
