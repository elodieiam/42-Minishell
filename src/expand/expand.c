/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:18 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/12 23:30:50 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*apply_exp(char *str, char **env)
{
	char	*res;
	char	*tmp;
	int		quote;
	int		i;

	res = ft_strdup("");
	quote = 0;
	i = 0;
	printf("str to expand = %s\n", str);
	while (str[i])
	{
		tmp = res;
		res = ft_strjoin(res, get_nonvarstr(str, &i, &quote));	
		printf("%c\n", str[i]);
		if (tmp)
			free(tmp);
		if (!res)
			return (NULL);
		tmp = res;
		if (quote != 39)
		{
			printf("res before exp %s\n", res);
			res = ft_strjoin(res, get_varstr(str, &i, env));
			printf("\nres after exp %s\n", res);
			free(tmp);
		}
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
		return (expand(node->operand->l_child, env) +
			expand(node->operand->r_child, env));
	if (exp_args(node->command->arguments, env)
		/*|| exp_rds(node->command->redirects, env)*/)
		return (-1);
	return (0);
}
