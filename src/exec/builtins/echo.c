/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:45:13 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/12 12:07:16 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_echo_opt(char *str)
{
	if (!str || !*str || *str != '-')
		return (0);
	str++;
	while (*str && *str == 'n')
		str++;
	if (*str)
		return (0);
	return (1);
}

int	exec_echo(t_node *node)
{
	int	i;
	int	is_option;

	is_option = 0;
	i = 1;
	while (is_echo_opt(node->arguments[i++]))
		is_option = 1;
	i--;
	while (node->arguments[i])
	{
		printf("%s", node->arguments[i++]);
		if (node->arguments[i])
			printf(" ");
	}
	if (!is_option)
		printf("\n");
	return (0);
}
