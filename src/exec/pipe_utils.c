/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:49:17 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/04 18:20:57 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	child_pipe(t_data *data, t_node *node)
{
	if (!node->operand)
	{
		if (expand(data, node, data->env->envtab))
			return (g_err_code);
		if (node->arguments && export_lastarg(data, node))
			return (g_err_code);
		if (node->redirects)
			if (handle_redirections(data, node))
				return (g_err_code);
		if (node->arguments && node->arguments[0] && !srch_builtin(data, node))
			g_err_code = child_exec(data, node);
		if (data->tree && node->redirects)
			reset_rds(&(data->fds), node);
	}
	else if (node->subshell)
		g_err_code = exec_command(data, node);
	return (g_err_code);
}

int	wait_pipes(t_data *data)
{
	int	pid;
	int	print;
	int	childval;

	pid = pop_pid(&(data->pidlist));
	print = 1;
	while (pid != -1)
	{
		if (waitpid(pid, &childval, WUNTRACED) == -1)
			return (exit_line(data, errnl(255, "minishell: waitpid failed")));
		if (print && handle_child_sigs(childval))
			print = 0;
		g_err_code = WEXITSTATUS(childval);
		pid = pop_pid(&(data->pidlist));
	}
	return (g_err_code);
}
