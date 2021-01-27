/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:26 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 17:00:26 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MSH_CMD_NAME_SIZE 256
# define SH_NAME msh
# define PROMPT_TOKEN "m$ "

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <unistd.h>

# include "libft.h"
# include "get_next_line.h"
# include "msh_error.h"
# include "msh_parsing.h"
# include "msh_builtin.h"
# include "msh_variables.h"

int     g_verbose;

int		shell(t_builtin builtins);
void	run_cmd(t_command cmd, t_builtin builtins);
void	add_env_vars();
void	execute(t_command cmd);

#endif