/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/09 19:16:38 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_equal_sign(char **str)
{
	if (**str == '=')
		return (0);
	while (**str && **str != '=')
		(*str)++;
	if (!**str)
		return (0);
	if (**str == '=' && *(*str + 1) && *(*str + 1) != '=')
		return (1);
	return (0);
}

static int	check_nb_quotes(char *str)
{
	int	nb_quotes;

	nb_quotes = 0;
	if (*str == '"')
	{
		while (*str)
		{
			if (*str == '"')
				nb_quotes++;
			str++;
		}
	}
	else if (*str == 39)
	{
		while (*str)
		{
			if (*str == 39)
				nb_quotes++;
			str++;
		}
	}
	if (nb_quotes != 2 && nb_quotes != 0)
		return (0);
	return (1);
}

static int	check_quotes_pos(char *str)
{
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		if (*str == '"' && !*(str + 1))
			return (1);
	}
	else if (*str == 39)
	{
		str++;
		while (*str && *str != 39)
			str++;
		if (*str == 39 && !*(str + 1))
			return (1);
	}
	else
	{
		while (*str)
			str++;
		if (*str == '"' || *str == 39)
			return (0);
	}
	return (1);
}

static int	is_valid_arg(char *str)
{
	if (!check_equal_sign(&str))
		return (0);
	if (!check_nb_quotes(str + 1))
		return (0);
	if (!check_quotes_pos(str + 1))
		return (0);
	return (1);
}

int	update_env(t_data *data, t_node *node)
{
	char	**new_env;
	int		nb_arg;

	new_env = NULL;
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
		nb_arg++;
	new_env = malloc(sizeof(char *) * (nb_arg + 2));
	if (!new_env)
		return (0);
	nb_arg = 0;
	while (data->env->envtab[nb_arg])
	{
		new_env[nb_arg] = strdup(data->env->envtab[nb_arg]);
		nb_arg++;
	}
	new_env[nb_arg] = node->command->arguments[1];
	new_env[nb_arg + 1] = NULL;
	if (data->env->malloced == 1)
		free_dchartab(data->env->envtab);
	data->env->envtab = new_env;
	data->env->malloced = 1;
	return (1);
}


//handle error if malloc fails
int	exec_export(t_data *data, t_node *node)
{
	int	i;

	i = 1;
	(void)data;
	// if (!node->command->arguments[i])
	// 	return (display_env(data), 0);
	while (node->command->arguments[i])
	{
		if (is_valid_arg(node->command->arguments[i]))
		{
			if (!update_env(data, node))
				return (1);
		}
		else
			return (1);
		i++;
	}
	i = 0;
	while (data->env->envtab[i])
	{
		printf("%s\n", data->env->envtab[i]);
		i++;
	}
	return (0);
}
