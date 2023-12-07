/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:25 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/07 15:40:05 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_simple_heredoc(char *lim)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("Heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == (-1))
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			free (line);
			break ;
		}
		free (line);
	}
	close(fd);
	unlink("Heredoc");
	return (0);
}
