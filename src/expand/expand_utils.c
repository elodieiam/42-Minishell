/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:27:10 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/07 19:55:37 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_varsep(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

char	*get_varstr(char *str, int *i, int *quote, char **env)
{

}

//not 100% sure about this function
int	nonvarlen(char *str)
{
	int		i;
	int		nb_quotes;
	int		quote;

	i = 0;
	nb_quotes = 0;
	quote = 0;
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

char	*get_nonvarstr(char *str, int *i, int *quote)
{
	char	*res;
	int		j;

	j = 0;
	res = malloc(sizeof(char) * nonvarlen(str));
	if (!res)
		return (NULL);
	while (str[*i] && (*quote == 39 || str[*i] != '$'))
	{
		if (str[*i] == *quote)
		{
			quote = 0;
			(*i)++;
		}
		else if (!quote && (str[*i] == 34 || str[*i] == 39))
		{
			*quote = str[*i];
			(*i)++;
		}
		str[*i] = res[j++];
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}
