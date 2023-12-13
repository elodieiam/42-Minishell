/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/13 14:41:11 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_heredoc(t_data *data, t_node *node)
{
	pid_t	pid;
	int		childval;

	childval = 0;
	pid = fork();
	if (pid == -1)
		return (exit_line(data, errnl(-1, "minishell: fork failed")));
	signal(SIGINT, SIG_IGN);
	if (!pid)
		if (child_exec(data, node))
			return (UNKNOWN_ERR);
	if (waitpid(pid, &childval, 0) == -1)
		return (exit_line(data, errnl(-1, "minishell: waitpid failed")));
	if (handle_child_sigs(childval))
		return (WTERMSIG(childval) + 128);
	return (WEXITSTATUS(childval));
}

int	exec_child_heredoc(t_data *data, t_node *node)
{
	pid_t	pid;
	int		fd;

	fd = open(node->redirects->heredoc_name, O_RDONLY);
	if (fd == (-1))
		return (1);
	pid = fork();
	if (pid == -1)
		return (exit_line(data, errnl(-1, "minishell: fork failed")));
	if (pid == 0)
	{
		dup2(fd, 0);
		close(fd);
		if (!export_lastarg(data, node) && !srch_builtin(data, node))
			g_err_code = execute_heredoc(data, node);
		return (exit_all(data, g_err_code));
	}
	waitpid(pid, NULL, 0);
	return (close(fd), unlink(node->redirects->heredoc_name), 0);
}

int	child_process(t_node *node, t_data *data, char *lim)
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
			return (exit_heredoc(node), exit_all(data, g_err_code));
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			free (line);
			break ;
		}
		res = ft_strjoin(line, "\n");
		if (!res)
			return (free(line), MALLOC_ERR);
		write(node->redirects->fd, res, ft_strlen(res));
		free (line);
		free (res);
	}
	return (close(node->redirects->fd), exit_all(data, g_err_code));
}

int	open_heredoc(t_data *data, t_node *node)
{
	int		pid;
	int		childval;

	childval = 0;
	node->redirects->heredoc_name = get_heredoc_name();
	node->redirects->fd = open(node->redirects->heredoc_name,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->redirects->fd == (-1))
		return (UNKNOWN_ERR);
	pid = fork();
	if (pid == (-1))
		return (UNKNOWN_ERR);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, ft_handler_heredoc);
		return (child_process(node, data, node->redirects->files[0]));
	}
	waitpid(pid, &childval, 0);
	if (WEXITSTATUS(childval) == 130)
	{
		close(node->redirects->fd);
		return (unlink(node->redirects->heredoc_name), SIGINT_ERR);
	}
	return (0);
}

int	open_heredocs(t_data *data, t_node *node)
{
	if (node->arguments && node->redirects
		&& node->redirects->rdtype == 9)
		g_err_code = open_heredoc(data, node);
	else if (!node->arguments)
	{
		open_heredocs(data, node->operand->l_child);
		open_heredocs(data, node->operand->r_child);
	}
	return (0);
}
