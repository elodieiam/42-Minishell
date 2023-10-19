/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:28:57 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/18 19:04:56 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "lexer.h"

/*----------------parsing.c---------------*/
int			parse(t_data *data);
t_node		*new_node(int is_command);
void		print_tree(t_node *node, int depth);

/*----------------rdlist.c---------------*/
void		free_rdlist(t_rdlist **list);
void		rdlist_add_back(t_rdlist **list, t_rdlist *new_rd);
t_rdlist	*new_rd(t_toktype rd_type, char *file);

/*----------------init_cmd.c---------------*/

t_node		*init_cmd_node(t_token *cmd_tok, int malloc_size);
t_node		*handlecommand(t_data *data, t_token *current_tok);

#endif
