/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:25:35 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/19 16:39:40 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	**get_files(DIR *d, char **res, char *str)
{
	struct dirent	*dir;
	int				i;

	if (!d)
		return (NULL);
	i = 0;
	dir = readdir(d);
	while (dir != NULL)
	{
		if ((*dir->d_name != '.' || *str == '.') && asterisk(dir->d_name, str))
		{
			if (i == 0)
			{
				free(res[0]);
				res[0] = NULL;
			}
			res = tab_addback(res, dir->d_name);
			if (!res)
				return (NULL);
			i++;
		}
		dir = readdir(d);
	}
	closedir(d);
	return (res);
}

char	**expand_wildcard(char *str)
{
	char			**res;
	DIR				*d;

	d = opendir(".");
	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(str);
	if (!res[0])
		return (free(res), NULL);
	res[1] = NULL;
	res = get_files(d, res, str);
	if (!res)
		return (NULL);
	closedir(d);
	return (res);
}
