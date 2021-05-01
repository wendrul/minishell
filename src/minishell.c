/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/01 21:50:07 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	int i;

	if (signo == SIGINT)
	{
		i = -1;
		write(STDERR_FILENO, "\n", 1);
		write(STDERR_FILENO, PROMPT_TOKEN, ft_strlen(PROMPT_TOKEN));
	}
}

void	sig_when_waiting(int signo)
{
	(void)signo;
}

void	prepare_shell(t_builtin *b)
{
	int i;

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
	set_env_vars(g_msh->env);
	dict_put("?", "0");
}

int		main(int argc, char **argv, char **envp)
{
	t_builtin	builtins;
	int			status;
	char		*status_str;

	(void)argc;
	(void)argv;
	g_msh = malloc(sizeof(struct s_msh));
	g_msh->env = envp;
	g_msh->head = NULL;
	g_msh->cur = NULL;
	g_msh->err_no = -1;
	g_msh->redir_in_fd = -1;
	g_msh->redir_out_fd = -1;
	prepare_shell(&builtins);
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
