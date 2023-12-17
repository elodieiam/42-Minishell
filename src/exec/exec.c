/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/17 17:50:04 by tsaint-p         ###   ########.fr       */
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

int	exec_command(t_data *data, t_node *node)
{
	if (node->arguments && export_lastarg(data, node))
		return (g_err_code);
	if (node->redirects)
		handle_redirections(data, node);
	if (node->arguments && node->arguments[0] && !srch_builtin(data, node))
		g_err_code = execute(data, node);
	if (node->redirects)
		reset_rds(&(data->fds), node);
	return (g_err_code);
}

int	exec_or(t_data *data, t_node *tree)
{
	if (!handle_redirections(data, tree) && exec(data, tree->operand->l_child))
		exec(data, tree->operand->r_child);
	if (tree->redirects)
		reset_rds(&(data->fds), tree);
	return (g_err_code);
}

int	exec_and(t_data *data, t_node *tree)
{
	//protect handle redir
	if (tree->redirects)
		handle_redirections(data, tree);
	if (!exec(data, tree->operand->l_child))
		exec(data, tree->operand->r_child);
	if (tree->redirects)
		reset_rds(&(data->fds), tree);
	return (g_err_code);
}

int	exec_subshell(t_data *data, t_node *node)
{
	int	pid;
	int	childval;

	pid = 0;
	childval = 0;
	if (node->subshell)
		pid = fork();
	if (!pid)
	{
		if (node->arguments || (!node->operand && node->redirects))
			g_err_code = exec_command(data, node);
		else
		{
			if (node->operand->optype == T_OR)
				g_err_code = exec_or(data, node);
			if (node->operand->optype == T_AND)
				g_err_code = exec_and(data, node);
			//implement fd old_fd for pipe ?
			if (node->operand->optype == T_PIPE)
				g_err_code = exec_pipe(data, node);
		}
		exit_all(data, g_err_code);
	}
	else if (waitpid(pid, &childval, 0) == -1)
		exit_line(data, errnl(UNKNOWN_ERR, "minishell: waitpid failed"));
	return (WEXITSTATUS(childval));
}

int	exec(t_data *data, t_node *node)
{
	if (!node)
		return (g_err_code);
	if (node->subshell)
		g_err_code = exec_subshell(data, node);
	else if (node->arguments || (!node->arguments && node->redirects))
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
