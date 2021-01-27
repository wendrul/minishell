/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:20 by wendrul           #+#    #+#             */
/*   Updated: 2021/01/27 22:36:34 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILTIN_H
# define MSH_BUILTIN_H

# define PWD_BUFF_SIZE 30

#include "minishell.h"

typedef struct	s_builtin
{
	char				name[256];
	int					(*method)(int argc, char **argv);
	struct s_builtin	*next;
}			*	t_builtin;

int		name_cmp(char *str1, char *str2);
void	free_arr(char **ptr);
void	print_arr(char **s);

int		run_builtin(t_builtin builtin, char *name, t_command cmd);
void	add_builtin(t_builtin *list, char *name, int (*method)(int, char**));

int		msh_exit(int argc, char **argv);
int		msh_echo(int argc, char **argv);
int		msh_env();
int		msh_pwd();

#endif