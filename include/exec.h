/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/22 01:34:49 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*-------------------exec.c------------------*/
int		exec(t_data *data);
int		exec_command(t_data *data, t_node *node);

/*-------------------exit.c------------------*/
int		exec_exit(t_data *data, t_node *node);

/*------------------execve.c-----------------*/
int		execute(t_data *data, t_node *node);

/*----------------exec_utils.c---------------*/
int		is_path(const char *str);
char	*bettercat(char *s1, char *s2);
void	free_dchartab(char **tab);

/*-------------------echo.c------------------*/
int		exec_echo(t_node *node);

/*------------------export.c-----------------*/
int		exec_export(t_data *data, char **arguments);
int		changevar(t_data *data, char *argument, int i);

/*----------------export_utils.c-------------*/
int		is_valid_arg(char *str);
int		ft_strcmp(char *s1, char *s2);
void	swap_strings(char **s1, char **s2);

/*----------------export_env.c---------------*/
int		display_env(t_data *data);
int		update_env(t_data *data, char **arguments, int index);

/*----------------exec_env.c-----------------*/
int		exec_env(t_data *data);

/*-------------------cd.c--------------------*/


#endif
