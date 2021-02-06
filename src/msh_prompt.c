/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/06 02:28:58 by ede-thom         ###   ########.fr       */
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



int		shell(t_builtin builtins)
{
	static int	cmd_num = 0;
	char		*line;
	char		**cmds;
	t_command	cmd;
	char		**cmd_ptr;
	t_list		*elements;

	line = gnl();
	cmd_num++;
	cmd.num = cmd_num;
	if (!(elements = parse_quotes(line, cmd)))
		return (2);
	semicolon_split()
	
	elements = parse_tokens(elements, cmd);
	ft_lstiter(elements, print_el);
	printf("\n");
	if (!(cmds = ft_split(line, ';')))
		error_exit(SPLIT_FAIL_ERROR);
	cmd_ptr = cmds;
	while (*cmds)
	{
		execute_pipe(*cmds, cmd, builtins);
		cmds++;	
	}
	free_arr(cmd_ptr);
	return (0);
}

