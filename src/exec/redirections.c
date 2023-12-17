/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/17 17:43:26 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_redirects(t_data *data, t_rdlist *rd, t_node *node)
{
	if (rd->rdtype == T_DOPCHEV)
	{
		if (data->fds.curr[0] != STDIN_FILENO)
			close(data->fds.curr[0]);
		if (access(rd->heredoc_name, F_OK) == -1)
			return (exit_line(data, errnl(NOTFOUND_ERR, "not found")));
		if (access(rd->heredoc_name, R_OK) == -1)
			return (exit_line(data, errnl(PERM_ERR, "access denied")));
		if (rd->fd >= 0)
			close(rd->fd);
		data->fds.curr[0] = open(rd->heredoc_name, O_RDONLY);
		signal(SIGINT, SIG_IGN);
	}
	else if (rd->rdtype == T_OPCHEV)
	{
		if (data->fds.curr[0] != 0)
			close(data->fds.curr[0]);
		if (access(node->redirects->file, F_OK) == -1)
			return (exit_line(data, errnl(NOTFOUND_ERR, "not found")));
		if (access(node->redirects->file, R_OK) == -1)
			return (exit_line(data, errnl(PERM_ERR, "access denied")));
		data->fds.curr[0] = open(node->redirects->file, O_RDONLY);
	}
	else if (rd->rdtype == T_CLCHEV)
	{
		if (data->fds.curr[1] != 1)
			close(data->fds.curr[1]);
		if (access(node->redirects->file, F_OK) == -1)
			data->fds.curr[1] = open(node->redirects->file, O_WRONLY | O_CREAT, 0644);
		else
		{
			if (access(node->redirects->file, W_OK) == -1)
				return (exit_line(data, errnl(PERM_ERR, "access denied")));
			data->fds.curr[1] = open(node->redirects->file, O_WRONLY);
		}
	}
	return (0);
}

// TODO: put ret_val in g_err_code
int	handle_redirections(t_data *data, t_node *node)
{
	t_rdlist	*curr_rd;

	curr_rd = node->redirects;
	while (curr_rd)
	{
		open_redirects(data, curr_rd, node);
		curr_rd = curr_rd->next;
	}
	if (data->fds.curr[0] != STDIN_FILENO)
	{
		data->fds.std[0] = dup(STDIN_FILENO);
		if (dup2(data->fds.curr[0], STDIN_FILENO) == -1)
			return (exit_line(data, UNKNOWN_ERR));
		close(data->fds.curr[0]);
	}
	if (data->fds.curr[1] != STDOUT_FILENO)
	{
		data->fds.std[1] = dup(STDOUT_FILENO);
		if (dup2(data->fds.curr[1], STDOUT_FILENO) == -1)
			return (exit_line(data, UNKNOWN_ERR));
		close(data->fds.curr[1]);
	}
	return (0);
}

//TODO: protect calls
int	reset_rds(t_fds *fds, t_node *node)
{
	t_rdlist	*curr_rd;

	curr_rd = NULL;
	if (node)
		curr_rd = node->redirects;
	while (curr_rd)
	{
		if (curr_rd->rdtype == T_DOPCHEV && curr_rd->heredoc_name)
			unlink(curr_rd->heredoc_name);
		curr_rd = curr_rd->next;
	}
	if (fds->curr[0] != STDIN_FILENO)
	{
		dup2(fds->std[0], STDIN_FILENO);
		close(fds->std[0]);
		fds->curr[0] = STDIN_FILENO;
	}
	if (fds->curr[1] != STDOUT_FILENO)
	{
		dup2(fds->std[1], STDOUT_FILENO);
		close(fds->std[1]);
		fds->curr[1] = STDOUT_FILENO;
	}
	return (0);
}
