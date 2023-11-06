/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:54:04 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/06 10:11:10 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	errnl(int exit_code, char *error_str)
{
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
	return (exit_code);
}

int	exit_line(t_data *data, int exit_code)
{
	if (!data)
		return (exit_code);
	if (data->prompt)
		free(data->prompt);
	if (data->tokens)
		free_tokens(&(data->tokens));
	if (data->tree)
		free_tree(data);
	if (data->lst_env)
		free_env(&(data->lst_env));
	data->err_code = exit_code;
	return (exit_code);
}
