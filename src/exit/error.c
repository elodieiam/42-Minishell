/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:37:54 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/28 14:48:37 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_error(t_data *data, t_token *toklist)
{
	char	*tok_str;

	if (!toklist)
		tok_str = "newline";
	else
		tok_str = toklist->string;
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(tok_str, 2);
	write(2, "'\n", 2);
	return (exit_line(data, SYNTAX_ERR));
}

int	fatal_error(t_data *data, char *cmd)
{
	ft_putstr_fd(COL_RED, 2);
	ft_putstr_fd("minishell: fatal error caused by ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	ft_putstr_fd(COL_RES, 2);
	g_err_code = UNKNOWN_ERR;
	return (exit_line(data, UNKNOWN_ERR));
}
