/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/08 15:28:21 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*-------------------exec.c------------------*/
int		exec(t_data *data, t_node *node);
int		exec_command(t_data *data, t_node *node);

/*-------------------exit.c------------------*/
int		exec_exit(t_data *data, t_node *node);

/*------------------execve.c-----------------*/
int		execute(t_data *data, t_node *node);
void	check_file(t_data *data, char *file_path, char *cmd);
char	*get_cmd_path(t_data *data, char *command);
/*----------------exec_utils.c---------------*/
int		is_path(const char *str);
char	*bettercat(char *s1, char *s2);
void	free_dchartab(char **tab);
int		export_lastarg(t_data *data, t_node *node);

/*-------------------echo.c------------------*/
int		exec_echo(t_node *node);

/*------------------export.c-----------------*/
int		exec_export(t_data *data, char **arguments);

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
int		exec_cd(t_data *data, t_node *node);

/*-------------------pwd.c-------------------*/
int		exec_pwd(t_data *data, t_node *node);

/*-------------------unset.c--------------------*/
int		exec_unset(t_data *data, char **args);

/*-------------------heredoc.c--------------------*/
int		exec_heredoc_and_command(t_node *node, char *lim, t_data *data);
int		exec_simple_heredoc(char *lim);

/*-------------------redirections.c--------------------*/
int		handle_redirections(t_data *data, t_node *node);

#endif