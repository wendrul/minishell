/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/05 19:04:16 by ede-thom         ###   ########.fr       */
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
	
	line = gnl();
	cmd_num++;
	cmd.num = cmd_num;
	if (!(cmds = ft_split(line, ';')))
		error_exit(SPLIT_FAIL_ERROR);
	while (*cmds)
	{
		execute_pipe(*cmds, cmd, builtins);
		//free(*cmds);
		cmds++;	
	}
	//free(cmds);
	return (0);
}
