/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 12:36:44 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	int i;

	if (g_msh->verbose)
		printf("signal: %d\n", signo);
	if (signo == SIGINT)
	{
		i = -1;
		write(STDERR_FILENO, "\n", 1);
		write(STDERR_FILENO, PROMPT_TOKEN, ft_strlen(PROMPT_TOKEN));
	}
	if (signo == SIGQUIT)
	{
			
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_builtin	builtins;
	int			status;
	char		*status_str;
	int i = -1;
	
	g_msh = malloc(sizeof(struct s_msh));
	g_msh->env = envp;
	g_msh->verbose = 0;
	g_msh->err_no = -1;
	g_msh->redir_in_fd = -1;
	g_msh->redir_out_fd = -1;
	if (argc > 1)
		g_msh->verbose = name_cmp("-v", argv[1]);
	while (++i < HASHSIZE)
		g_msh->dict[i] = NULL;
	builtins = NULL;
	add_builtin(&builtins, "cd", msh_cd);
	add_builtin(&builtins, "echo", msh_echo);
	add_builtin(&builtins, "env", msh_env);
	add_builtin(&builtins, "exit", msh_exit);
	add_builtin(&builtins, "pwd", msh_pwd);
	add_builtin(&builtins, "unset", msh_unset);
	add_builtin(&builtins, "export", msh_export);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	set_env_vars(g_msh->env);
	dict_put("?", "0");
	while (1)
	{
		if ((status = shell(builtins)) != 0)
		{
			if (!(status_str = ft_itoa(status)))
				error_exit(MALLOC_FAIL_ERROR);
			dict_put("?", status_str);
		}
	}
	free(g_msh);
	return (0);
}

void	set_env_vars(char **envp)
{
	while (*envp)
	{
		dict_strput(*envp)->is_env = 1;
		envp++;
	}
}
