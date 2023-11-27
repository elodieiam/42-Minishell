/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:31:18 by taospa            #+#    #+#             */
/*   Updated: 2023/11/27 14:22:32 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_pwd(t_data *data, t_node *node)
{
	char	*pwd;

	if (node->command->arguments[1])
		return (exit_line(data, errnl(1, "pwd: too many arguments")));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (exit_line(data, errnl(MALLOC_ERR, "malloc failed")));
	if (!getcwd(pwd, PATH_MAX))
		return (free(pwd), exit_line(data, errnl(UNKNOWN_ERR, "fatal: getcwd failed")));
	if (printf("%s\n", pwd) ==  -1)
		return (free(pwd), exit_line(data, errnl(UNKNOWN_ERR, "fatal: getcwd failed")));
	free(pwd);
	return (0);
};
