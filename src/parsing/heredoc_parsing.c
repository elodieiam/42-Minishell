/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:09:32 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/08 21:23:48 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_heredoc_name(void)
{
	static int	i;
	char		*heredoc_number;
	char		*heredoc_name;

	heredoc_number = ft_itoa(i++);
	heredoc_name = ft_strjoin(".tmp_heredoc_", heredoc_number);
	free (heredoc_number);
	return (heredoc_name);
}

int	check_heredoc2(t_node *node)
{
	char	*lim;
	int		fd;
	char	*line;
	char	*res;

	lim = node->command->redirects->files[0];
	if (node->command->redirects->rdtype == 9)
	{
		node->command->redirects->heredoc_name = get_heredoc_name();
		line = NULL;
		fd = open(node->command->redirects->heredoc_name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == (-1))
			return (1);
		node->command->redirects->fd = fd;
		while (1)
		{
			line = readline("> ");
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
	if (node->is_command)
		g_err_code = check_heredoc2(node);
	else
	{
		if (node->operand->optype == T_OR)
			g_err_code = do_or(data, node);
		if (node->operand->optype == T_AND)
			g_err_code = do_and(data, node);
	}
	return (0);
}
