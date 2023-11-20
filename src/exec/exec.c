/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/20 18:48:22 by tsaint-p         ###   ########.fr       */
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
		data->err_code = exec_echo(node);
		return (1);
	}
	if (!ft_strncmp(node->command->arguments[0], "export", 7))
	{
		data->err_code = exec_export(data, node);
		return (1);
	}
	return (0);
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
