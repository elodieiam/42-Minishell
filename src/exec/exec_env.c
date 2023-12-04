/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:45:59 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/04 12:57:14 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_printable(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

int	exec_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env->envtab[i])
	{
		if (is_printable(data->env->envtab[i]))
			printf("%s\n", data->env->envtab[i]);
		i++;
	}
	return (1);
}
