/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 00:40:37 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/04 01:13:51 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_headvar(t_data *data, int len, char *var)
{
	int		i;

	i = 0;
	while (data->env->envtab[i] && \
		(ft_strncmp(var, data->env->envtab[i], ft_strlen(var))
			|| data->env->envtab[i][len] != '='))
		i++;
	if (data->env->envtab[i])
		return (ft_strdup(&data->env->envtab[i][ft_strlen(var) + 1]));
	return (ft_strdup(""));
}

char	*append_var(t_data *data, char *argument)
{
	int		i;
	char	*tab[4];

	i = 0;
	while (argument[i] != '+')
		i++;
	tab[3] = malloc(sizeof(char) * (i + 2));
	if (!tab[3])
		return (NULL);
	ft_strlcpy(tab[3], argument, i + 1);
	tab[2] = get_headvar(data, i, tab[3]);
	tab[0] = ft_strdup(&argument[i + 2]);
	tab[1] = ft_strjoin(tab[2], tab[0]);
	if (tab[2])
		free(tab[2]);
	if (tab[0])
		free(tab[0]);
	if (!tab[1])
		return (free(tab[3]), NULL);
	tab[3][i] = '=';
	tab[3][i + 1] = '\0';
	tab[2] = ft_strjoin(tab[3], tab[1]);
	if (!tab[2])
		return (free(tab[3]), free(tab[1]), NULL);
	return (free(tab[3]), free(tab[1]), tab[2]);
}
