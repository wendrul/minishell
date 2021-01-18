/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:48 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 17:00:48 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		main(int argc, char **argv)
{
	t_builtin builtins;

	builtins = NULL;
	(void)argc;
	(void)argv;
	add_builtin(&builtins, "exit", msh_exit);
	add_builtin(&builtins, "echo", msh_echo);
	printf("aaaa\n");
	while (1)
		shell(builtins);
	return (0);
}

void		error_exit(char *str)
{
	printf("msh: %s\n", str);
	exit(0);
}

void		simple_error(char *msg, int cmd_no, char *cmd_name)
{
	printf("msh: %d: %s: %s\n", cmd_no, cmd_name, msg);
}