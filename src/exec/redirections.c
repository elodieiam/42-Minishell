/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/02 13:42:55 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_infile(t_data *data, t_rdlist *rd)
{
	if (rd->rdtype == T_DOPCHEV)
	{
		if (access(rd->heredoc_name, F_OK) == -1)
			return (exit_line(data, errnl(NOTFOUND_ERR, "not found")));
		if (access(rd->heredoc_name, R_OK) == -1)
			return (exit_line(data, errnl(PERM_ERR, "access denied")));
		if (rd->fd >= 0)
			close(rd->fd);
		data->fds.curr[0] = open(rd->heredoc_name, O_RDONLY);
	}
	else if (rd->rdtype == T_OPCHEV)
	{
		if (access(rd->file, F_OK) == -1)
			return (exit_line(data, errnl(NOTFOUND_ERR, "not found")));
		if (access(rd->file, R_OK) == -1)
			return (exit_line(data, errnl(PERM_ERR, "access denied")));
		data->fds.curr[0] = open(rd->file, O_RDONLY);
	}
	return (0);
}

int	open_outfile(t_data *data, t_rdlist *rd)
{
	if (rd->rdtype == T_CLCHEV)
	{
		if (data->fds.curr[1] != STDOUT_FILENO)
			close(data->fds.curr[1]);
		if (access(rd->file, F_OK) == -1)
			data->fds.curr[1] = open(rd->file, O_WRONLY | O_CREAT, 0644);
		else
		{
			if (access(rd->file, W_OK) == -1)
				return (exit_line(data, errnl(PERM_ERR, "access denied")));
			data->fds.curr[1] = open(rd->file, O_WRONLY);
		}
	}
	else if (rd->rdtype == T_DCLCHEV)
	{
		if (access(rd->file, F_OK) == -1)
			data->fds.curr[1] = open(rd->file, 578, 0644);
		else
		{
			if (access(rd->file, W_OK) == -1)
				return (exit_line(data, errnl(PERM_ERR, "access denied")));
			data->fds.curr[1] = open(rd->file, O_WRONLY | O_APPEND);
		}
	}
	return (0);
}

int	open_redirect(t_data *data, t_rdlist *rd)
{
	if (rd->rdtype == T_DOPCHEV || rd->rdtype == T_OPCHEV)
	{
		if (open_infile(data, rd))
			return (g_err_code);
	}
	else if (rd->rdtype == T_DCLCHEV || rd->rdtype == T_CLCHEV)
	{
		if (data->fds.curr[1] != STDOUT_FILENO)
		{
			close(data->fds.curr[1]);
		}
		if (open_outfile(data, rd))
			return (g_err_code);
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
		if (open_redirect(data, curr_rd))
			return (g_err_code);
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
