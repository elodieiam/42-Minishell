/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:54:04 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/23 16:28:34 by tsaint-p         ###   ########.fr       */
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
	if (data->tokens)
		free_tokens(&(data->tokens));
	if (data->tree)
		free_tree(data);
	data->err_code = exit_code;
	return (exit_code);
}
