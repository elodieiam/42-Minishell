/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:29:51 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/19 11:54:15 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	middle_pipe(t_data *data, t_node *node, int fd[2], int nread_fd)
{
	int	child_pid;

	child_pid = -1;
	pipe(fd); //protect ?
	child_pid = fork();
	// if (fd == -1) free
	if (!child_pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(nread_fd, STDIN_FILENO);
		close(nread_fd);
		exec(data, node);
		exit(exit_all(data, g_err_code));
	}
	close(nread_fd);
	nread_fd = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	if (!append_pid(&(data->pidlist), child_pid))
		return (exit_line(data, errnl(UNKNOWN_ERR, "malloc failed")));
	return (0);
}

int	last_pipe(t_data *data, t_node *node, int nread_fd)
{
	int	child_pid;

	child_pid = -1;
	child_pid = fork();
	// if (fd == -1) free
	if (!child_pid)
	{
		dup2(nread_fd, STDIN_FILENO);
		close(nread_fd);
		exec(data, node);
		exit(exit_all(data, g_err_code));
	}
	close(nread_fd);
	if (!append_pid(&(data->pidlist), child_pid))
		return (exit_line(data, errnl(UNKNOWN_ERR, "malloc failed")));
	return (0);
}

int	pipex(t_data *data, t_node *node, int fd[2], int nread_fd)
{
	if (!node || (!node->arguments && !node->operand))
		return (UNKNOWN_ERR);
	if (node->operand && node->operand->optype == T_PIPE)
	{
		pipex(data, node->operand->l_child, fd, nread_fd);
		pipex(data, node->operand->r_child, fd, nread_fd);
	}
	else if (node->parent && \
		(node->parent->operand->l_child == node || node->parent->parent))
	{
		g_err_code = middle_pipe(data, node, fd, nread_fd);
		if (g_err_code)
			return (g_err_code);
	}
	else if (node->arguments)
	{
		g_err_code = last_pipe(data, node, nread_fd);
		if (g_err_code)
			return (g_err_code);
	}
	return (0);
}

int	exec_pipe(t_data *data, t_node *node)
{
	int			fd[2];
	int			nread_fd;
	int			pid;

	fd[0] = -1;
	fd[1] = -1;
	signal(SIGQUIT, sig_handler_child);
	signal(SIGINT, sig_handler_child);
	nread_fd = dup(STDIN_FILENO);
	pipex(data, node, fd, nread_fd);
	pid = pop_pid(&(data->pidlist));
	while (pid != -1)
	{
		waitpid(pid, NULL, 0);
		// wait(0);
		pid = pop_pid(&(data->pidlist));
	}
	return (g_err_code);
}
