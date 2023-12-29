/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/29 14:01:01 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	child_process(t_data *data, t_rdlist *rd)
{
	char	*line;
	char	*res;

	line = NULL;
	res = NULL;
	signal(SIGINT, ft_handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line && g_err_code != 130)
			return (exit_heredoc(rd, data, g_err_code));
		if (g_err_code == 130 || \
			!ft_strncmp(line, rd->file, ft_strlen(rd->file) + 1))
			break ;
		res = ft_strjoin(line, "\n");
		free (line);
		if (!res)
			return (close(rd->fd), UNKNOWN_ERR);
		line = apply_exp(res, data->env->envtab);
		if (!line)
			return (close(rd->fd), UNKNOWN_ERR);
		write(rd->fd, line, ft_strlen(line));
		free (line);
	}
	return (free(line), close(rd->fd), exit_all(data, g_err_code));
}

int	open_heredoc(t_data *data, t_rdlist *rd)
{
	int		pid;
	int		childval;

	rd->heredoc_name = get_heredoc_name(data);
	if (!rd->heredoc_name)
		return (g_err_code);
	rd->fd = open(rd->heredoc_name, 578, 0644);
	if (rd->fd == (-1))
		return (PERM_ERR);
	pid = fork();
	if (pid == (-1))
		return (UNKNOWN_ERR);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		return (child_process(data, rd));
	if (waitpid(pid, &childval, 0) == -1)
		return (close(rd->fd), UNKNOWN_ERR);
	if (WEXITSTATUS(childval) == 130)
	{
		close(rd->fd);
		if (unlink(rd->heredoc_name) == -1)
			return (UNKNOWN_ERR);
		return (cherr_code(SIGINT_ERR));
	}
	return (0);
}

int	open_heredocs(t_data *data, t_node *node)
{
	t_rdlist	*curr_rd;

	if (!node)
		return (g_err_code);
	curr_rd = node->redirects;
	while (curr_rd)
	{
		if (curr_rd->rdtype == T_DOPCHEV && open_heredoc(data, curr_rd))
			return (exit_line(data, g_err_code));
		close(curr_rd->fd);
		curr_rd = curr_rd->next;
	}
	if (node->operand)
	{
		if (open_heredocs(data, node->operand->l_child))
			return (g_err_code);
		if (open_heredocs(data, node->operand->r_child))
			return (g_err_code);
	}
	return (0);
}
