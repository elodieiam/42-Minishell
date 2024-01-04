/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/04 23:06:50 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	change_var(t_data *data, char *argument, int j, int append)
{
	char	*new_var;
	char	**tmp_env;

	if (!ft_strchr(argument, '='))
		return (1);
	if (append)
		new_var = append_var(data, argument);
	else
		new_var = ft_strdup(argument);
	if (!new_var)
		return (UNKNOWN_ERR);
	if (!data->env->malloced)
	{
		tmp_env = cpy_env(data->env->envtab);
		if (!tmp_env)
			return (free(new_var), UNKNOWN_ERR);
		data->env->malloced = 1;
		data->env->envtab = tmp_env;
	}
	free(data->env->envtab[j]);
	data->env->envtab[j] = new_var;
	return (1);
}

int	search_var(t_data *data, char *argument, int i, int append)
{
	int		j;

	j = -1;
	while (data->env->envtab[++j])
	{
		if (!ft_strncmp(argument, data->env->envtab[j], i) && \
			(data->env->envtab[j][i] == '=' || !data->env->envtab[j][i]))
			return (change_var(data, argument, j, append));
	}
	return (0);
}

int	var_already_set(t_data *data, char *argument, int append)
{
	int		i;
	int		changed;

	i = 0;
	while (argument[i] && argument[i] != '='
		&& argument[i] != '+')
		i++;
	changed = search_var(data, argument, i, append);
	if (changed == UNKNOWN_ERR)
		return (UNKNOWN_ERR);
	else if (changed == 1)
		return (1);
	return (0);
}

int	export_arg(t_data *data, char *arg)
{
	int	append;
	int	set;

	append = 0;
	if (is_valid_arg(arg, &append))
	{
		set = var_already_set(data, arg, append);
		if (set == -1)
			return (-1);
		else if (set == 0)
		{
			if (update_env(data, arg, append) == UNKNOWN_ERR)
				return (g_err_code);
			return (0);
		}
	}
	else
		return (exit_line(data, ferrnl("export",
					arg, "not a valid identifier", 1)));
	return (0);
}

int	exec_export(t_data *data, char **arguments)
{
	int	i;

	i = 1;
	if (!arguments[i])
	{
		if (display_env(data) == UNKNOWN_ERR)
			return (g_err_code);
		return (0);
	}
	while (arguments[i])
	{
		export_arg(data, arguments[i]);
		i++;
	}
	return (0);
}
