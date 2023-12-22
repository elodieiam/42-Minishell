/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/22 12:16:49 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_command(t_data *data, t_node *node)
{
	if (node->arguments && export_lastarg(data, node))
		return (g_err_code);
	if (expand(node, data->env->envtab))
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

//protec handle redir
int	exec_and(t_data *data, t_node *tree)
{
	if (tree->redirects)
		handle_redirections(data, tree);
	if (!exec(data, tree->operand->l_child))
		exec(data, tree->operand->r_child);
	if (tree->redirects)
		reset_rds(&(data->fds), tree);
	return (g_err_code);
}

//implement fd old_fd for pipe ?
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
