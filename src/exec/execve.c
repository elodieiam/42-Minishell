/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:20:37 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/04 19:18:54 by tsaint-p         ###   ########.fr       */
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
	if (!command || !command[0])
		return (0);
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
	if (!file_path || !cmd[0])
		exit(exit_all(data, ferrnl(cmd, NULL, "command not found", 127)));
	if (access(file_path, F_OK) == -1)
	{
		free(file_path);
		exit(exit_all(data,
				ferrnl(cmd, NULL, "No such file or directory", 127)));
	}
	if (access(file_path, X_OK) == -1)
	{
		free(file_path);
		exit(exit_all(data, ferrnl(cmd, NULL, "Permission denied", 126)));
	}
}

int	child_exec(t_data *data, t_node *node)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(data, node->arguments[0]);
	check_file(data, cmd_path, node->arguments[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, ft_handler);
	execve(cmd_path, node->arguments, data->env->envtab);
	free(cmd_path);
	return (exit_all(data, exit_line(data,
				errnl(-1, "minishell: execve failed"))));
}

int	execute(t_data *data, t_node *node)
{
	pid_t	pid;
	int		childval;

	childval = 0;
	if (!node->arguments)
		return (0);
	pid = fork();
	if (pid == -1)
		return (exit_line(data, errnl(-1, "minishell: fork failed")));
	if (!pid)
		if (child_exec(data, node))
			return (UNKNOWN_ERR);
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &childval, WUNTRACED) == -1)
		return (exit_line(data, errnl(-1, "minishell: waitpid failed")));
	if (handle_child_sigs(childval))
	{
		return (WTERMSIG(childval) + 128);
	}
	return (WEXITSTATUS(childval));
}
