/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:52:47 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/15 20:02:20 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*freengonextok(t_token *token)
{
	t_token	*next_tok;

	if (!token)
		return (NULL);
	next_tok = token->next;
	free(token->string);
	free(token);
	return (next_tok);
}

t_toktype	ft_gettype(char *string)
{
	if (*string == '(')
		return (T_OPPAR);
	if (*string == ')')
		return (T_CLPAR);
	if (!ft_strncmp(string, "|", 2))
		return (T_PIPE);
	if (!ft_strncmp(string, "||", 3))
		return (T_OR);
	if (!ft_strncmp(string, "&&", 3))
		return (T_AND);
	if (!ft_strncmp(string, "<", 2))
		return (T_OPCHEV);
	if (!ft_strncmp(string, ">", 2))
		return (T_CLCHEV);
	if (!ft_strncmp(string, "<<", 3))
		return (T_DOPCHEV);
	if (!ft_strncmp(string, ">>", 3))
		return (T_DCLCHEV);
	return (T_WORD);
}

//if !string useful ?
t_token	*ft_newtoken(char *string)
{
	t_token	*token;

	if (!string)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->string = string;
	token->type = ft_gettype(token->string);
	token->next = NULL;
	return (token);
}

void	ft_addtokback(t_token **tok_list, t_token *token)
{
	t_token	*current_tok;

	if (!*tok_list)
	{
		*tok_list = token;
		return ;
	}
	current_tok = *tok_list;
	while (current_tok->next)
		current_tok = current_tok->next;
	current_tok->next = token;
}

int	is_empty(char *cmd_line)
{
	if (!cmd_line)
		return (-1);
	while (ft_isspace(*cmd_line))
		cmd_line++;
	return (!*cmd_line);
}
