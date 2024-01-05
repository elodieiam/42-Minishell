/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:44:59 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/05 12:38:08 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_equal_sign(char *str, int *append)
{
	if (*str == '=')
		return (0);
	while (*str && *str != '=' && *str != '+')
		str++;
	if (!*str)
		return (1);
	if (*str == '+' && str[1] && str[1] == '=' && str[2])
	{
		*append = 1;
		return (1);
	}
	if (*str == '=' && *(str + 1) && *(str + 1) != '=')
		return (1);
	if (*str == '=' && !*(str + 1))
		return (1);
	return (0);
}

int	check_valid_string(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str && *str != '=' && *str != '+')
	{
		if (is_varsep(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void	swap_strings(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	is_valid_arg(char *str, int *append)
{
	if (!check_equal_sign(str, append))
		return (0);
	if (!check_valid_string(str))
		return (0);
	return (1);
}
