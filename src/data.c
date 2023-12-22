/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:03:59 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/22 16:09:45 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->prompt = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->pidlist = NULL;
	data->fds.curr[0] = STDIN_FILENO;
	data->fds.curr[1] = STDOUT_FILENO;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
		return (free(data), NULL);
	data->env->envtab = env;
	data->env->malloced = 0;
	g_err_code = 0;
	return (data);
}
