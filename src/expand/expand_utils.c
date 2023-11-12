/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:27:10 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/12 23:30:53 by tsaint-p         ###   ########.fr       */
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

char	*get_varstr(char *str, int *i, char **env)
{
	int	j;
	int	k;

	if (!str)
		return (NULL);
	if (str[*i] != '$')
		return (ft_strdup(""));
	if ((str[*i] == '$' && ft_isdigit(str[*i + 1])))
	{
		*i += 2;
		return (ft_strdup(""));
	}
	j = 0;
	(*i)++;
	while(!is_varsep(str[*i + j]))
		j++;
	k = 0;
	while (env[k] && (ft_strncmp(&str[*i], env[k], j) || env[k][j] != '='))
			k++;
	*i = *i + j;
	//printf("env[%d][%d] = %s", k, j, &env[k][j]);
	if (env[k])
		return (ft_strdup(&env[k][j + 1]));
	return (ft_strdup(""));
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
		res[*i] = str[j++];
		(*i)++;
	}
	res[j] = '\0';
	printf("res of nonvarstr : %s\n", res);
	return (str);
}
