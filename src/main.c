/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/11/03 16:04:34 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//init data ?
int	main(int ac, char *av[], char *env[])
{
	char	*line;
	t_data	*data;
	int		exit_val;
	
	if (ac != 1)
		return (errnl(1, "Error : no arguments required"));
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data || get_env(env, data))
		return (-1);
	while (1)
	{
		line = readline("minishell>");
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);	
			break ;
		}
		add_history(line);

		data->tokens = ft_lexer(line);
		print_tokens(data->tokens);
		parse(data);
		pretty_print_ast(data->tree, "");
		free(line);
		exit_line(data, 0);
	}
	if (data->lst_env)
		free_env(&(data->lst_env));
	exit_val = data->err_code;
	free(data);
	return (exit_val);
}
