/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:28:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/23 16:49:01 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "lexer.h"

/*----------------parsing.c---------------*/
int			parse(t_data *data);

/*-----------------tree.c----------------*/
t_node		*new_node(int is_command);
void		free_tree(t_data *data);
int			free_node(t_node *node);

/*----------------rdlist.c---------------*/
void		free_rdlist(t_rdlist **list);
void		rdlist_add_back(t_rdlist **list, t_rdlist *new_rd);
t_rdlist	*new_rd(t_toktype rd_type, char *file);

/*----------------cmd_node.c---------------*/
t_node		*init_cmd_node(t_token **tokens, int malloc_size);
t_node		*handlecommand(t_data *data);
void		free_args(char ***args);

/*----------------cmd_node.c---------------*/
t_node		*handleoperator(t_data *data);

#endif
