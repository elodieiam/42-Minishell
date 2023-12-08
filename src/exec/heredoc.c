/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/08 21:17:50 by elrichar         ###   ########.fr       */
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
	close(fd);
	unlink(node->command->redirects->heredoc_name);
	free(node->command->redirects->heredoc_name);
	return (0);
}

int	exec_heredoc_and_command(t_node *node, t_data *data)
{
	close(node->command->redirects->fd);
	if (exec_child_heredoc(data, node))
		return (1);
	return (0);
}

int	exec_simple_heredoc(t_node *node)
{
	close(node->command->redirects->fd);
	unlink(node->command->redirects->heredoc_name);
	free(node->command->redirects->heredoc_name);
	return (0);
}
