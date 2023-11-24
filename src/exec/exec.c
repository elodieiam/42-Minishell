/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/22 00:40:16 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	srch_builtin(t_data *data, t_node *node)
{
	if (!node || !node->is_command || !node->command->arguments)
		return (0);
	else if (!ft_strncmp(node->command->arguments[0], "exit", 5))
		return (exec_exit(data, node));
	else if (!ft_strncmp(node->command->arguments[0], "echo", 5))
		data->err_code = exec_echo(node);
	else if (!ft_strncmp(node->command->arguments[0], "export", 7))
		data->err_code = exec_export(data, node->command->arguments);
	else if (!ft_strncmp(node->command->arguments[0], "env", 4))
		data->err_code = exec_env(data);
	/*else if (!ft_strncmp(node->command->arguments[0], "cd", 3))
		data->err_code = exec_cd(data, node);*/
	else
		return (0);
	return (1);
}

int	exec_command(t_data *data, t_node *node)
{
	if (!srch_builtin(data, node))
		data->err_code = execute(data, node);
	return (data->err_code);
}

int	exec(t_data *data)
{
	if (!data->tree)
		return (data->err_code);
	if (data->tree->is_command)
		data->err_code = exec_command(data, data->tree);
	return (data->err_code);
}
