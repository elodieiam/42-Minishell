/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:36:08 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/08 18:16:06 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//operators 4
//redirection 7
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

typedef struct s_env
{
	int		malloced;
	char	**envtab;
}	t_env;

typedef struct s_token
{
	t_toktype		type;
	char			*string;
	struct s_token	*next;
}	t_token;

typedef struct s_rdlist
{
	char			**files;
	int				fd;
	t_toktype		rdtype;
	struct s_rdlist	*next;
}	t_rdlist;

typedef struct s_command
{
	char		**arguments;
	t_rdlist	*redirects;
}	t_command;

typedef struct s_operand
{
	t_toktype		optype;
	struct s_node	*l_child;
	struct s_node	*r_child;
}	t_operand;

typedef struct s_node
{
	int			is_command;
	int			subshell;
	t_operand	*operand;
	t_command	*command;
}	t_node;

typedef struct s_data
{
	char			*prompt;
	t_token			*tokens;
	t_node			*tree;
	t_node			*tmp_tree;
	t_env			*env;
}	t_data;

#endif
