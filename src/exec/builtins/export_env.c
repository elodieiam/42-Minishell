/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:08:37 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/03 16:47:23 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sorted_env(char **new_env, int i)
{
	int	j;

	while (new_env[i])
	{
		j = 0;
		while (new_env[i][j] && new_env[i][j] != '=')
		{
			printf("%c", new_env[i][j]);
			j++;
		}
		if (new_env[i][j] && new_env[i][j] == '=')
		{
			printf("%c\"", new_env[i][j]);
			j++;
			while (new_env[i][j])
			{
				printf("%c", new_env[i][j]);
				j++;
			}
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

void	sort_env(int nb_arg, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_arg - 1)
	{
		j = i + 1;
		while (j < nb_arg)
		{
			if (ft_strcmp(new_env[i], new_env[j]) > 0)
				swap_strings(&new_env[i], &new_env[j]);
			j++;
		}
		i++;
	}
	i = 0;
	print_sorted_env(new_env, i);
}

int	chenv(t_data *data, char *argument, char **new_env, int append)
{
	int		nb_arg;

	nb_arg = -1;
	while (data->env->envtab[++nb_arg])
	{
		new_env[nb_arg] = ft_strdup(data->env->envtab[nb_arg]);
		if (!new_env[nb_arg])
			return (free_dchartab(new_env), fatal_error(data, "malloc"));
	}
	if (append)
		new_env[nb_arg] = append_var(data, argument);
	else
	{
		new_env[nb_arg] = ft_strdup(argument);
		if (!new_env[nb_arg])
			return (free_dchartab(new_env), fatal_error(data, "malloc"));
	}
	new_env[nb_arg + 1] = NULL;
	return (0);
}

int	update_env(t_data *data, char **arguments, int index, int append)
{
	char	**new_env;
	int		nb_arg;

	new_env = NULL;
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
		nb_arg++;
	new_env = malloc(sizeof(char *) * (nb_arg + 2));
	if (!new_env)
		return (fatal_error(data, "malloc"));
	if (chenv(data, arguments[index], new_env, append))
		return (g_err_code);
	if (data->env->malloced == 1)
		free_dchartab(data->env->envtab);
	data->env->envtab = new_env;
	data->env->malloced = 1;
	return (1);
}

int	display_env(t_data *data)
{
	int		nb_arg;
	char	**new_env;

	new_env = NULL;
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
		nb_arg++;
	new_env = malloc(sizeof(char *) * (nb_arg + 1));
	if (!new_env)
		return (fatal_error(data, "malloc"));
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
	{
		new_env[nb_arg] = ft_strdup(data->env->envtab[nb_arg]);
		if (!new_env[nb_arg])
			return (free_dchartab(new_env), fatal_error(data, "malloc"));
		nb_arg++;
	}
	new_env[nb_arg] = NULL;
	sort_env(nb_arg, new_env);
	free_dchartab(new_env);
	return (1);
}
