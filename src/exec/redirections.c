/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:36:23 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/07 21:05:56 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	only_red_exec(t_node *node)
{
	if (node->command->redirects->rdtype == 9)
		if (exec_simple_heredoc(node->command->redirects->files[0]))
			return (1);
	return (0);
}

int	exec_heredoc_and_command(t_node *node, char *lim, t_data *data)
{
	pid_t	pid;
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
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 0);
		close(fd);
		execve("/bin/cat", node->command->arguments, data->env->envtab);
		// line = get_cmd_path(data, node->command->arguments[0]);
		// check_file(data, line, node->command->arguments[0]);
		// printf("Passe\n");
		// execve(line, node->command->arguments, data->env->envtab);
	}
	waitpid(pid, NULL, 0);
	close(fd);
	unlink("Heredoc");
	return (0);
}

int	red_and_command_exec(t_node *node, t_data *data)
{
	if (node->command->redirects->rdtype == 9)
		if (exec_heredoc_and_command(node, node->command->redirects->files[0], data))
			return (1);
	return (0);
}

// else if (node->command->redirects && node->command->arguments)
	// 	if (red_and_command_exec(data, node))
	// 		return (1);
int	handle_redirections(t_data *data, t_node *node)
{
	(void)data;
	if (!node->command->redirects && node->command->arguments)
		return (2);
	if (node->command->redirects && !node->command->arguments)
		if (only_red_exec(node))
			return (1);
	if (node->command->redirects && node->command->arguments)
		if (red_and_command_exec(node, data))
			return (1);
	return (0);
}
