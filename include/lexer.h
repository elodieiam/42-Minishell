/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:30:00 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/16 15:31:33 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

typedef struct s_token
{
	t_toktype		type;
	char			*string;
	struct s_token	*next;
}	t_token;


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
