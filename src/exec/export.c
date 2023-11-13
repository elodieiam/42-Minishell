/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/13 15:56:55 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_env(t_data *data, t_node *node)
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
	new_env[nb_arg] = ft_strdup(node->command->arguments[1]);
	new_env[nb_arg + 1] = NULL;
	if (data->env->malloced == 1)
		free_dchartab(data->env->envtab);
	data->env->envtab = new_env;
	data->env->malloced = 1;
	return (1);
}

int	var_already_set(t_data *data, t_node *node)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (node->command->arguments[1][i] != '=')
		i++;
	while (data->env->envtab[j])
	{
		if (!ft_strncmp(node->command->arguments[1], data->env->envtab[j], i + 1))
		{
			tmp = malloc(sizeof(char) * ft_strlen(node->command->arguments[1]) + 1);
			if (!tmp)
				return (-1);
			ft_strlcpy(tmp, node->command->arguments[1], ft_strlen(node->command->arguments[1]) + 1);
			if (data->env->malloced)
				free(data->env->envtab[j]);
			data->env->envtab[j] = tmp;
			return (1);
		}
		j++;
	}
	return (0);
}


int	exec_export(t_data *data, t_node *node)
{
	int	i;
	int	set;

	i = 1;
	// if (!node->command->arguments[i])
	// 	return (display_env(data), 0);
	while (node->command->arguments[i])
	{
		if (is_valid_arg(node->command->arguments[i]))
		{
			set = var_already_set(data, node);
			printf("is valid arg\n");
			if (set == -1)
				return (1);
			else if (set == 0)
			{
				if (!update_env(data, node))
					return (1);		
			}
		}
		else
			return (1);
		i++;
	}
	i = 0;
	while (data->env->envtab[i])
	{
		printf("%s\n", data->env->envtab[i]);
		i++;
	}
	return (0);
}
