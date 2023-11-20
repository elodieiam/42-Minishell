/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/20 22:47:15 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_var(t_data *data, t_node *node, int index, int i)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = 0;
	while (data->env->envtab[j])
	{
		if (!ft_strncmp(node->command->arguments[index],
				data->env->envtab[j], i))
		{
			tmp = malloc(sizeof(char)
					* ft_strlen(node->command->arguments[index]) + 1);
			if (!tmp)
				return (-1);
			ft_strlcpy(tmp, node->command->arguments[index],
				ft_strlen(node->command->arguments[index]) + 1);
			if (data->env->malloced)
				free(data->env->envtab[j]);
			data->env->envtab[j] = tmp;
			return (1);
		}
		j++;
	}
	return (0);
}

int	var_already_set(t_data *data, t_node *node, int index)
{
	int		i;
	int		check;

	i = 0;
	while (node->command->arguments[index][i] &&
			node->command->arguments[index][i] != '=')
		i++;
	check = check_var(data, node, index, i);
	if (check == -1)
		return (-1);
	else if (check == 1)
		return (1);
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
			if (set == -1)
				return (-1);
			else if (set == 0)
				if (!update_env(data, node, i))
					return (1);
		}
		else
			return (exit_line(data, ferrnl
					("export", node->command->arguments[i],
						"not a valid identifier", 1)));
		i++;
	}
	return (0);
}
