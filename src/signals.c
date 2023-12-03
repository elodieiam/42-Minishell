/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:02:42 by taospa            #+#    #+#             */
/*   Updated: 2023/12/03 19:05:30 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_err_code = 130;
	}
}

int	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handler);
	return (0);
}

int	handle_child_sigs(int childval)
{
	if (WIFSIGNALED(childval))
	{
		if (WTERMSIG(childval) == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (WTERMSIG(childval) == SIGINT)
			printf("\n");
		return (1);
	}
	return (0);
}

void	sig_handler_child(int sig)
{
	(void)sig;
}
