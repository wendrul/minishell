/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/01/18 21:13:53 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell(t_builtin builtins)
{
	static int	cmd_num = 0;
	char		*line;
	t_command	cmd;

	printf("€ ");
	fflush(stdout);
	if (get_next_line(STDIN_FILENO, &line) == -1)
		error_exit(MALLOC_FAIL_ERROR);
	cmd_num++;
	cmd.num = cmd_num;
	cmd.argc = parse_into_args(line, &cmd.argv);
	run_cmd(cmd, builtins);
	return 0;
}

void run_cmd(t_command cmd, t_builtin builtins)
{
	if (cmd.argc >= 1)
	{
		if (!run_builtin(builtins, cmd.argv[0], cmd))
			simple_error(NOT_FOUND_ERROR, cmd.num, cmd.argv[0]);
	}
}