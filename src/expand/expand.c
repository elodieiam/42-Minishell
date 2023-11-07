/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:18 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/07 20:10:16 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*apply_exp(char *str, char **env)
{
	char	*res;
	int		quote;
	int		i;

	res = ft_strdup("");
	quote = 0;
	i = 0;
	while (str[i])
	{
		res = ft_strjoin(res, get_nonvarstr(str, &i, &quote));	
		res = ft_strjoin(res, get_varstr(str, &i, &quote, env));
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
		tmp = apply_exp(args[i], env);
		if (!tmp)
			return (-1);
		free(tmp);
	}
	return (0);
}

//care if malloc fails
t_rdlist	*exp_rds(t_rdlist *rdlist, char **env)
{

}

int	expand(t_node *node, char **env)
{
	if (!node->is_command)
		return (expand(node->operand->l_child, env) +
			expand(node->operand->r_child, env));
	if (exp_args(node->command->arguments, env)
		|| exp_rds(node->command->redirects, env))
		return (-1);
	return (0);
}
