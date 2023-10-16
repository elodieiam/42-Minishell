/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/10/16 13:08:12 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		printf("string %d: \"%s\" type : %d\n", i++, tokens->string, tokens->type);
		fflush(stdout);
		tokens = tokens->next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell>");
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);	
			break ;
		}
		add_history(line);
		tokens = ft_lexer(line);
		print_tokens(tokens);
		free(line);
		free_tokens(&tokens);
	}
}
