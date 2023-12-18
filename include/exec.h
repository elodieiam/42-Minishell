/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by elrichar          #+#    #+#             */
/*   Updated: 2023/12/18 12:43:49 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

/*-------------------exec.c------------------*/
int			exec(t_data *data, t_node *node);

/*-------------------builtins.c------------------*/
int			srch_builtin(t_data *data, t_node *node);

/*-------------------exit.c------------------*/
int			exec_exit(t_data *data, t_node *node);

/*------------------execve.c-----------------*/
int			execute(t_data *data, t_node *node);
void		check_file(t_data *data, char *file_path, char *cmd);
char		*get_cmd_path(t_data *data, char *command);
int			child_exec(t_data *data, t_node *node);

/*----------------exec_utils.c---------------*/
int			is_path(const char *str);
char		*bettercat(char *s1, char *s2);
void		free_dchartab(char **tab);
int			export_lastarg(t_data *data, t_node *node);

/*-------------------echo.c------------------*/
int			exec_echo(t_node *node);

/*------------------export.c-----------------*/
int			exec_export(t_data *data, char **arguments);

/*----------------export_utils.c-------------*/
int			is_valid_arg(char *str);
int			ft_strcmp(char *s1, char *s2);
void		swap_strings(char **s1, char **s2);

/*----------------export_env.c---------------*/
int			display_env(t_data *data);
int			update_env(t_data *data, char **arguments, int index);

/*----------------exec_env.c-----------------*/
int			exec_env(t_data *data);

/*-------------------cd.c--------------------*/
int			exec_cd(t_data *data, t_node *node);

/*-------------------pwd.c-------------------*/
int			exec_pwd(t_data *data, t_node *node);

/*------------------unset.c------------------*/
int			exec_unset(t_data *data, char **args);

/*-----------------heredoc.c-----------------*/
int			exec_child_heredoc(t_data *data, t_node *node);
int			open_heredocs(t_data *data, t_node *node);

/*------------------pipe.c-------------------*/
int			exec_pipe(t_data *data, t_node *node);

/*-----------------pidlist.c-----------------*/
t_pidlist	*append_pid(t_pidlist **head, int new_pid);
int			pop_pid(t_pidlist **pidlist_head);
void		free_pidlist(t_pidlist **pidlist);

/*--------------redirections.c---------------*/
int			handle_redirections(t_data *data, t_node *node);
int			reset_rds(t_fds *fds, t_node *node);

/*--------------heredoc_utils.c--------------*/
char		*get_heredoc_name(void);
void		exit_heredoc(t_rdlist *rd);

#endif
