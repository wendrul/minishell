/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/06 20:51:13 by ede-thom         ###   ########.fr       */
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
	t_command	cmd;
	t_list		*elements;
	t_list		**cmds;
	int			i;

	(void)&builtins;
	line = gnl();
	cmd_num++;
	cmd.num = cmd_num;
	if (!(elements = parse_quotes(line, cmd)))
		return (2);
	elements = parse_tokens(elements, cmd);
	ft_lstiter(elements, print_el);
	printf("\n");	
	//syntax check;
	cmds = get_cmds(elements);
	i = 0;
	while (cmds[i])
	{
		printf("cmd %d - ", i);
		fflush(stdout);
		ft_lstiter(cmds[i], print_el);
		printf("\n");
		//execute_pipe(cmds[i], cmd, builtins);
		i++;
	}
	clear_list_arr(&cmds);
	return (0);
}

