/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/20 14:28:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gnl(char **old)
{
	char	*line;
	int		gnl_ret;

	if (old != NULL)
		free(*old);
	ft_putstr_fd(PROMPT_TOKEN, STDERR_FILENO);
	signal(SIGINT, handle_signal);
	gnl_ret = get_next_line(STDIN_FILENO, &line);
	signal(SIGINT, sig_when_waiting);
	if (gnl_ret == -1)
		error_exit(FAILED_TO_GET_NEXT_LINE);
	if (gnl_ret == 0)
	{
		write(STDOUT_FILENO, "exit\n", 6);
		exit(0);
	}
	return (line);
}

void		clear_list_arr(t_list ***lst)
{
	t_list	**tmp;

	tmp = *lst;
	while (*tmp)
	{
		ft_lstclear(tmp, del_element);
		tmp++;
	}
	free(*lst);
}

t_list		**read_and_syntax(t_command cmd_meta)
{
	t_list	*elements;
	char	*line;

	line = gnl(NULL);
	while (*line == '\0')
		line = gnl(&line);
	elements = parse_quotes(line, cmd_meta);
	free(line);
	if (!elements)
		return (NULL);
	elements = parse_tokens(elements, cmd_meta);
	if (!syntax_check(elements, cmd_meta))
	{
		ft_lstclear(&elements, del_element);
		return (NULL);
	}
	return (get_cmds(elements));
}

void		reset_io_fds(int og_inout[2])
{
	if (g_msh->redir_out_fd != -1)
		close(g_msh->redir_out_fd);
	if (g_msh->redir_in_fd != -1)
		close(g_msh->redir_in_fd);
	g_msh->redir_out_fd = -1;
	g_msh->redir_in_fd = -1;
	dup2(og_inout[0], STDOUT_FILENO);
	dup2(og_inout[1], STDIN_FILENO);
	close(og_inout[0]);
	close(og_inout[1]);
}

int			shell(t_builtin builtins)
{
	static int	cmd_num = 0;
	t_command	cmd_meta;
	t_list		**cmds;
	int			i;
	int			og_inout[2];

	cmd_num++;
	cmd_meta.num = cmd_num;
	if (!(cmds = read_and_syntax(cmd_meta)))
		return (2);
	i = -1;
	while (cmds[++i])
	{
		og_inout[0] = dup(STDOUT_FILENO);
		og_inout[1] = dup(STDIN_FILENO);
		if (redirections(&cmds[i], cmd_meta) == -1)
		{
			clear_list_arr(&cmds);
			return (2);
		}
		dispatch(cmds[i], cmd_meta, builtins);
		reset_io_fds(og_inout);
	}
	clear_list_arr(&cmds);
	return (0);
}
