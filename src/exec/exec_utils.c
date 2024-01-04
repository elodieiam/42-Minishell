/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:21:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/04 15:16:43 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_path(const char *str)
{
	if (!str)
		return (0);
	while (*str && *str != '/')
		str++;
	if (*str)
		return (1);
	return (0);
}

char	*bettercat(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len1 + len2 + 1)
	{
		if (i < len1)
			res[i] = s1[i];
		else if (i == len1)
			res[i] = '/';
		else
			res[i] = s2[i - len1 - 1];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	end_export_lastarg(t_data *data, char **tab)
{
	int		fd;
	int		tmp;

	fd = open("/dev/null", O_WRONLY);
	tmp = dup(STDERR_FILENO);
	dup2(fd, STDERR_FILENO);
	close(STDERR_FILENO);
	if (exec_export(data, tab))
		return (free(tab[1]), free(tab), dup2(STDERR_FILENO, tmp),
			close(fd), close(tmp), g_err_code);
	dup2(STDERR_FILENO, tmp);
	close(fd);
	close(tmp);
	free(tab[1]);
	free(tab);
	return (0);
}

// what if arg[0] == NULL ?
// print error ? exit line ?
int	export_lastarg(t_data *data, t_node *node)
{
	char	**tab;
	int		cpt;

	if (!node->arguments || !node->arguments[0])
		return (g_err_code);
	tab = ft_calloc(3, sizeof(char *));
	if (!tab)
		return (fatal_error(data, "malloc"));
	cpt = 0;
	while (node->arguments[cpt + 1])
		cpt++;
	tab[0] = "export";
	tab[1] = ft_strjoin("_=", node->arguments[cpt]);
	if (!tab[1])
		return (free(tab), fatal_error(data, "malloc"));
	return (end_export_lastarg(data, tab));
}

void	free_dchartab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
