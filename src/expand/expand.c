/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:18 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/14 22:00:08 by taospa           ###   ########.fr       */
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
//t_rdlist	*exp_rds(t_rdlist *rdlist, char **env)
//{

//}

int	expand(t_node *node, char **env)
{
	if (!node)
		return (0);
	if (!node->is_command && node->operand)
		return (expand(node->operand->l_child, env)
			+ expand(node->operand->r_child, env));
	if (exp_args(node->command->arguments, env)
		/*|| exp_rds(node->command->redirects, env)*/)
		return (-1);
	return (0);
}
