/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:18 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/04 16:16:29 by tsaint-p         ###   ########.fr       */
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
		return (free(str_to_join), NULL);
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

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tmp = res;
		res = getnvarvar(res, str, &i, env);
		free(tmp);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	exp_args(char **args, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
		{
			tmp = args[i];
			args[i] = expand_wildcard(args[i]);
			printf("files : %s\n", args[i]);
			free(tmp);
			if (!args[i])
				return (MALLOC_ERR);
		}
		tmp = args[i];
		args[i] = apply_exp(args[i], env);
		free(tmp);
		if (!args[i])
			return (-1);
		i++;
	}
	return (0);
}

//care if malloc fails
int	exp_rds(t_rdlist *rdlist, char **env)
{
	char	*tmp;

	while (rdlist)
	{
		if (ft_strchr(rdlist->files, '*'))
		{
			tmp = rdlist->files;
			rdlist->files = expand_wildcard(rdlist->files);
			printf("files : %s\n", rdlist->files);
			free(tmp);
			if (!rdlist->files)
				return (MALLOC_ERR);
		}
		tmp = rdlist->files;
		rdlist->files = apply_exp(rdlist->files, env);
		free(tmp);
		if (!rdlist->files)
			return (MALLOC_ERR);
		rdlist = rdlist->next;
	}
	return (0);
}

int	expand(t_node *node, char **env)
{
	if (!node)
		return (0);
	if (!node->is_command && node->operand)
		return (expand(node->operand->l_child, env)
			+ expand(node->operand->r_child, env));
	if (exp_args(node->command->arguments, env)
		|| exp_rds(node->command->redirects, env))
		return (-1);
	return (0);
}
