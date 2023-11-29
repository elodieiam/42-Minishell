/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/29 16:28:23 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	srch_builtin(t_data *data, t_node *node)
{
	if (!node || !node->is_command || !node->command->arguments)
		return (0);
	if (!ft_strncmp(node->command->arguments[0], "exit", 5))
		return (exec_exit(data, node));
	else if (!ft_strncmp(node->command->arguments[0], "echo", 5))
		g_err_code = exec_echo(node);
	else if (!ft_strncmp(node->command->arguments[0], "export", 7))
		g_err_code = exec_export(data, node->command->arguments);
	else if (!ft_strncmp(node->command->arguments[0], "env", 4))
		g_err_code = exec_env(data);
	else if (!ft_strncmp(node->command->arguments[0], "cd", 3))
		g_err_code = exec_cd(data, node);
	else if (!ft_strncmp(node->command->arguments[0], "pwd", 4))
		g_err_code = exec_pwd(data, node);
	else if (!ft_strncmp(node->command->arguments[0], "unset", 6))
		g_err_code = exec_unset(data, node->command->arguments);
	else
		return (0);
	return (1);
}

int	exec_command(t_data *data, t_node *node)
{
	if (!srch_builtin(data, node))
		g_err_code = execute(data, node);
	return (g_err_code);
}

int	exec(t_data *data)
{
	if (!data->tree)
		return (g_err_code);
	if (data->tree->is_command)
		g_err_code = exec_command(data, data->tree);
	return (g_err_code);
}
