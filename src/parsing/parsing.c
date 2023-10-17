/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:26:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/10/17 12:24:51 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handlepar(t_token *token, int *parenth)
{
	if (token->type == T_OPPAR )
		(*parenth)++;
	if (token->type == T_CLPAR)
		(*parenth)--;
	return ;
	
}
void	handlewords(t_data *data, t_token *current_tok)
{
	int	squotes;
	int	dquotes;

	squotes = 0;
	dquotes = 0;
	//to continue
}

int	parse(t_data *data)
{
	int		parenth;
	t_token	*current_tok;
	
	parenth = 0;
	current_tok = data->tokens;
	while (current_tok)
	{
		handlepar(current_tok, &parenth);
		handlewords(data, current_tok);
		current_tok = current_tok->next;
	}
	return (0);
}

t_node	*new_node(int is_command)
{
	t_node	*node;

	node = malloc (sizeof(t_node));
	if (!node)
		return (NULL);
	if (is_command)
	{
		node->is_command = 1;
		node->command.arguments = NULL;
		node->command.redirects = NULL;
	}
	else
	{
		node->is_command = 0;
		node->operand.l_child = NULL;
		node->operand.r_child = NULL;
		node->operand.optype = 0;
	}
	return (node);
}

void	print_tree(t_node *node, int depth)
{
	if (!node)
		return ;
	while (depth--)
		printf("\t");
	if (node->is_command && node->command.arguments)
		printf("%s\n", node->command.arguments[0]);
	else if (!node->is_command)
	{
		print_tree(node->operand.r_child, depth + 1);
		printf("%s\n", tta(node->operand.optype));
		print_tree(node->operand.l_child, depth + 1);
	}
}
