/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/10/19 13:19:41 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*tta(t_toktype int_type)
{
	if (int_type == 1)
		return ("T_WORD");
	if (int_type == 2)
		return ("T_OPPAR");
	if (int_type == 3)
		return ("T_CLPAR");
	if (int_type == 4)
		return ("T_PIPE");
	if (int_type == 5)
		return ("T_OR");
	if (int_type == 6)
		return ("T_AND");
	if (int_type == 7)
		return ("T_OPCHEV");
	if (int_type == 8)
		return ("T_CLCHEV");
	if (int_type == 9)
		return ("T_DOPCHEV");
	if (int_type == 10)
		return ("T_DCLCHEV");
	return (NULL);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		printf("string %d: \"%s\" type : %s\n", i++, tokens->string, tta(tokens->type));
		fflush(stdout);
		tokens = tokens->next;
	}
}

int	main(void)
{
	char	*line;
	t_data	*data;

	while (1)
	{
		line = readline("minishell>");
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);	
			break ;
		}
		add_history(line);
		data = malloc(sizeof(t_data));
		if (!data)
			return (-1);
		data->tokens = ft_lexer(line);
		print_tokens(data->tokens);
		parse(data);
		print_tree(data->tree, 0);
		free(line);
		exit_line(data, 0);
	}
	return (data->err_code);
}
