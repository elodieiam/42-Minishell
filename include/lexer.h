/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:30:00 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/17 14:37:59 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structs.h"
/*----------------lexer.c---------------*/
t_token	*ft_lexer(char *cmd_line);
void	printlist(t_token *token); //temp
void	free_tokens(t_token **tokens);

/*----------------tokens.c---------------*/
void	ft_addtokback(t_token **tok_list, t_token *token);
t_token	*ft_newtoken(char *string);

/*----------------lexer_utils.c----------*/
int		ft_isspace(int ch);
int		ft_iswordsep(int ch);

#endif
