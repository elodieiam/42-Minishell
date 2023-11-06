/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:21:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/06 16:15:03 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int	is_path(const char *str)
{
	if (!str)
		return (0);
	while (*str && *str != '/')
		str++;
	if (*str)
		return (1);
	return (0);
}

char	*bettercat(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len1 + len2 + 1)
	{
		if (i < len1)
			res[i] = s1[i];
		else if (i == len1)
			res[i] = '/';
		else
			res[i] = s2[i - len1 - 1];
		i++;
	}
	res[i] = 0;
	return (res);
}

void	free_dchartab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
