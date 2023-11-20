/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/20 14:14:54 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	var_already_set(t_data *data, t_node *node, int index)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (node->command->arguments[index][i] && node->command->arguments[index][i] != '=')
		i++;
	while (data->env->envtab[j])
	{
		if (!ft_strncmp(node->command->arguments[index], data->env->envtab[j], i))
		{
			tmp = malloc(sizeof(char) * ft_strlen(node->command->arguments[index]) + 1);
			if (!tmp)
				return (-1);
			ft_strlcpy(tmp, node->command->arguments[index], ft_strlen(node->command->arguments[index]) + 1);
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
	if (!node->command->arguments[i])
		return (display_env(data), 0);
	while (node->command->arguments[i])
	{
		if (is_valid_arg(node->command->arguments[i]))
		{
			set = var_already_set(data, node, i);
			printf("%s : set = %d\n", node->command->arguments[i], set);
			if (set == -1)
				return (1);
			else if (set == 0)
			{
				if (!update_env(data, node, i))
					return (1);
			}
		}
		else
			printf("export : '%s' : not a valid identifier\n", \
					node->command->arguments[i]);
		i++;
	}
	return (0);
}
