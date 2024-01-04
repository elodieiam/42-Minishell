/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:48:25 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/04 18:05:49 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	var_exists(char *cmd_arg, char **env, int *index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_arg[j])
		j++;
	while (env[i])
	{
		if (!ft_strncmp(cmd_arg, env[i], j) && (!env[i][j] || env[i][j] == '='))
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int	fill_unset_tab(char **envtab, char **new_env, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envtab[i])
	{
		if (i == index)
			i++;
		if (!envtab[i])
			break ;
		new_env[j] = ft_strdup(envtab[i]);
		if (!new_env[j])
		{
			free_dchartab(new_env);
			return (UNKNOWN_ERR);
		}
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (0);
}

int	unset_env(t_data *data, int index)
{
	int		nb_arg;
	char	**new_env;

	nb_arg = 0;
	while (data->env->envtab[nb_arg])
		nb_arg++;
	new_env = malloc(sizeof(char *) * nb_arg);
	if (!new_env)
		return (fatal_error(data, "malloc"));
	if (fill_unset_tab(data->env->envtab, new_env, index))
		return (free_dchartab(new_env), fatal_error(data, "malloc"));
	if (data->env->malloced)
		free_dchartab(data->env->envtab);
	data->env->malloced = 1;
	data->env->envtab = new_env;
	return (0);
}

int	exec_unset(t_data *data, char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (var_exists(args[i], data->env->envtab, &j))
		{
			if (unset_env(data, j))
				return (UNKNOWN_ERR);
		}
		i++;
	}
	return (0);
}
