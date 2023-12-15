/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:18 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/15 13:14:48 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//leak on res ??
char	*getnvarvar(char *res, char *str, int *i, char **env)
{
	char		*str_to_join;
	char		*tmp;
	static int	quote;

	str_to_join = get_nonvarstr(str, i, &quote);
	if (!str_to_join)
		return (NULL);
	res = ft_strjoin(res, str_to_join);
	free(str_to_join);
	if (!res)
		return (NULL);
	if (quote != 39)
	{
		str_to_join = get_varstr(str, i, env);
		if (!str_to_join)
			return (free(res), NULL);
		tmp = res;
		res = ft_strjoin(res, str_to_join);
		free(str_to_join);
		free(tmp);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*apply_exp(char *str, char **env)
{
	char	*res;
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (free(str), NULL);
	i = 0;
	while (str[i])
	{
		tmp = res;
		res = getnvarvar(res, str, &i, env);
		free(tmp);
		if (!res)
			return (free(str), NULL);
	}
	return (free(str), res);
}

int	exp_args(char ***args, char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!(*args))
		return (0);
	while ((*args)[i])
	{
		if (ft_strchr((*args)[i], '*'))
		{
			tmp = expand_wildcard((*args)[i]);
			free((*args)[i]);
			(*args)[i] = 0;
			(*args) = sumtab((*args), tmp);
			if (!(*args))
				return (MALLOC_ERR);
		}
		(*args)[i] = apply_exp((*args)[i], env);
		if (!(*args)[i])
			return (-1);
		i++;
	}
	return (0);
}

//care if malloc fails
int	exp_rds(t_rdlist *rdlist, char **env)
{
	char	**tmp;

	while (rdlist)
	{
		if (rdlist->rdtype != T_DOPCHEV)
		{
			if (ft_strchr(rdlist->files[0], '*'))
			{
				tmp = rdlist->files;
				rdlist->files = expand_wildcard(rdlist->files[0]);
				free_dchartab(tmp);
				if (!rdlist->files)
					return (MALLOC_ERR);
			}
			rdlist->files[0] = apply_exp(rdlist->files[0], env);
			if (!rdlist->files[0])
				return (MALLOC_ERR);
		}
		rdlist = rdlist->next;
	}
	return (0);
}

int	expand(t_node *node, char **env)
{
	if (!node)
		return (0);
	if (exp_args(&node->arguments, env)
		|| exp_rds(node->redirects, env))
		return (UNKNOWN_ERR);
	return (0);
}
