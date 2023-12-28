/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:28:48 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/28 19:02:13 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	srch_builtin(t_data *data, t_node *node)
{
	if (!node || !node->arguments || !node->arguments[0])
		return (0);
	if (!ft_strncmp(node->arguments[0], "exit", 5))
		return (exec_exit(data, node));
	else if (!ft_strncmp(node->arguments[0], "echo", 5))
		g_err_code = exec_echo(node);
	else if (!ft_strncmp(node->arguments[0], "export", 7))
		g_err_code = exec_export(data, node->arguments);
	else if (!ft_strncmp(node->arguments[0], "env", 4))
		g_err_code = exec_env(data);
	else if (!ft_strncmp(node->arguments[0], "cd", 3))
		g_err_code = exec_cd(data, node);
	else if (!ft_strncmp(node->arguments[0], "pwd", 4))
		g_err_code = exec_pwd(data, node);
	else if (!ft_strncmp(node->arguments[0], "unset", 6))
		g_err_code = exec_unset(data, node->arguments);
	else
		return (0);
	return (1);
}
