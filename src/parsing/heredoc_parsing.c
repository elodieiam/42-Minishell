/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:09:32 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/11 11:19:54 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_handler_heredoc(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		printf("Je suis sigint\n");
		g_err_code = 130;
	}
}

int	handle_heredoc_sigs(int childval)
{
	if (WIFSIGNALED(childval))
	{
		if (WTERMSIG(childval) == SIGINT)
		{
			g_err_code = 130;
		}
			return (1);
	}
	return (0);
}

int	check_heredoc2(t_data *data, t_node *node, int fd)
{
	int		pid;
	int		childval;
	char	*line;
	char	*res;
	char	*lim;

	childval = 0;
	line = NULL;
	res = NULL;
	if (!node->command->redirects)
		return (0);
	if (node->command->redirects->rdtype == 9)
	{
		lim = node->command->redirects->files[0];
		pid = fork();
		if (pid == (-1))
			return (1);
		signal(SIGINT, SIG_IGN);
		if (pid == 0)
		{
			node->command->redirects->heredoc_name = get_heredoc_name();
		fd = open(node->command->redirects->heredoc_name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == (-1))
				return (1);
			signal(SIGINT, SIG_DFL);
			while (1)
			{
				line = readline("> ");
				if (!line)
					return (exit_heredoc(data, node, fd));
				if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
				{
					free (line);
					break ;
				}
				res = ft_strjoin(line, "\n");
				if (!res)
					return (1);
				write(fd, res, ft_strlen(res));
				free (line);
				free (res);
			}
			free(node->command->redirects->heredoc_name);
			return (exit_all(data, g_err_code));
		}
		waitpid(pid, &childval, 0);
		if (handle_heredoc_sigs(childval))
		{
			close(fd);
			unlink(node->command->redirects->heredoc_name);
			return (WTERMSIG(childval) + 128);
		}
	}
	return (0);
}

int	do_or(t_data *data, t_node *tree)
{
	if (check_heredoc(data, tree->operand->l_child))
		return (check_heredoc(data, tree->operand->r_child));
	return (g_err_code);
}

int	do_and(t_data *data, t_node *tree)
{
	if (!check_heredoc(data, tree->operand->l_child))
		return (check_heredoc(data, tree->operand->r_child));
	return (g_err_code);
}

int	check_heredoc(t_data *data, t_node *node)
{
	if (node->is_command && node->command->redirects)
		g_err_code = check_heredoc2(data, node, node->command->redirects->fd);
	else if (!node->is_command)
	{
		if (node->operand->optype == T_OR)
			g_err_code = do_or(data, node);
		if (node->operand->optype == T_AND)
			g_err_code = do_and(data, node);
	}
	return (0);
}
