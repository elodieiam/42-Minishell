/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:29:51 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/03 19:30:13 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	middle_pipe(t_data *data, t_node *node, int fd[2], int nread_fd)
{
	int	child_pid;

	child_pid = -1;
	if (pipe(fd) == -1)
		return (exit_line(data, errnl(UNKNOWN_ERR, "pipe failed")));
	child_pid = fork();
	if (child_pid == -1)
		return (exit_line(data, errnl(UNKNOWN_ERR, "fork failed")));
	if (!child_pid)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(exit_all(data, g_err_code));
		close(fd[1]);
		if (dup2(nread_fd, STDIN_FILENO) == -1)
			exit(exit_all(data, g_err_code));
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
	if (child_pid == -1)
		return (exit_line(data, errnl(UNKNOWN_ERR, "fork failed")));
	if (!child_pid)
	{
		if (dup2(nread_fd, STDIN_FILENO) == -1)
			exit(exit_all(data, g_err_code));
		close(nread_fd);
		exec(data, node);
		exit(exit_all(data, g_err_code));
	}
	close(nread_fd);
	if (!append_pid(&(data->pidlist), child_pid))
		return (exit_line(data, errnl(UNKNOWN_ERR, "malloc failed")));
	return (0);
}

int	is_lastpipecmd(t_node *node)
{
	t_node	*curr;

	if (node->parent->operand->l_child == node)
		return (0);
	curr = node;
	while (curr->parent && curr->parent->operand->optype == T_PIPE)
	{
		if (curr->parent->operand->l_child == curr)
			return (0);
		curr = curr->parent;
	}
	return (1);
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
	else if (is_lastpipecmd(node))
		return (last_pipe(data, node, nread_fd));
	else if (node->arguments)
		return (middle_pipe(data, node, fd, nread_fd));
	return (0);
}

int	exec_pipe(t_data *data, t_node *node)
{
	int			fd[2];
	int			nread_fd;
	int			pid;
	int			childval;

	fd[0] = -1;
	fd[1] = -1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	nread_fd = dup(STDIN_FILENO);
	if (nread_fd == -1)
			return (exit_line(data, errnl(UNKNOWN_ERR, "minishell: dup failed")));
	if (pipex(data, node, fd, nread_fd) == UNKNOWN_ERR)
		return (g_err_code);
	pid = pop_pid(&(data->pidlist));
	while (pid != -1)
	{
		if (waitpid(pid, &childval, 0) == -1)
			return (exit_line(data, errnl(255, "minishell: waitpid failed")));
		if (WIFSIGNALED(childval))
			childval = WIFEXITED(childval) + 128;
		if (childval == 130)
			write(2, "\n", 1);
		pid = pop_pid(&(data->pidlist));
	}
	return (g_err_code);
}
