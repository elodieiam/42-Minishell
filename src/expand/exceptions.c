/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:42:46 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/04 16:16:27 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_exceptions(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_err_code));
	}
	(*i)++;
	printf("%d\n", *i);
	return (ft_strdup(""));
}

int	asterisk(char *file, char *exp)
{
	if (!ft_strcmp(exp, "*") || !ft_strcmp(file, exp))
		return (1);
	if (!*file)
		return (0);
	if (*exp == '*')
		return (asterisk(file, &(exp[1])) || asterisk(&(file[1]), exp));
	if (*file == *exp)
		return (asterisk(&(file[1]), &(exp[1])));
	return (0);
}

char	*expand_wildcard(char **tab)
{
	struct dirent	*dir;
	char			*res;
	DIR				*d;
	int				i;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	d = opendir(".");
	if (!d)
		return (free(res), NULL);
	dir = readdir(d);
	while (dir != NULL)
	{
		if ((dir->d_name[0] != '.' || tab[0][0] == '.') && asterisk(dir->d_name, str))
		{
			res = ft_strjoin(res, " ");
			res = ft_strjoin(res, dir->d_name);
			if (!res)
				return ((void)closedir(d), NULL);
		}
		dir = readdir(d);
	}
	closedir(d);
	return (res);
}
