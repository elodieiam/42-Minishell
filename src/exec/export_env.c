/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:08:37 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/20 15:56:59 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **new_env, int i)
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
	print_env(new_env, i);
}

int	update_env(t_data *data, t_node *node, int index)
{
	char	**new_env;
	int		nb_arg;

	new_env = NULL;
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
		nb_arg++;
	new_env = malloc(sizeof(char *) * (nb_arg + 2));
	if (!new_env)
		return (0);
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
	{
		new_env[nb_arg] = ft_strdup(data->env->envtab[nb_arg]);
		nb_arg++;
	}
	new_env[nb_arg] = ft_strdup(node->command->arguments[index]);
	new_env[nb_arg + 1] = NULL;
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
		return (0);
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
	{
		new_env[nb_arg] = ft_strdup(data->env->envtab[nb_arg]);
		nb_arg++;
	}
	new_env[nb_arg] = NULL;
	sort_env(nb_arg, new_env);
	free_dchartab(new_env);
	return (1);
}
