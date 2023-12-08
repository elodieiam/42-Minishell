/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/12/08 21:10:37 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned char	g_err_code;

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->prompt = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->tmp_tree = NULL;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
		return (free(data), NULL);
	data->env->envtab = env;
	data->env->malloced = 0;
	g_err_code = 0;
	return (data);
}

int	process_line(t_data *data)
{
	signal(SIGINT, ft_handler);
	data->prompt = readline("minishell>");
	if (!data->prompt)
		return (1);
	add_history(data->prompt);
	data->tokens = ft_lexer(data->prompt);
	if (!data->tokens || parse(data))
		return (1);
	expand(data->tree, data->env->envtab);
	//pretty_print_ast(data->tree, "");
	check_heredoc(data, data->tree);
	g_err_code = exec(data, data->tree);
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
		return (free(tab), MALLOC_ERR);
	tab[1] = ft_strjoin("SHLVL=", currlvl);
	free(currlvl);
	if (!tab[1])
		return (free(tab), MALLOC_ERR);
	g_err_code = exec_export(data, tab);
	free(tab[1]);
	free(tab);
	return (g_err_code);
}

int	main(int ac, char *av[], char **env)
{
	t_data	*data;
	int		exit;

	if (ac != 1)
		return (errnl(1, "Error : no arguments required"));
	(void)av;
	data = init_data(env);
	if (!data)
		return (-1);
	init_signal();
	exit = 0;
	if (increment_shlvl(data))
		return (exit_line(data, g_err_code));
	while (!exit)
		exit = process_line(data);
	printf("exit\n");
	return (exit_all(data, g_err_code));
}
