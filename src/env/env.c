/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:25:15 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/03 16:07:10 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env **lst_env)
{
	t_env	*tmp;

	if (!lst_env)
		return ;
	while (*lst_env)
	{
		tmp = *lst_env;
		(*lst_env) = (*lst_env)->next;
		free(tmp->element);
		free(tmp);
	}
}

t_env	*new_var(char *string)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->element = ft_strdup(string);
	var->next = NULL;
	return (var);
}

void	ft_addvarback(t_env **var_list, t_env *var)
{
	t_env	*current;

	if (!*var_list)
	{
		*var_list = var;
		return ;
	}
	current = *var_list;
	while (current->next)
		current = current->next;
	current->next = var;
}

int	get_env(char *env[], t_data *data)
{
	t_env	*var_list;
	t_env	*var;
	int		i;
	
	var_list = NULL;
	var = NULL;
	i = 0;
	while (env[i])
	{
		var = new_var(env[i]);
		if (!var)
			return (1);
		ft_addvarback(&var_list, var);
		i++;
	}
	data->lst_env = var_list;
	return (0);
}