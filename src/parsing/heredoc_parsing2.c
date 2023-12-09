/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:20:57 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/09 21:51:52 by elrichar         ###   ########.fr       */
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

int	exit_heredoc(t_data *data, t_node *node, int fd)
{
	printf("minishell: warning: heredoc delimited by EOF\n");
	close(fd);
	unlink(node->command->redirects->heredoc_name);
	free(node->command->redirects->heredoc_name);
	return (exit_all(data, g_err_code));
}

