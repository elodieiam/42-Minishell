/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:45 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/01/03 14:48:08 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "structs.h"

/*-------------asterisk.c-------------*/
char	**expand_wildcard(t_data *data, char *str);

/*--------------expand.c--------------*/
int		expand(t_data *data, t_node *node, char **env);
char	*apply_exp(t_data *data, char *str, char **env);

/*-----------expand_utils.c-----------*/
int		is_varsep(char c);
int		nonvarlen(char *str, int quote, int i);
char	**sumtab(t_data *data, char **t1, char **t2);
char	**tab_addback(char **tab, char *new);

/*----------expand_process.c----------*/
char	*expand_exceptions(char *str, int *i);
char	*get_nonvarstr(char *str, int *i, int *quote);
char	*get_varstr(char *str, int *i, char **env);
char	*rmhdquotes(char *str);

#endif
