/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/06 15:33:00 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*----------------exec.c---------------*/
int		exec(t_data *data);
int		exec_command(t_data *data, t_node *node);

/*----------------exit.c---------------*/
int		exec_exit(t_data *data, t_node *node);

/*----------------execve.c---------------*/
int		execute(t_data *data, t_node *node);

/*----------------exec_utils.c---------------*/
int		is_path(const char *str);
char	*bettercat(char *s1, char *s2);
void	free_dchartab(char **tab);

#endif
