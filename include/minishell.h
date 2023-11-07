/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:47:46 by taospa            #+#    #+#             */
/*   Updated: 2023/11/07 16:51:53 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "exit.h"
# include "exec.h"
# include "expand.h"

char	*tta(t_toktype int_type);
void    pretty_print_ast(t_node *node, char *prefix);
void	print_tokens(t_token *tokens);

#endif
