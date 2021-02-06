/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:07:18 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/05 23:29:55 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute(t_command cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0) /* Inside of child */
	{
		if (execve(getcmd_path(cmd), cmd.argv, g_msh->env) == -1)
		{
			if (g_msh->verbose)
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
			if (g_msh->verbose)
			{
				printf("status: %d\n", status);
			}
		}
		else
			simple_error(strerror(errno), cmd.num, cmd.name);
	}
}

void run_cmd(char *line, t_command cmd, t_builtin builtins)
{
	cmd.argc = parse_into_args(line, &cmd.argv);
	cmd.name = cmd.argv[0];	
	if (cmd.argc >= 1)
	{
		if (!run_builtin(builtins, cmd.argv[0], cmd))
		{
			execute(cmd);
		}
	}
}

// void dispatch(char *line, t_command cmd, t_builtin builtins)
// {
// 	if (nextisPIPE)
// 		execute_pipe(line, cmd, builtins);
// 	if (nextisGREAT)
// 		redirection(line, cmd, builtins);
// }

void execute_pipe(char *line, t_command cmd, t_builtin builtins)
{
	int		pipefd[2];
	pid_t	pid;
	char	*left;
	char	*right;
	int		stdout_cpy;


	if (!separate(&left, &right, '|', line))
	{
		run_cmd(line, cmd, builtins);
		return ;
	}
	if (pipe(pipefd))
		error_exit(FAILED_TO_CREATE_PIPE);
	pid = fork();
	stdout_cpy = dup(STDOUT_FILENO);
	if (pid == (pid_t)0)
	{
		/* This is the child process.
         Close other end first. */
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execute_pipe(right, cmd, builtins);
		close(pipefd[0]);
		exit(0);
	}
	else if (pid < (pid_t)0)
	{
		/* The fork failed. */
		error_exit(strerror(errno));
	}
	else
	{
		/* This is the parent process.
         Close other end first. */
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		run_cmd(left, cmd, builtins);
		close(pipefd[1]);
		close(STDOUT_FILENO);
		wait(NULL);
		dup2(stdout_cpy, STDOUT_FILENO);
		close(stdout_cpy);
	}
}

// void	redirection(char *line, t_command cmd, t_builtin builtins)
// {
// 	int		pipefd[2];
// 	pid_t	pid;
// 	char	*left;
// 	char	*right;
// 	int		stdout_cpy;

// 	if (!separate(left, right, '>', line))
// }