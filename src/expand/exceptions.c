/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:42:46 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/05 00:07:40 by taospa           ###   ########.fr       */
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

char	**sumtab(char **t1, char **t2)
{
	int		i;
	int		j;
	char	**res;

	if (!t2)
		return (free_dchartab(t1), NULL);
	i = 0;
	j = 0;
	while (t1[i])
		i++;
	while (t2[j])
		j++;
	res = malloc(sizeof(char *) * (i + j + 1));
	if (!res)
		return (free_dchartab(t1), free_dchartab(t2), NULL);
	i = -1;
	j = -1;
	while (t1[++i])
		res[i] = t1[i];
	while (t2[++j])
		res[i + j] = t2[j];
	res[i + j] = 0;
	return (free(t1), free(t2), res);
}

char	**tab_addback(char **tab, char *new)
{
	int		i;
	char	**res;

	i = 0;
	while (tab[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		res[i] = ft_strdup(tab[i]);
		if (!res[i])
			return (free_dchartab(res), free_dchartab(tab), NULL);
		i++;
	}
	res[i] = ft_strdup(new);
	if (!res[i])
		return (free_dchartab(res), free_dchartab(tab), NULL);
	res[i + 1] = NULL;
	free_dchartab(tab);
	return (res);
}

char	**expand_wildcard(char *str)
{
	struct dirent	*dir;
	char			**res;
	DIR				*d;
	int				i;

	i = 0;
	d = opendir(".");
	res = malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup(str);
	if (!res[0])
		return (free(res), NULL);
	res[1] = NULL;
	if (!d)
		return (NULL);
	dir = readdir(d);
	while (dir != NULL)
	{
		if ((dir->d_name[0] != '.' || str[0] == '.') && asterisk(dir->d_name, str))
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
	// print_dchartab(res);
	return (res);
}
