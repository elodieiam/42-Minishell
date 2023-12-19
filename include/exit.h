/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:53:56 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/12/19 16:07:21 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "structs.h"

/*-----------------exit.c-------------------*/
int	syntax_error(t_data *data, t_token *toklist);
int	ferrnl(char *command, char *arg, char *error, int ret_val);
int	errnl(int exit_code, char *error_str);
int	exit_line(t_data *data, int exit_code);
int	exit_all(t_data *data, int exit_code);

#endif
