/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:35:58 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/12 12:19:56 by tsaint-p         ###   ########.fr       */
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

void	exit_heredoc(t_node *node)
{
	printf("minishell: warning: heredoc delimited by EOF\n");
	close(node->redirects->fd);
	unlink(node->redirects->heredoc_name);
}
