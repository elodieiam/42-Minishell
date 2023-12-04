/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:45 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/04 22:46:00 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "structs.h"

/*--------------expand.c--------------*/
int		expand(t_node *node, char **env);

/*------------exceptions.c------------*/
char	*expand_exceptions(char *str, int *i);
char	**expand_wildcard(char *str);
char	**sumtab(char **t1, char **t2);
char	**tab_addback(char **tab, char *new);

/*-----------expand_utils.c-----------*/
int		is_varsep(char c);
int		nonvarlen(char *str, int quote, int i);
char	*get_nonvarstr(char *str, int *i, int *quote);
char	*get_varstr(char *str, int *i, char **env);

#endif
