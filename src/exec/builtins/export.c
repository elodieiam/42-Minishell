/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/15 19:37:01 by tsaint-p         ###   ########.fr       */
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

int	change_var(t_data *data, char *argument, int j)
{
	char	*new_var;
	char	**tmp_env;

	new_var = ft_strdup(argument);
	if (!new_var)
		return (UNKNOWN_ERR);
	if (!data->env->malloced)
	{
		tmp_env = cpy_env(data->env->envtab);
		if (!tmp_env)
			return (UNKNOWN_ERR);
		data->env->malloced = 1;
		data->env->envtab = tmp_env;
	}
	free(data->env->envtab[j]);
	data->env->envtab[j] = new_var;
	return (1);
}

int	search_var(t_data *data, char *argument, int i)
{
	int		j;

	j = -1;
	while (data->env->envtab[++j])
	{
		if (!ft_strncmp(argument, data->env->envtab[j], i))
			return (change_var(data, argument, j));
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
	changed = search_var(data, arguments[index], i);
	if (changed == UNKNOWN_ERR)
		return (UNKNOWN_ERR);
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
