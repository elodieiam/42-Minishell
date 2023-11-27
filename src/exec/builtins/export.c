/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/24 14:52:13 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**cpy_env(char **env)
{
	char	**res;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = NULL;
	i = 0;
	while (env[i])
	{
		res[i] = ft_strdup(env[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	return (res);
}

int	changevar(t_data *data, char *argument, int i)
{
	int		j;
	char	*new_var;
	char	**tmp_env;

	new_var = NULL;
	j = -1;
	while (data->env->envtab[++j])
		if (!ft_strncmp(argument, data->env->envtab[j], i))
		{
			tmp_env = cpy_env(data->env->envtab);
			if (!tmp_env)
				return (MALLOC_ERR);
			new_var = ft_strdup(argument);
			if (!new_var)
				return (MALLOC_ERR);
			if (data->env->malloced)
				free_dchartab(data->env->envtab);
			data->env->malloced = 1;
			data->env->envtab = tmp_env;
			free(data->env->envtab[j]);
			data->env->envtab[j] = new_var;
			return (1);
		}
	return (0);
}

int	var_already_set(t_data *data, char **arguments, int index)
{
	int		i;
	int		changed;

	i = 0;
	while (arguments[index][i] &&
			arguments[index][i] != '=')
		i++;
	changed = changevar(data, arguments[index], i);
	if (changed == MALLOC_ERR)
		return (MALLOC_ERR);
	else if (changed == 1)
		return (1);
	return (0);
}

int	exec_export(t_data *data, char **arguments)
{
	int	i;
	int	set;

	i = 1;
	if (!arguments[i])
		return (display_env(data), 0);
	while (arguments[i])
	{
		if (is_valid_arg(arguments[i]))
		{
			set = var_already_set(data, arguments, i);
			if (set == -1)
				return (-1);
			else if (set == 0)
				if (!update_env(data, arguments, i))
					return (1);
		}
		else
			return (exit_line(data, ferrnl
					("export", arguments[i],
						"not a valid identifier", 1)));
		i++;
	}
	return (0);
}
