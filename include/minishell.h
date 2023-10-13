/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:47:46 by taospa            #+#    #+#             */
/*   Updated: 2023/10/13 17:42:36 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum e_toktype
{
	T_START = 0,
	T_WORD,
	T_OPPAR,
	T_CLPAR,
	T_PIPE,
	T_OR,
	T_AND,
	T_OPCHEV,
	T_CLCHEV,
	T_DOPCHEV,
	T_DCLCHEV
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*string;
	struct s_token	*next;
}	t_token;

/*----------------lexer.c---------------*/
t_token	*ft_lexer(char *cmd_line);

/*----------------tokens.c---------------*/
void	ft_addtokback(t_token **tok_list, t_token *token);
t_token	*ft_newtoken(char *string);

/*----------------lexer_utils.c----------*/
int		ft_isspace(int ch);
int		ft_iswordsep(int ch);

#endif
