/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:44:59 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/10 17:59:09 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_equal_sign(char **str)
{
	if (**str == '=')
		return (0);
	while (**str && **str != '=')
		(*str)++;
	if (!**str)
		return (0);
	if (**str == '=' && *(*str + 1) && *(*str + 1) != '=')
		return (1);
	return (0);
}

static int	check_nb_quotes(char *str)
{
	int	nb_quotes;

	nb_quotes = 0;
	if (*str == '"')
	{
		while (*str)
		{
			if (*str == '"')
				nb_quotes++;
			str++;
		}
	}
	else if (*str == 39)
	{
		while (*str)
		{
			if (*str == 39)
				nb_quotes++;
			str++;
		}
	}
	if (nb_quotes != 2 && nb_quotes != 0)
		return (0);
	return (1);
}

static int	check_quotes_pos(char *str)
{
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		if (*str == '"' && !*(str + 1))
			return (1);
	}
	else if (*str == 39)
	{
		str++;
		while (*str && *str != 39)
			str++;
		if (*str == 39 && !*(str + 1))
			return (1);
	}
	else
	{
		while (*str)
			str++;
		if (*str == '"' || *str == 39)
			return (0);
	}
	return (1);
}

int	is_valid_arg(char *str)
{
	if (!check_equal_sign(&str))
		return (0);
	if (!check_nb_quotes(str + 1))
		return (0);
	if (!check_quotes_pos(str + 1))
		return (0);
	return (1);
}