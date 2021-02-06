/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/05 23:13:13 by ede-thom         ###   ########.fr       */
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
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT_TOKEN, ft_strlen(PROMPT_TOKEN));
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
	add_builtin(&builtins, "export", msh_export);
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
	while (*envp)
	{
		dict_strput(*envp)->is_env = 1;
		envp++;
	}
}

void	error_exit(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(0);
}

void	simple_error(char *msg, int cmd_no, char *cmd_name)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putnbr_fd(cmd_no, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
//	printf("msh: %d: %s: %s\n", cmd_no, cmd_name, msg);
}

void	shell_error(char *msg, int cmd_no)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putnbr_fd(cmd_no, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
