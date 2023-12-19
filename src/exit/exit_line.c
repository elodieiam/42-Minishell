/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:54:04 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/19 13:04:23 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// write : minishell: command: arg: error\n
int	ferrnl(char *command, char *arg, char *error, int ret_val)
{
	write(2, "minishell: ", 11);
	if (command)
	{
		write(2, command, ft_strlen(command));
		write(2, ": ", 2);
		if (arg)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": ", 2);
		}
	}
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (ret_val);
}

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
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->tokens)
		free_tokens(&(data->tokens));
	if (data->tree)
		free_tree(data);
	// if (data->tmp_tree)
		// free_tree(data);
	if (data->pidlist)
		free_pidlist(&(data->pidlist));
	reset_rds(&(data->fds), NULL);
	g_err_code = exit_code;
	return (exit_code);
}

int	exit_all(t_data *data, int exit_code)
{
	exit_line(data, exit_code);
	if (data->env)
	{
		if (data->env->malloced)
			free_dchartab(data->env->envtab);
		free(data->env);
		data->env = NULL;
	}
	free(data);
	exit(exit_code);
}
