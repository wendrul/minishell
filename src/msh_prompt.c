/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/07 16:35:55 by ede-thom         ###   ########.fr       */
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
		if (g_msh->verbose)
		{
			ft_lstiter(cmds[i], print_el);
			write(STDOUT_FILENO, "\n", 1);
		}
		redirections(&cmds[i]);
		dispatch(cmds[i], cmd_meta, builtins);
		i++;
	}
	clear_list_arr(&cmds);
	return (0);
}

