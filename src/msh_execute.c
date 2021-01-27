/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:07:18 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/27 00:42:41 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_command cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0) /* Inside of child */
	{
		if (execve(getcmd_path(cmd), cmd.argv, __environ) == -1)
		{
			if (g_verbose)
				printf("errno: %d: %s\n", errno, strerror(errno));
			simple_error(NOT_FOUND_ERROR, cmd.num, cmd.argv[0]);
			exit(0);
		}
	}
	else if (child_pid == -1)
		simple_error(strerror(errno), cmd.num, cmd.name);
	else
	{
		/* Inside of parent */
	    if (waitpid(child_pid, &status, 0) == child_pid)
		{
			if (g_verbose)
				printf("status: %d\n", status);
		}
	    else
			simple_error(strerror(errno), cmd.num, cmd.name);
	}
}

void	run_cmd(t_command cmd, t_builtin builtins)
{
	if (cmd.argc >= 1)
	{
		if (!run_builtin(builtins, cmd.argv[0], cmd))
		{
			execute(cmd);
		}
	}
}
