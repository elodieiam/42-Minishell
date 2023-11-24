/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:31:59 by taospa            #+#    #+#             */
/*   Updated: 2023/11/24 20:43:40 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

int	check_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		write(2, "minishell: cd : ", 16);
		write(2, path, ft_strlen(path));
		write(2," : no suck file or directory\n", 29);
	}
	else if (access(path, X_OK) == -1 && access(path, R_OK) == -1
			&& access(path, W_OK) == -1)
	{
		write(2, "minishell: cd : ", 16);
		write(2, path, ft_strlen(path));
		write(2," : Permission denied\n", 21);
	}
	else
		return (0);
	return (-1);
}

int	cd_specific(t_data *data, t_node *node, char **newpwd)
{
	int		i;

	i = 0;
	if (!node->command->arguments[1])
	{
		*newpwd = get_varstr("$HOME", &i, data->env->envtab);
		if (*newpwd && ft_strncmp(*newpwd, "", 2))
			return (free(newpwd), exit_line(data,
						errnl(1, "minishell: cd: HOME not set")));
		return (1);
	}
	else if (!ft_strncmp(node->command->arguments[1], "-", 2))
	{
		*newpwd = get_varstr("$OLDPWD", &i, data->env->envtab);
		if (*newpwd && ft_strncmp(*newpwd, "", 2))
			return (free(*newpwd), exit_line(data,
						errnl(1, "minishell: cd: OLDPWD not set")));
		printf("%s\n", *newpwd);
		return (1);
	}
	return (0);
}

int	exec_cd(t_data *data, t_node *node)
{
	char	oldpwd[PATH_MAX];
	char	*newpwd;
	// char	*export_str;

	if (!cd_specific(data, node, &newpwd))
		newpwd = ft_strdup(node->command->arguments[1]);
	if (!getcwd(oldpwd, PATH_MAX))
		return (exit_line(data, errnl(UNKNOWN_ERR, "fatal: getcwd failed")));
	if (check_access(newpwd) == -1)
		return (free(newpwd), 1);
	chdir(newpwd);
	// export newpwd and oldpwd
	return (0);
}
