/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2024/01/04 15:02:35 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_err_code;

int	cherr_code(int err_code)
{
	g_err_code = err_code;
	return (err_code);
}

int	process_line(t_data *data)
{
	init_signal();
	data->prompt = readline("\033[1;94mminishell> \033[0m");
	if (!data->prompt)
		return (1);
	if (*data->prompt && *data->prompt != '\n')
		add_history(data->prompt);
	data->tokens = ft_lexer(data, data->prompt);
	if (!data->tokens)
		return (exit_line(data, g_err_code), 0);
	if (parse(data, &data->tree))
		return (exit_line(data, g_err_code), 0);
	if (data->tokens)
		return (syntax_error(data, data->tokens), 0);
	// pretty_print_ast(data->tree, "");
	if (open_heredocs(data, data->tree))
		return (exit_line(data, g_err_code), 0);
	if (exec(data, data->tree))
		return (exit_line(data, g_err_code), 0);
	exit_line(data, g_err_code);
	return (0);
}

int	increment_shlvl(t_data *data)
{
	int		i;
	char	*currlvl;
	char	**tab;

	i = 0;
	tab = ft_calloc(3, sizeof(char *));
	while (data->env->envtab[i] && \
			ft_strncmp(data->env->envtab[i], "SHLVL=", 6))
		i++;
	if (!data->env->envtab[i])
		currlvl = ft_strdup("1");
	else
		currlvl = ft_itoa(ft_atoi(&(data->env->envtab[i][6])) + 1);
	if (!currlvl)
		return (free(tab), UNKNOWN_ERR);
	tab[1] = ft_strjoin("SHLVL=", currlvl);
	free(currlvl);
	if (!tab[1])
		return (free(tab), UNKNOWN_ERR);
	g_err_code = exec_export(data, tab);
	free(tab[1]);
	free(tab);
	return (g_err_code);
}

int	prep_stdinnout(void)
{
	int		fd;

	if (!isatty(0))
		exit(0);
	else
	{
		fd = open("/dev/stdin", O_RDWR);
		if (fd == -1)
			return (UNKNOWN_ERR);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), UNKNOWN_ERR);
		close(fd);
	}
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	t_data	*data;
	int		exit_val;

	if (ac != 1)
		return (errnl(1, "Error : no arguments required"));
	(void)av;
	data = init_data(env);
	if (!data)
		return (UNKNOWN_ERR);
	if (prep_stdinnout())
		exit_all(data, fatal_error(data, "minishell launch"));
	// init_signal();
	if (increment_shlvl(data))
		return (exit_line(data, g_err_code));
	exit_val = 0;
	while (!exit_val)
	{
		exit_val = process_line(data);
		// printf("err code: %d\n", g_err_code);
	}
	printf("exit\n");
	return (exit_all(data, g_err_code));
}
