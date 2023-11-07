/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/11/06 18:32:44 by elrichar         ###   ########.fr       */
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
	data->err_code = 0;
	data->tokens = NULL;
	data->tree = NULL;
	data->tmp_tree = NULL;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
		return (free(data), NULL);
	data->env->envtab = env;
	data->env->malloced = 0;
	return (data);
}

//init data ?
int	main(int ac, char *av[], char **env)
{
	t_data	*data;
	
	if (ac != 1)
		return (errnl(1, "Error : no arguments required"));
	(void)av;
	data = init_data(env);
	if (!data)
		return (-1);
	while (1)
	{
		data->prompt = readline("minishell>");
		add_history(data->prompt);
		data->tokens = ft_lexer(data->prompt);
		parse(data);
		data->err_code = exec(data);
		exit_line(data, 0);
	}
	return (exit_all(data, data->err_code));
}
