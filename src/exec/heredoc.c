/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/11 15:16:18 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_child_heredoc(t_data *data, t_node *node)
{
	pid_t	pid;
	char	*cmd_path;
	int		fd;

	fd = open(node->command->redirects->heredoc_name, O_RDONLY);
	if (fd == (-1))
		return (1);
	cmd_path = NULL;
	pid = fork();
	if (pid == -1)
		return (exit_line(data, errnl(-1, "minishell: fork failed")));
	if (pid == 0)
	{
		dup2(fd, 0);
		close(fd);
		cmd_path = get_cmd_path(data, node->command->arguments[0]);
		check_file(data, cmd_path, node->command->arguments[0]);
		execve(cmd_path, node->command->arguments, data->env->envtab);
		free(cmd_path);
		free(node->command->redirects->heredoc_name);
		return (exit_line(data, errnl(-1, "minishell: execve failed")));
	}
	waitpid(pid, NULL, 0);
	return (close(fd), unlink(node->command->redirects->heredoc_name), 0);
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
		write(node->command->redirects->fd, res, ft_strlen(res));
		free (line);
		free (res);
	}
	return (close(node->command->redirects->fd), exit_all(data, g_err_code));
}

int	open_heredoc(t_data *data, t_node *node)
{
	int		pid;
	int		childval;

	childval = 0;
	node->command->redirects->heredoc_name = get_heredoc_name();
	node->command->redirects->fd = open(node->command->redirects->heredoc_name,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->command->redirects->fd == (-1))
		return (UNKNOWN_ERR);
	pid = fork();
	if (pid == (-1))
		return (UNKNOWN_ERR);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, ft_handler_heredoc);
		return (child_process(node, data, node->command->redirects->files[0]));
	}
	waitpid(pid, &childval, 0);
	if (WEXITSTATUS(childval) == 130)
	{
		close(node->command->redirects->fd);
		return (unlink(node->command->redirects->heredoc_name), SIGINT_ERR);
	}
	return (0);
}

int	open_heredocs(t_data *data, t_node *node)
{
	if (node->is_command && node->command->redirects
		&& node->command->redirects->rdtype == 9)
		g_err_code = open_heredoc(data, node);
	else if (!node->is_command)
	{
		open_heredocs(data, node->operand->l_child);
		open_heredocs(data, node->operand->r_child);
	}
	return (0);
}
