/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/28 21:57:10 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (g_msh->verbose)
		printf("signal: %d\n", signo);
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT_TOKEN, ft_strlen(PROMPT_TOKEN));
	}
	if (signo == SIGQUIT)
	{
		exit(0);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_builtin builtins;

	g_msh = malloc(sizeof(struct s_msh));
	g_msh->env = envp;
	if (argc > 1)
		g_msh->verbose = name_cmp("-v", argv[1]);
	builtins = NULL;
	add_builtin(&builtins, "cd", msh_cd);
	add_builtin(&builtins, "echo", msh_echo);
	add_builtin(&builtins, "env", msh_env);
	add_builtin(&builtins, "exit", msh_exit);
	add_builtin(&builtins, "pwd", msh_pwd);
	add_builtin(&builtins, "unset", msh_unset);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	set_env_vars(g_msh->env);
	while (1)
		shell(builtins);
	free(g_msh);
	return (0);
}

void	set_env_vars(char **envp)
{
	char	*key;
	char	*val;
	int		pos;

	while (*envp)
	{
		pos = ft_indexof('=', *envp);
 		if (!(key = ft_substr(*envp, 0, pos)))
 			error_exit(MALLOC_FAIL_ERROR);
		if (!(val = ft_substr(*envp, pos + 1, ft_strlen(*envp))))
			error_exit(MALLOC_FAIL_ERROR);
		dict_put(key, val)->is_env = 1;
		free(key);
		free(val);
		envp++;
	}
}

void	error_exit(char *str)
{
	printf("msh: %s\n", str);
	exit(0);
}

void	simple_error(char *msg, int cmd_no, char *cmd_name)
{
	printf("msh: %d: %s: %s\n", cmd_no, cmd_name, msg);
}
