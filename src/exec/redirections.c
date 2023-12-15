/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/15 23:33:51 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include <minishell.h>

int	open_redirects(t_data *data, t_rdlist *rd, t_node *node, int fd[2])
{
	if (rd->rdtype == T_DOPCHEV)
	{
		close(node->redirects->fd);
		// if (exec_child_heredoc(data, node))
		// 	return (1);
		// unlink(node->redirects->heredoc_name);
	}
	else if (rd->rdtype == T_OPCHEV)
	{
		if (fd[0] != 0)
			close(fd[0]);
		if (access(node->redirects->file, F_OK) == -1)
			return (exit_line(data, errnl(NOTFOUND_ERR, "not found")));
		if (access(node->redirects->file, R_OK) == -1)
			return (exit_line(data, errnl(PERM_ERR, "access denied")));
		fd[0] = open(node->redirects->file, O_RDONLY);
	}
	else if (rd->rdtype == T_CLCHEV)
	{
		if (fd[1] != 1)
			close(fd[1]);
		if (access(node->redirects->file, F_OK) == -1)
			fd[1] = open(node->redirects->file, O_WRONLY | O_CREAT, 0755);
		else
		{
			if (access(node->redirects->file, W_OK) == -1)
				return (exit_line(data, errnl(PERM_ERR, "access denied")));
			fd[1] = open(node->redirects->file, O_WRONLY);
		}
	}
	return (0);
}

// TODO: put ret_val in g_err_code
int	handle_redirections(t_data *data, t_node *node, int fd[2], int old_fd[2])
{
	t_rdlist	*curr_rd;

	curr_rd = node->redirects;
	while (curr_rd)
	{
		open_redirects(data, curr_rd, node, fd);
		curr_rd = curr_rd->next;
	}
	if (fd[0] != 0)
	{
		old_fd[0] = dup(0);
		if (dup2(fd[0], 0) == -1)
			return (exit_line(data, UNKNOWN_ERR));
		close(fd[0]);
	}
	if (fd[1] != 1)
	{
		old_fd[1] = dup(1);
		if (dup2(fd[1], 1) == -1)
			return (exit_line(data, UNKNOWN_ERR));
		close(fd[1]);
	}
	return (0);
}

int	reset_rds(int fd[2], int old_fd[2])
{
	if (fd[0] != 0)
	{
		dup2(old_fd[0], 0);
		close(old_fd[0]);
	}
	if (fd[1] != 1)
	{
		dup2(old_fd[1], 1);
		close(old_fd[1]);
	}
	return (0);
}
