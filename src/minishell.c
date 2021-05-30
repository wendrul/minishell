/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/30 13:37:18 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_when_waiting(int signo)
{
	(void)signo;
}

void	prepare_shell(t_builtin *b)
{
	int	i;

	i = -1;
	while (++i < HASHSIZE)
		g_msh->dict[i] = NULL;
	*b = NULL;
	add_builtin(b, "cd", msh_cd);
	add_builtin(b, "echo", msh_echo);
	add_builtin(b, "env", msh_env);
	add_builtin(b, "exit", msh_exit);
	add_builtin(b, "pwd", msh_pwd);
	add_builtin(b, "unset", msh_unset);
	add_builtin(b, "export", msh_export);
	signal(SIGINT, sig_when_waiting);
	signal(SIGQUIT, sig_when_waiting);
	signal(SIGPIPE, sig_when_waiting);
	set_env_vars(g_msh->env);
	dict_put("?", "0");
}

static void	initialize_gmsh(char **envp)
{
	g_msh = malloc(sizeof(struct s_msh));
	g_msh->env = envp;
	g_msh->head = NULL;
	g_msh->cur = NULL;
	g_msh->err_no = -1;
	g_msh->redir_in_fd = -1;
	g_msh->redir_out_fd = -1;
	g_msh->clear_buf = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_builtin	builtins;
	int			status;
	char		*status_str;

	(void)argc;
	(void)argv;
	initialize_gmsh(envp);
	prepare_shell(&builtins);
	while (1)
	{
		status = shell(builtins);
		if (status != 0)
		{
			status_str = ft_itoa(status);
			if (!status_str)
				error_exit(MALLOC_FAIL_ERROR);
			dict_put("?", status_str);
			free(status_str);
		}
	}
}

void	set_env_vars(char **envp)
{
	while (*envp)
	{
		dict_strput(*envp)->is_env = 1;
		envp++;
	}
}
