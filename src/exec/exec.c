/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/12 17:31:32 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	srch_builtin(t_data *data, t_node *node)
{
	if (!node || !node->arguments)
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

int	exec_command(t_data *data, t_node *node)
{
	if (!export_lastarg(data, node) && !srch_builtin(data, node))
		g_err_code = execute(data, node);
	return (g_err_code);
}

int	exec_or(t_data *data, t_node *tree)
{
	if (exec(data, tree->operand->l_child))
		return (exec(data, tree->operand->r_child));
	return (g_err_code);
}

int	exec_and(t_data *data, t_node *tree)
{
	if (!exec(data, tree->operand->l_child))
		return (exec(data, tree->operand->r_child));
	return (g_err_code);
}

int	exec(t_data *data, t_node *node)
{
	if (!node)
		return (g_err_code);
	if (node->arguments)
		g_err_code = exec_command(data, node);
	else
	{
		if (node->operand->optype == T_OR)
			g_err_code = exec_or(data, node);
		if (node->operand->optype == T_AND)
			g_err_code = exec_and(data, node);
		if (node->operand->optype == T_PIPE)
			g_err_code = exec_pipe(data, node);
	}
	return (g_err_code);
}
