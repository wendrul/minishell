/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:07:18 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/19 18:44:28 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(t_command cmd)
{
	pid_t child_pid;
	int status;

	status = 130;
	child_pid = fork();
	if (child_pid == 0) /* Inside of child */
	{
		if (execve(getcmd_path(cmd), cmd.argv, g_msh->env) == -1)
		{
			simple_error(strerror(errno), cmd.num, cmd.argv[0]);
			if (errno == EACCES)
				exit(126);
			exit(127);
		}
		exit(1);
	}
	else if (child_pid == -1)
		simple_error(strerror(errno), cmd.num, cmd.name);
	else
	{
		if (waitpid(child_pid, &status, 0) != child_pid)
			simple_error(strerror(errno), cmd.num, cmd.name);
	}
	return (status);
}

void run_cmd(t_list *cmd, t_command cmd_meta, t_builtin builtins)
{
	int status;
	char *status_str;

	cmd_meta.argc = parse_into_args(cmd, &cmd_meta.argv);
	cmd_meta.name = cmd_meta.argv[0];	
	if (cmd_meta.argc >= 1)
	{
		if (!run_builtin(builtins, cmd_meta.argv[0], cmd_meta, &status))
			status = WEXITSTATUS(execute(cmd_meta));
		if (!(status_str = ft_itoa(status)))
			error_exit(MALLOC_FAIL_ERROR);
		dict_put("?", status_str);
		free(status_str);
	}
	free_arr(cmd_meta.argv);
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

void dispatch(t_list *cmd, t_command cmd_meta, t_builtin builtins)
{
	if (next_token(cmd) == PIPE)
		execute_pipe(cmd, cmd_meta, builtins);
	else
		run_cmd(cmd, cmd_meta, builtins);
}

void execute_pipe(t_list *cmd, t_command cmd_meta, t_builtin builtins)
{
	int		pipefd[2];
	pid_t	pid;
	t_list	*left;
	t_list	*right;
	int		stdout_cpy;

	if (!separate_at(lst_indexof(PIPE, cmd), cmd, &left, &right))
	{
		run_cmd(cmd, cmd_meta, builtins);
		return ;
	}
	if (pipe(pipefd))
		error_exit(FAILED_TO_CREATE_PIPE);
	pid = fork();
	if (pid == (pid_t)0)
	{
		/* This is the child process.
         Close other end first. */
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dispatch(right, cmd_meta, builtins);
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
		stdout_cpy = dup(STDOUT_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		run_cmd(left, cmd_meta, builtins);
		close(pipefd[1]);
		close(STDOUT_FILENO);
		wait(NULL);
		dup2(stdout_cpy, STDOUT_FILENO);
		close(stdout_cpy);
	}
}

int redirect(char *filename, int type, t_command cmd_meta)
{
	int fd;

	if ((type == GREAT || type == GREATGREAT) && g_msh->redir_out_fd != -1)
		close(g_msh->redir_out_fd);
	if (type == GREAT)
	{
		if ((fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777)) == -1)
		{
			shell_error(strerror(errno), cmd_meta.num);
			return(0);
		}
		g_msh->redir_out_fd = fd;
		dup2(fd, STDOUT_FILENO);
	}
	else if (type == GREATGREAT)
	{
		if ((fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0777)) == -1)
		{
			shell_error(strerror(errno), cmd_meta.num);
			return(0);
		}
		g_msh->redir_out_fd = fd;
		dup2(fd, STDOUT_FILENO);
	}
	else if (type == LESS)
	{
		if (g_msh->redir_in_fd != -1)
			close(g_msh->redir_in_fd);
		if ((fd = open(filename, O_RDONLY)) == -1)
			shell_error(strerror(errno), cmd_meta.num);
		g_msh->redir_in_fd = fd;
		dup2(fd, STDIN_FILENO);
	}
	return (1);
}

int	redirections(t_list **cmd_ptr, t_command cmd_meta)
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
			if (!redirect(((t_cmd_element)(*tmp2)->next->content)->str, e->type, cmd_meta))
				return (-1);
			after_redir = (*tmp2)->next->next;
			ft_lstdelone((*tmp2)->next, del_element);
			ft_lstdelone(*tmp2, del_element);
			*tmp2 = after_redir;
			//tmp2 = &after_redir;
			continue;
		}
		tmp2 = &((*tmp2)->next);
	}
	return (0);
}
