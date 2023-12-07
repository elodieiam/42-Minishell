/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:20:37 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/07 11:41:14 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_paths(t_data *data)
{
	int	i;

	i = 0;
	while (data->env->envtab[i])
	{
		if (!ft_strncmp(data->env->envtab[i], "PATH=", 5))
			return (&(data->env->envtab[i][5]));
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_data *data, char *command)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	if (is_path(command))
		return (ft_strdup(command));
	paths = ft_split(get_paths(data), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = bettercat(paths[i], command);
		if (!access(tmp, X_OK))
			break ;
		i++;
		free(tmp);
		tmp = NULL;
	}
	free_dchartab(paths);
	return (tmp);
}

void	check_file(t_data *data, char *file_path, char *cmd)
{
	if (!file_path)
		exit(exit_all(data, ferrnl(cmd, NULL, "command not found", 127)));
	if (access(file_path, F_OK) == -1)
		exit(exit_all(data,
				ferrnl(cmd, NULL, "No such file or directory", 127)));
	if (access(file_path, X_OK) == -1)
		exit(exit_all(data, ferrnl(cmd, NULL, "Permission denied", 126)));
}

int	child_exec(t_data *data, t_node *node)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(data, node->command->arguments[0]);
	check_file(data, cmd_path, node->command->arguments[0]);
	signal(SIGQUIT, sig_handler_child);
	signal(SIGINT, sig_handler_child);
	execve(cmd_path, node->command->arguments, data->env->envtab);
	free(cmd_path);
	return (exit_line(data, errnl(-1, "minishell: execve failed")));
}

int	exec_heredoc(char *lim)
{
	int		fd;
	int		i;
	char	*buff;

	buff = malloc(sizeof(char) * ft_strlen(lim) + 1);
	if (!buff)
		return (1);
	fd = open("Heredoc", O_CREAT | O_WRONLY, 0700);
	if (fd == (-1))
		return (1);
	i = read(0, buff, ft_strlen(lim));
	if (i < 0)
		return (close(fd), free(buff), 1);
	while (i > 0 && strncmp(buff, lim, ft_strlen(lim)))
	{
		write(fd, buff, ft_strlen(lim));
		i = read(0, buff, ft_strlen(lim));
		if (i < 0)
			return (close(fd), free(buff), 1);
		buff[i] = '\0';
	}
	close(fd);
	unlink("Heredoc");
	free(buff);
	return (0);
}

int	only_red_exec(t_node *node)
{
	if (node->command->redirects->rdtype == 9
		&& node->command->redirects->files[0])
		if (exec_heredoc(node->command->redirects->files[0]))
			return (1);
	return (0);
}

//TODO : protect execute callers from execve fail
int	execute(t_data *data, t_node *node)
{
	pid_t	pid;
	pid_t	waitval;
	int		childval;

	childval = 0;
	waitval = 0;
	pid = fork();
	if (pid == -1)
		return (exit_line(data, errnl(-1, "minishell: fork failed")));
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		if (node->command->arguments && !node->command->redirects)
		{
			if (child_exec(data, node))
				return (UNKNOWN_ERR);
		}
		if (node->command->redirects)
		{
			if (!node->command->arguments)
			{
				if (only_red_exec(node))
					return (UNKNOWN_ERR);
				else
					return (printf("worked\n"), UNKNOWN_ERR);
			}
		}
	}
	waitval = waitpid(pid, &childval, 0);
	if (waitval == -1)
		return (exit_line(data, errnl(-1, "minishell: waitpid failed")));
	if (handle_child_sigs(childval))
		return (WTERMSIG(childval) + 128);
	return (WEXITSTATUS(childval));
}
