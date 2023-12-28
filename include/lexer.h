/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:30:00 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/28 16:15:44 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structs.h"
/*----------------lexer.c---------------*/
t_token	*ft_lexer(t_data *data, char *cmd_line);
void	printlist(t_token *token); //temp
void	free_tokens(t_token **tokens);

/*----------------tokens.c---------------*/
void	ft_addtokback(t_token **tok_list, t_token *token);
t_token	*ft_newtoken(char *string);
t_token	*freengonextok(t_token *token);
int		is_empty(char *cmd_line);

/*----------------lexer_utils.c----------*/
int		ft_isspace(int ch);
int		ft_iswordsep(int ch);

#endif
