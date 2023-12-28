/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:31:18 by taospa            #+#    #+#             */
/*   Updated: 2023/12/28 19:05:25 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_pwd(t_data *data, t_node *node)
{
	char	*pwd;

	if (node->arguments[1])
		return (exit_line(data, errnl(1, "pwd: too many arguments")));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (fatal_error(data, "malloc"));
	if (!getcwd(pwd, PATH_MAX))
		return (free(pwd), fatal_error(data, "getcwd"));
	if (printf("%s\n", pwd) == -1)
		return (free(pwd), exit_line(data,
				errnl(UNKNOWN_ERR, "fatal: getcwd failed")));
	free(pwd);
	return (0);
}
