/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:07:18 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 15:06:44 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_child(t_command cmd)
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

int		execute(t_command cmd)
{
	pid_t	child_pid;
	int		status;

	status = 130;
	child_pid = fork();
	if (child_pid == 0)
		exec_child(cmd);
	else if (child_pid == -1)
		simple_error(strerror(errno), cmd.num, cmd.name);
	else
	{
		if (waitpid(child_pid, &status, 0) != child_pid)
			simple_error(strerror(errno), cmd.num, cmd.name);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	status_msg(status);
	return (status);
}

void	run_cmd(t_list *cmd, t_command cmd_meta, t_builtin builtins)
{
	int		status;
	char	*status_str;

	cmd_meta.argc = parse_into_args(cmd, &cmd_meta.argv);
	cmd_meta.name = cmd_meta.argv[0];
	if (cmd_meta.argc >= 1)
	{
		if (!run_builtin(builtins, cmd_meta.argv[0], cmd_meta, &status))
			status = execute(cmd_meta);
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

void	dispatch(t_list *cmd, t_command cmd_meta, t_builtin builtins)
{
	if (next_token(cmd) == PIPE)
		execute_pipe(cmd, cmd_meta, builtins);
	else
		run_cmd(cmd, cmd_meta, builtins);
}
