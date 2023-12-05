/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:27:10 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/05 12:48:43 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_varsep(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

char	*get_varcontent(char *var)
{
	while (*var && *var != '=')
		var++;
	return (ft_strdup(var));
}

//not 100% sure about this function
int	nonvarlen(char *str, int quote, int i)
{
	int		nb_quotes;

	nb_quotes = 0;
	if (!str)
		return (0);
	while (str[i] && (quote == 39 || str[i] != '$'))
	{
		if (str[i] == quote)
		{
			quote = 0;
			nb_quotes++;
		}
		else if (!quote && (str[i] == 34 || str[i] == 39))
		{
			quote = str[i];
			nb_quotes++;
		}
		i++;
	}
	return (i - nb_quotes + 1);
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
