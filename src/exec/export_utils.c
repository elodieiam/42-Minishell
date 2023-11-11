/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:44:59 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/11 17:06:26 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_equal_sign(char *str)
{
	if (*str == '=')
		return (0);
	while (*str && *str != '=')
		str++;
	if (!*str)
		return (0);
	if (*str == '=' && *(str + 1) && *(str + 1) != '=')
		return (1);
	return (0);
}


int	is_valid_arg(char *str)
{
	if (!check_equal_sign(str))
		return (0);
	return (1);
}