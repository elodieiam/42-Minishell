/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:35:58 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/01 23:53:03 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

char	*heredoc_urandpath(char **heredoc_name, int fd_urand)
{
	char	*tmp;
	char	buffer;
	int		i;

	i = 0;
	buffer = '\0';
	while (++i < 15)
	{
		if (read(fd_urand, &buffer, 1) == -1)
		{
			g_err_code = UNKNOWN_ERR;
			return (NULL);
		}
		(*heredoc_name)[i] = ((unsigned char) buffer % 26) + 97;
	}
	tmp = *heredoc_name;
	*heredoc_name = ft_strjoin("/tmp/", *heredoc_name);
	free(tmp);
	if (!heredoc_name)
	{
		g_err_code = UNKNOWN_ERR;
		return (NULL);
	}
	return (*heredoc_name);
}

// TODO: print errors 
int	fill_heredoc_name(int fd_urand, char **heredoc_name)
{
	*heredoc_name = heredoc_urandpath(heredoc_name, fd_urand);
	if (!heredoc_name && g_err_code == UNKNOWN_ERR)
		return (UNKNOWN_ERR);
	else if (!heredoc_name)
		return (UNKNOWN_ERR);
	return (0);
}

char	*get_heredoc_name(t_data *data)
{
	char	*heredoc_name;
	int		fd_urand;

	fd_urand = open("/dev/urandom", O_RDONLY);
	if (fd_urand == -1)
	{
		g_err_code = PERM_ERR;
		return (NULL);
	}
	heredoc_name = ft_calloc(16, sizeof(char));
	if (!heredoc_name)
	{
		fatal_error(data, "malloc");
		return (close(fd_urand), NULL);
	}
	heredoc_name[0] = '.';
	g_err_code = fill_heredoc_name(fd_urand, &heredoc_name);
	printf("hd name = %s\n", heredoc_name);
	return (close(fd_urand), heredoc_name);
}

int	exit_heredoc(t_rdlist *rd, t_data *data, int g_err_code)
{
	printf("minishell: warning: heredoc delimited by EOF\n");
	close(rd->fd);
	return (exit_all(data, g_err_code));
}
