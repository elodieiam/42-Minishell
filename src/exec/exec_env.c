/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:45:59 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/20 17:07:17 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env->envtab[i])
	{
		printf("%s\n", data->env->envtab[i]);
		i++;
	}
	return (1);
}
