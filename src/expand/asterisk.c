/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:25:35 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/28 21:29:30 by elrichar         ###   ########.fr       */
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

char	**get_files(t_data *data, DIR *d, char **res, char *str)
{
	struct dirent	*dir;
	int				i;

	if (!d)
		return (NULL);
	i = 0;
	dir = readdir(d);
	if (!dir)
		return (exit_line(data, errnl(UNKNOWN_ERR, "readdir failed")), NULL);
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
				return (fatal_error(data, "malloc"), NULL);
			i++;
		}
		dir = readdir(d);
		if (!dir)
			return (exit_line(data, errnl(UNKNOWN_ERR, "readdir failed")), NULL);
	}
	if (closedir(d) == -1)
		return (exit_line(data, errnl(UNKNOWN_ERR, "closedir failed")), NULL);
	return (res);
}

char	**expand_wildcard(t_data *data, char *str)
{
	char			**res;
	DIR				*d;

	d = opendir(".");
	if (!d)
		return (exit_line(data, errnl(UNKNOWN_ERR, "opendir failed")), NULL);
	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (fatal_error(data, "malloc"), NULL);
	res[0] = ft_strdup(str);
	if (!res[0])
		return (free(res), fatal_error(data, "malloc"), NULL);
	res[1] = NULL;
	res = get_files(data, d, res, str);
	if (!res)
		return (NULL);
	return (res);
}
