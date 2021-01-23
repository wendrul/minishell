/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:07:18 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/23 18:17:51 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tres_thing(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	
	if (child_pid == 0) {
	     // in child; do stuff including perhaps exec
	} else if (child_pid == -1) {
	     // failed to fork 
	} else {
	     if (waitpid(child_pid, &status, 0) == child_pid) {
	          // child exited or interrupted; now you can do something with status
	     } else {
	          // error etc
	     }
	}
}

void	run_cmd(t_command cmd, t_builtin builtins)
{
	if (cmd.argc >= 1)
	{
		if (!run_builtin(builtins, cmd.argv[0], cmd))
		{
			//ENVP expects "key=value" our dictionnary is for personal usage (separte key and value)
			if (execve(getcmd_path(cmd), cmd.argv, NULL) == -1)
			{
				printf("errno: %d: %s\n", errno, strerror(errno));
				simple_error(NOT_FOUND_ERROR, cmd.num, cmd.argv[0]);
			}
		}
	}
}
