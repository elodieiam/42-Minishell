/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:45:13 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/07 16:42:53 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_echo_opt(char *str)
{
	if (!*str || *str != '-')
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
	while (is_echo_opt(node->command->arguments[i++]))
		is_option = 1;
	i--;
	while (node->command->arguments[i])
	{
		printf("%s", node->command->arguments[i++]);
		if (node->command->arguments[i])
			printf(" ");
	}
	if (!is_option)
		printf("\n");
	return (0);
}