/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:46:54 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 15:18:40 by agoodwin         ###   ########.fr       */
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

typedef struct			s_var_dict
{
	struct s_var_dict	*next;
	char				*key;
	char				*value;
	int					is_env;
}					*	t_var_dict;

typedef struct			s_msh
{
	char				**env;
	t_var_dict			dict[HASHSIZE];
	int					redir_out_fd;
	int					redir_in_fd;
	int					err_no;
}					*	t_msh;

t_msh					g_msh;

t_var_dict				dict_get(char *s);
t_var_dict				dict_put(char *key, char *val);
void					dict_print(t_var_dict *dict);
int						dict_rm(char *key);
t_var_dict				dict_strput(char *str);

int						shell(t_builtin builtins);
void					run_cmd(t_list *cmd, t_command cmd_meta, t_builtin b);
void					execute_pipe(t_list *c, t_command m, t_builtin b);
void					set_env_vars(char **envp);
int						execute(t_command cmd);
void					dispatch(t_list *cmd, t_command cmd_meta, t_builtin b);
int						redirections(t_list **cmd, t_command cmd_meta);
void					handle_signal(int signo);
void					sig_when_waiting(int signo);

#endif
