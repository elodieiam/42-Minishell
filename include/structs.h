/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:36:08 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/15 20:13:19 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//operators >= 4
//redirection >= 7
typedef enum e_toktype
{
	T_START = 0,
	T_WORD = 1,
	T_OPPAR = 2,
	T_CLPAR = 3,
	T_PIPE = 4,
	T_OR = 5,
	T_AND = 6,
	T_OPCHEV = 7,
	T_CLCHEV = 8,
	T_DOPCHEV = 9,
	T_DCLCHEV = 10,
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
	char			*file;
	int				fd;
	char			*heredoc_name;
	t_toktype		rdtype;
	struct s_rdlist	*next;
}	t_rdlist;

typedef struct s_operand
{
	t_toktype		optype;
	struct s_node	*l_child;
	struct s_node	*r_child;
}	t_operand;

typedef struct s_node
{
	int				subshell;
	char			**arguments;
	t_operand		*operand;
	t_rdlist		*redirects;
	struct s_node	*parent;
}	t_node;

typedef struct s_pidlist
{
	int					pid;
	struct s_pidlist	*next;
}	t_pidlist;

typedef struct s_data
{
	char			*prompt;
	t_token			*tokens;
	t_node			*tree;
	t_node			*tmp_tree;
	t_env			*env;
	t_pidlist		*pidlist;
}	t_data;

#endif
