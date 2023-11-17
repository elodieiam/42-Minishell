/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:50 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/17 20:38:23 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_sepstring(char **cmd_line)
{
	int		i;
	char	first_sep;
	char	*res;

	i = 0;
	first_sep = **cmd_line;
	if (first_sep == ')' || first_sep == '(')
	{
		res = malloc(2 * sizeof(char));
		ft_strlcpy(res, &first_sep, 2);
		(*cmd_line)++;
	}
	else
	{
		while ((*cmd_line)[i] == first_sep && i < 2)
			i++;
		res = ft_calloc(i + 1, sizeof(char));
		if (!res)
			return (NULL);
		i = 0;
		while (**cmd_line == first_sep && i < 2)
			res[i++] = *((*cmd_line)++);
	}
	return (res);
}

char	*fill_string(char *dest, char **cmd_line, int quote)
{
	int	i;

	i = 0;
	if (**cmd_line == 34 || **cmd_line == 39)
	{
		dest[i++] = **cmd_line;
		quote = *((*cmd_line)++);
	}
	while (**cmd_line && !(!quote && ft_iswordsep(**cmd_line)))
	{
		if (**cmd_line == quote)
			quote = 0;
		dest[i++] = *((*cmd_line)++);
	}
	if (quote && **cmd_line == quote)
		dest[i++] = *(*cmd_line)++;
	dest[i] = 0;
	return (dest);
}

char	*ft_getstring(char **cmd_line)
{
	int		quote;
	int		i;
	char	*res;

	quote = 0;
	i = 0;
	res = NULL;
	while (ft_isspace(**cmd_line))
		(*cmd_line)++;
	if (ft_iswordsep(**cmd_line))
		return (get_sepstring(cmd_line));
	if ((*cmd_line)[i] == 34 || (*cmd_line)[i] == 39)
		quote = (*cmd_line)[i++];
	while ((*cmd_line)[i] && !(!quote && ft_iswordsep((*cmd_line)[i])))
		if ((*cmd_line)[i++] == quote)
			quote = 0;
	if (quote && (*cmd_line)[i] == quote)
		i++;
	res = ft_calloc(i + 1, sizeof(char));
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
	while (*cmd_line && !is_empty(cmd_line))
	{
		tok = ft_newtoken(ft_getstring(&cmd_line));
		if (!tok)
			return (NULL);
		ft_addtokback(&tok_list, tok);
	}
	return (tok_list);
}
