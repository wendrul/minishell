/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:20 by wendrul           #+#    #+#             */
/*   Updated: 2021/05/25 12:33:57 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILTIN_H
# define MSH_BUILTIN_H

# define PWD_BUFF_SIZE 4096

# include "minishell.h"

typedef struct s_builtin
{
	char				name[256];
	int					(*method)(int argc, char **argv);
	struct s_builtin	*next;
}*t_builtin;

int				name_cmp(char *str1, char *str2);
void			free_arr(char **ptr);
void			print_arr(char **s);

int				run_builtin(t_builtin builtin, char *n, t_command cmd, int *s);
void			add_builtin(t_builtin *list, char *n, int (*m)(int, char**));

int				msh_exit(int argc, char **argv);
int				msh_echo(int argc, char **argv);
int				msh_env(int argc, char **argv);
int				msh_pwd(int argc, char **argv);
int				msh_cd(int argc, char **argv);
int				msh_unset(int argc, char **argv);
int				msh_export(int argc, char **argv);

#endif
