/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/10/16 12:50:32 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell>");
		if (!ft_strncmp(line, "exit", 5))
			break ;
		tokens = ft_lexer(line);
		print_tokens(tokens);
		free(line);
	}
}
