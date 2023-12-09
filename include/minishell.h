/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:47:46 by taospa            #+#    #+#             */
/*   Updated: 2023/12/09 16:14:38 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>

# include "../libft/libft.h"
# include "parsing.h"
# include "exit.h"
# include "exec.h"
# include "expand.h"

# define SUCCESS 0,
# define UNSPEC_ERR 1
# define SYNTAX_ERR 2
# define MALLOC_ERR 125
# define PERM_ERR 126
# define NOTFOUND_ERROR 127
# define SIGINT_ERR 128
# define UNKNOWN_ERR 255

extern unsigned char	g_err_code;

int	check_heredoc(t_data *data, t_node *node);

/*---------------debug.c------------*/
char	*tta(t_toktype int_type);
void	pretty_print_ast(t_node *node, char *prefix);
void	print_tokens(t_token *tokens);
void	print_dchartab(char **tab);

/*---------------signals.c---------*/
void	ft_handler(int signum);
int		init_signal(void);
int		handle_child_sigs(int childval);
void	sig_handler_child(int sig);

#endif
