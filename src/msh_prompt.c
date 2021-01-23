/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/01/23 21:20:07 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell(t_builtin builtins)
{
	static int	cmd_num = 0;
	char		*line;
	t_command	cmd;

	//printf("€ ");
	write(STDOUT_FILENO, "$ ", 2);
	if (get_next_line(STDIN_FILENO, &line) == -1)
		error_exit(MALLOC_FAIL_ERROR);
	cmd_num++;
	cmd.num = cmd_num;
	cmd.argc = parse_into_args(line, &cmd.argv);
	cmd.name = cmd.argv[0];
	run_cmd(cmd, builtins);
	return 0;
}
