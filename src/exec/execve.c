/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:20:37 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/30 15:00:23 by elrichar         ###   ########.fr       */
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

int	handle_child_sigs(int childval, t_data *data)
{
	if (WIFSIGNALED(childval))
	{
		if (WTERMSIG(childval) == SIGQUIT)
		{
			printf("Quit (core dumped)\n");
			exit_line(data, 131);
		}
		return (1);
	}
	return (0);
}

void sig_handler_child(int sig)
{
	(void)sig;
}

int	execute(t_data *data, t_node *node)
{
	char	*cmd_path;
	pid_t	pid;
	pid_t	waitval;
	int		childval;

	childval = 0;
	waitval = 0;
	pid = fork();
	if (pid == -1)
		return (exit_line(data, errnl(-1, "minishell: fork failed")));
	if (!pid)
	{
		cmd_path = get_cmd_path(data, node->command->arguments[0]);
		check_file(data, cmd_path, node->command->arguments[0]);
		signal(SIGQUIT, sig_handler_child);
		execve(cmd_path, node->command->arguments, data->env->envtab);
		free(cmd_path);
		exit(exit_line(data, errnl(-1, "minishell: execve failed")));
	}
	waitval = waitpid(pid, &childval, 0);
	if (waitval == -1)
		return (exit_line(data, errnl(-1, "minishell: waitpid failed")));
	if (handle_child_sigs(childval, data))
		return (WTERMSIG(childval));
	return (WEXITSTATUS(childval));
}
