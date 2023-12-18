/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/18 12:45:42 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	child_process(t_data *data, t_rdlist *rd)
{
	char	*line;
	char	*res;

	line = NULL;
	res = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_err_code == 130)
			break ;
		if (!line)
			return (exit_heredoc(rd), exit_all(data, g_err_code));
		if (!ft_strncmp(line, rd->file, ft_strlen(rd->file) + 1))
		{
			free (line);
			break ;
		}
		res = ft_strjoin(line, "\n");
		if (!res)
			return (free(line), UNKNOWN_ERR);
		write(rd->fd, res, ft_strlen(res));
		free (line);
		free (res);
	}
	return (close(rd->fd), exit_all(data, g_err_code));
}

int	open_heredoc(t_data *data, t_rdlist *rd)
{
	int		pid;
	int		childval;

	childval = 0;
	rd->heredoc_name = get_heredoc_name();
	// dprintf(2, "hd name : %s\n", node->redirects-)
	// if (!rd->heredoc_name)
	rd->fd = open(rd->heredoc_name,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (rd->fd == (-1))
		return (PERM_ERR);
	pid = fork();
	if (pid == (-1))
		return (UNKNOWN_ERR);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		return (signal(SIGINT, ft_handler_heredoc)
			, child_process(data, rd));
	waitpid(pid, &childval, 0);
	if (WEXITSTATUS(childval) == 130)
	{
		close(rd->fd);
		return (unlink(rd->heredoc_name), SIGINT_ERR);
	}
	return (0);
}

int	open_heredocs(t_data *data, t_node *node)
{
	t_rdlist	*curr_rd;

	curr_rd = node->redirects;
	while (curr_rd)
	{
		if (curr_rd->rdtype == T_DOPCHEV)
			g_err_code = open_heredoc(data, curr_rd);
		curr_rd = curr_rd->next;
	}
	if (!node->arguments)
	{
		open_heredocs(data, node->operand->l_child);
		open_heredocs(data, node->operand->r_child);
	}
	return (0);
}
