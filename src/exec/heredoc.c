/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/08 15:37:23 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_child_heredoc(t_data *data, t_node *node)
{
	pid_t	pid;
	char	*cmd_path;
	int		fd;

	fd = open("Heredoc", O_RDONLY);
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
		return (exit_line(data, errnl(-1, "minishell: execve failed")));
	}
	waitpid(pid, NULL, 0);
	close(fd);
	unlink("Heredoc");
	return (0);
}

int	exec_heredoc_and_command(t_node *node, char *lim, t_data *data)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("Heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == (-1))
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			free (line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free (line);
	}
	close(fd);
	if (exec_child_heredoc(data, node))
		return (1);
	return (0);
}

int	exec_simple_heredoc(char *lim)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("Heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == (-1))
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			free (line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free (line);
	}
	close(fd);
	unlink("Heredoc");
	return (0);
}
