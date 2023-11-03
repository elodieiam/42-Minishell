/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:36:08 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/03 13:31:30 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_toktype
{
	T_START = 0,
	T_WORD,
	T_OPPAR,
	T_CLPAR,
//operators 4
	T_PIPE,
	T_OR,
	T_AND,
//redirection 7
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

typedef struct s_rdlist
{
	char			*file;
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
} 	t_node;

typedef struct s_data
{
	int		err_code;
	t_token *tokens;
	t_node	*tree;
	t_node	*tmp_tree;
}	t_data;

#endif
