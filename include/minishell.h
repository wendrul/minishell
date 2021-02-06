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
# define PROMPT_TOKEN "\033[1;36mm$ \033[0;m"
# define HASHSIZE 101

# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_HOME "HOME"
# define ENV_PATH "PATH"

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
# include "utils.h"

typedef struct	s_var_dict
{
	struct s_var_dict	*next;
	char				*key;
	char				*value;
    int                 is_env;
}			*	t_var_dict;

typedef struct  s_msh
{
    int         verbose;
    char        **env;
    t_var_dict  dict[HASHSIZE];
}           *   t_msh;

t_msh   g_msh;

t_var_dict	dict_get(char *s);
t_var_dict	dict_put(char *key, char *val);
void        dict_print(t_var_dict *dict);
int			dict_rm(char *key);
t_var_dict	dict_strput(char *str);

int		    shell(t_builtin builtins);
void	    run_cmd(char *line, t_command cmd, t_builtin builtins);
void	    execute_pipe(char *line, t_command cmd, t_builtin builtins);
void	    set_env_vars(char **envp);
void	    execute(t_command cmd);
void		dispatch(t_list *cmd, t_command cmd_meta, t_builtin builtins);
void		redirections(t_list **cmd);

#endif