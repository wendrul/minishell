/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 17:00:48 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	//printf("signal: %d\n", signo);
	if (signo == SIGINT)
	{
		printf("\n");
	}
	if (signo == SIGQUIT)
	{
		exit(0);
	}
}

int		main(void)
{
	t_builtin builtins;

	builtins = NULL;
	add_builtin(&builtins, "echo", msh_echo);
	add_builtin(&builtins, "env", msh_env);
	add_builtin(&builtins, "exit", msh_exit);
	add_env_vars();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
		shell(builtins);
	return (0);
}

void	add_env_vars()
{
	char **env;
	char **tmp;

	env = __environ;
	while (*env)
	{
		if (!(tmp = ft_split(*env, '=')))
			error_exit(MALLOC_FAIL_ERROR);
		dict_put(tmp[0], tmp[1]);
		free_arr(tmp);
		env++;
	}
}

void		error_exit(char *str)
{
	printf("msh: %s\n", str);
	exit(0);
}

void		simple_error(char *msg, int cmd_no, char *cmd_name)
{
	printf("msh: %d: %s: %s\n", cmd_no, cmd_name, msg);
}