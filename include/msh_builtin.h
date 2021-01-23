/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:20 by wendrul           #+#    #+#             */
/*   Updated: 2021/01/23 00:46:57 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILTIN_H
# define MSH_BUILTIN_H

#include "minishell.h"

typedef struct	s_builtin
{
	char				name[256];
	int					(*method)(int argc, char **argv);
	struct s_builtin	*next;
}			*	t_builtin;

int		name_cmp(char *str1, char *str2);
void	free_arr(void **ptr);

int		run_builtin(t_builtin builtin, char *name, t_command cmd);
void	add_builtin(t_builtin *list, char *name, int (*method)(int, char**));

int		msh_exit(int argc, char **argv);
int		msh_echo(int argc, char **argv);

#endif