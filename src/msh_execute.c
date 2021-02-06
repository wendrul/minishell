/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:07:18 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/06 23:20:28 by ede-thom         ###   ########.fr       */
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

int		next_token(t_list *cmd)
{
	t_cmd_element e;

	while (cmd)
	{
		e = (t_cmd_element)cmd->content;
		if (e->type != TEXT)
			return (e->type);
		cmd = cmd->next;
	}
	return (TEXT);
}

void dispatch(t_list *line, t_command cmd, t_builtin builtins)
{
(void)builtins;
(void)cmd;
(void)line;
	
	// type = next_token(line);
	// if (type == PIPE)
	// 	execute_pipe(line, cmd, builtins);
}

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
		//dispatch(right, cmd, builtins);
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

void redirect(char *str, int type)
{
	(void)str;
	(void)type;
	return ;
}

void	redirections(t_list **cmd_ptr)
{
	t_list *after_redir;
	t_list **tmp2;
	t_cmd_element e;

	tmp2 = cmd_ptr;
	while (*tmp2)
	{
		e = (t_cmd_element)(*tmp2)->content;
		if (e->type == GREAT || e->type == GREATGREAT || e->type == LESS)
		{
			redirect(((t_cmd_element)(*tmp2)->next->content)->str, e->type);
			after_redir = (*tmp2)->next->next;
			printf("ptr: %p\n", after_redir);
			ft_lstdelone((*tmp2)->next, del_element);
			ft_lstdelone(*tmp2, del_element);
			*tmp2 = after_redir;
			//tmp2 = &after_redir;
			continue;
		}
		tmp2 = &((*tmp2)->next);
	}
}
