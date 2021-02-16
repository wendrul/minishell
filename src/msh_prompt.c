/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/15 00:24:23 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gnl()
{
	char	*line;
	int		gnl_ret;

	write(STDOUT_FILENO, PROMPT_TOKEN, ft_strlen(PROMPT_TOKEN));
	gnl_ret = get_next_line(STDIN_FILENO, &line);
	if (gnl_ret == -1)
		error_exit(FAILED_TO_GET_NEXT_LINE);
	if (gnl_ret == 0)
	{
		write(STDOUT_FILENO, "exit\n", 6);
		exit(0);
	}
	return (line);
}

void	clear_list_arr(t_list ***lst)
{
	t_list	**tmp;

	tmp = *lst;
	while (*tmp)
	{
		ft_lstclear(tmp, del_element);
		tmp++;
	}
}

int		shell(t_builtin builtins)
{
	static int	cmd_num = 0;
	char		*line;
	t_command	cmd_meta;
	t_list		*elements;
	t_list		**cmds;
	int			i;
	int			og_inout[2];

	(void)&builtins;
	line = gnl();
	cmd_num++;
	cmd_meta.num = cmd_num;
	if (!(elements = parse_quotes(line, cmd_meta)))
		return (2);
	elements = parse_tokens(elements, cmd_meta);
	if (!syntax_check(elements, cmd_meta))
		return (2);
	cmds = get_cmds(elements);
	i = 0;
	while (cmds[i])
	{
		og_inout[0] = dup(STDOUT_FILENO);
		og_inout[1] = dup(STDIN_FILENO);
		if (g_msh->verbose)
		{
			ft_lstiter(cmds[i], print_el);
			write(STDOUT_FILENO, "\n", 1);
		}
		if (redirections(&cmds[i], cmd_meta) == -1)
			return (2);
		dispatch(cmds[i], cmd_meta, builtins);
		if (g_msh->redir_out_fd != -1)
			close (g_msh->redir_out_fd);
		if (g_msh->redir_in_fd != -1)
			close (g_msh->redir_in_fd);
		g_msh->redir_out_fd = -1;
		g_msh->redir_in_fd = -1;
		dup2(og_inout[0], STDOUT_FILENO);
		dup2(og_inout[1], STDIN_FILENO);
		close(og_inout[0]);
		close(og_inout[1]);
		i++;
	}
	clear_list_arr(&cmds);
	return (0);
}

