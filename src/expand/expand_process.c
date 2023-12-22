/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:42:46 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/22 14:45:52 by elrichar         ###   ########.fr       */
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
	else if (is_varsep(str[*i]))
		return (ft_strdup("$"));
	(*i)++;
	return (ft_strdup(""));
}

char	*get_nonvarstr(char *str, int *i, int *quote)
{
	char	*res;
	int		j;

	j = 0;
	res = malloc(sizeof(char) * (nonvarlen(str, *quote, *i) + 1));
	if (!res)
		return (NULL);
	while (str[*i] && (*quote == 39 || str[*i] != '$'))
	{
		if (str[*i] == *quote)
			*quote = 0;
		else
		{
			if (!*quote && (str[*i] == 34 || str[*i] == 39))
				*quote = str[*i];
			else
				res[j++] = str[*i];
		}
		(*i)++;
	}
	res[j] = '\0';
	return (res);
}

char	*get_varstr(char *str, int *i, char **env)
{
	int	j;
	int	k;

	if (!str)
		return (NULL);
	if (str[*i] != '$')
		return (ft_strdup(""));
	if (str[*i] == '$' && (ft_isdigit(str[*i + 1]) || \
		(is_varsep(str[*i + 1]) && str[*i + 1] != '_')))
		return (expand_exceptions(str, i));
	j = 0;
	(*i)++;
	while (!is_varsep(str[*i + j]) || (!j && str[*i] == '_'))
		j++;
	k = 0;
	while (env[k] && (ft_strncmp(&str[*i], env[k], j) || env[k][j] != '='))
		k++;
	*i = *i + j;
	printf("env = %s\n", env[k]);
	if (env[k])
		return (ft_strdup(&env[k][j + 1]));
	return (ft_strdup(""));
}
