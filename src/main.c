/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/10/23 16:56:26 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*line;
	t_data	*data;
	int		exit_val;
	
	data = malloc(sizeof(t_data));
	if (!data)
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
	exit_val = data->err_code;
	free(data);
	return (exit_val);
}
