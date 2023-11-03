/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/11/03 18:57:43 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*init_data(void)
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
	data->lst_env = NULL;
	return (data);
}

//init data ?
int	main(int ac, char *av[], char *env[])
{
	t_data	*data;
	int		exit_val;
	
	if (ac != 1)
		return (errnl(1, "Error : no arguments required"));
	(void)av;
	data = init_data();
	if (!data || get_env(env, data))
		return (-1);
	while (1)
	{
		data->prompt = readline("minishell>");
		add_history(data->prompt);
		data->tokens = ft_lexer(data->prompt);
		parse(data);
		exec(data);
		exit_line(data, 0);
	}
	if (data->lst_env)
		free_env(&(data->lst_env));
	exit_val = data->err_code;
	free(data);
	return (exit_val);
}
