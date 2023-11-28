/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:33:51 by taospa            #+#    #+#             */
/*   Updated: 2023/11/28 16:41:52 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->prompt = NULL;
	data->err_code = 0;
	data->tokens = NULL;
	data->tree = NULL;
	data->tmp_tree = NULL;
	data->env = malloc(sizeof(t_env));
	if (!data->env)
		return (free(data), NULL);
	data->env->envtab = env;
	data->env->malloced = 0;
	return (data);
}
void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handler);
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	t_data	*data;

	if (ac != 1)
		return (errnl(1, "Error : no arguments required"));
	(void)av;
	data = init_data(env);
	init_signal();
	if (!data)
		return (-1);
	while (1)
	{
		data->prompt = readline("minishell>");
		if (!data->prompt)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->prompt);
		data->tokens = ft_lexer(data->prompt);
		parse(data);
		expand(data->tree, data->env->envtab);
		pretty_print_ast(data->tree, "");
		data->err_code = exec(data);
		exit_line(data, data->err_code);
	}
	return (exit_all(data, data->err_code));
}
