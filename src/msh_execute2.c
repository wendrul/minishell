/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:03:58 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/29 22:27:03 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	keep_status(void)
{
	int	status;

	status = 0;
	if (dict_get("?"))
		status = ft_atoi(dict_get("?")->value);
	return (status);
}

void	handle_child(int pipefd[2], t_list *right,
						t_command cmd_meta, t_builtin b)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dispatch(right, cmd_meta, b);
	close(pipefd[0]);
	ft_lstclear(&right, del_element);
	exit(keep_status());
}

void	handle_parent(int pipefd[2], t_list *left,
						t_command cmd_meta, t_builtin b)
{
	int		stdout_cpy;
	int		status;
	char	*status_str;

	close(pipefd[0]);
	stdout_cpy = dup(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	run_cmd(left, cmd_meta, b);
	close(pipefd[1]);
	close(STDOUT_FILENO);
	wait(&status);
	if (WIFEXITED(status))
		status_str = ft_itoa(WEXITSTATUS(status));
	else
		status_str = ft_itoa(status);
	if (!status_str)
		error_exit(MALLOC_FAIL_ERROR);
	dict_put("?", status_str);
	free(status_str);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdout_cpy);
}

void	execute_pipe(t_list *cmd, t_command cmd_meta, t_builtin b)
{
	int		pipefd[2];
	pid_t	pid;
	t_list	*left;
	t_list	*right;

	left = NULL;
	right = NULL;
	if (!separate_at(lst_indexof(PIPE, cmd), cmd, &left, &right))
	{
		run_cmd(cmd, cmd_meta, b);
		return ;
	}
	if (pipe(pipefd))
		error_exit(FAILED_TO_CREATE_PIPE);
	pid = fork();
	if (pid < (pid_t)0)
		error_exit(strerror(errno));
	if (pid == (pid_t)0)
		handle_child(pipefd, right, cmd_meta, b);
	else
		handle_parent(pipefd, left, cmd_meta, b);
	ft_lstclear(&right, del_element);
}
