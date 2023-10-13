/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:50 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/13 17:42:47 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fill_string(char *dest, char **cmd_line, int quote)
{
	int	i;

	i = 0;
	while (ft_isspace(**cmd_line))
		(*cmd_line)++;
	if (**cmd_line == 34 || **cmd_line == 39)
		quote = *(*cmd_line++);
	while (**cmd_line && (!quote && !ft_iswordsep(**cmd_line))
		&& **cmd_line != quote)
	{
		dest[i] = *(*cmd_line++);
		i++;
	}
	return (dest);
}

char	*ft_getstring(char **cmd_line)
{
	int	quote;
	int	i;
	char	*res;

	quote = 0;
	i = 0;
	res = NULL;
	while (ft_isspace((*cmd_line)[i]))
		i++;
	if ((*cmd_line)[i] == 34 || (*cmd_line)[i] == 39)
		quote = (*cmd_line)[i++];
	while ((*cmd_line)[i] && (!quote && !ft_iswordsep((*cmd_line)[i]))
		&& (*cmd_line)[i] != quote)
		i++;
	res = malloc(sizeof(char) * i);
	if (!res)
		return (NULL);
	return (fill_string(res, cmd_line, quote));
}

t_token	*ft_lexer(char *cmd_line)
{
	t_token	*tok_list;
	t_token	*tok;

	tok_list = NULL;
	tok = NULL;
	if (!cmd_line)
		return (NULL);
	while (*cmd_line)
	{
		tok = ft_newtoken(ft_getstring(&cmd_line));
		if (!tok)
			return (NULL);
		ft_addtokback(&tok_list, tok);
	}
	return (tok_list);
}
