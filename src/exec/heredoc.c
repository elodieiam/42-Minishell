/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/17 22:45:49 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			return (free(line), UNKNOWN_ERR);
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
	// if (!node->redirects->heredoc_name)
	node->redirects->fd = open(node->redirects->heredoc_name,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->redirects->fd == (-1))
		return (PERM_ERR);
	pid = fork();
	if (pid == (-1))
		return (UNKNOWN_ERR);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		return (signal(SIGINT, ft_handler_heredoc)
			, child_process(node, data, node->redirects->file));
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
	if (node->redirects && node->redirects->rdtype == T_DOPCHEV)
		g_err_code = open_heredoc(data, node);
	else if (!node->arguments)
	{
		open_heredocs(data, node->operand->l_child);
		open_heredocs(data, node->operand->r_child);
	}
	return (0);
}
