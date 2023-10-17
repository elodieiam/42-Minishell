/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:28:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/17 11:52:02 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "lexer.h"

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

struct s_operand
{
	t_toktype		optype;
	struct s_node	*l_child;
	struct s_node	*r_child;
};

typedef struct s_node
{
	int					is_command;
	struct s_operand	operand;
	t_command			command;
} 	t_node;


/*----------------parsing.c---------------*/

#endif
