/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:18 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/03 14:47:52 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*apply_exp(t_data *data, char *str, char **env)
{
	char	*res;
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (free(str), fatal_error(data, "malloc"), NULL);
	i = 0;
	while (str[i])
	{
		tmp = res;
		res = getnvarvar(res, str, &i, env);
		free(tmp);
		if (!res)
			return (free(str), fatal_error(data, "malloc"), NULL);
	}
	return (free(str), res);
}

int	exp_args(t_data *data, char ***args, char **env)
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
			tmp = expand_wildcard(data, (*args)[i]);
			if (!tmp)
				return (UNKNOWN_ERR);
			free((*args)[i]);
			(*args)[i] = 0;
			(*args) = sumtab(data, (*args), tmp);
			if (!(*args))
				return (UNKNOWN_ERR);
		}
		(*args)[i] = apply_exp(data, (*args)[i], env);
		if (!(*args)[i])
			return (UNKNOWN_ERR);
		i++;
	}
	return (0);
}

int	exp_rds(t_data *data, t_rdlist *rdlist, char **env)
{
	char	**tmp;

	tmp = NULL;
	while (rdlist)
	{
		if (rdlist->rdtype != T_DOPCHEV)
		{
			if (ft_strchr(rdlist->file, '*'))
			{
				tmp = expand_wildcard(data, rdlist->file);
				if (!tmp)
					return (cherr_code(UNKNOWN_ERR));
				if (tmp[1])
					return (free_dchartab(tmp), cherr_code(1));
				rdlist->file = tmp[0];
				free(tmp[1]);
				free(tmp);
			}
			rdlist->file = apply_exp(data, rdlist->file, env);
			if (!rdlist->file)
				return (cherr_code(UNKNOWN_ERR));
		}
		rdlist = rdlist->next;
	}
	return (0);
}

int	expand(t_data *data, t_node *node, char **env)
{
	if (!node)
		return (0);
	if (exp_args(data, &node->arguments, env)
		|| exp_rds(data, node->redirects, env))
		return (UNKNOWN_ERR);
	return (0);
}
