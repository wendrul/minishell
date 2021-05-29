/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/05/29 18:59:56 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	set_up_termcaps(char *term_name)
{
	struct termios	termios_new;
	struct termios	termios_backup;

	tgetent(NULL, term_name);
	tcgetattr(STDIN_FILENO, &termios_backup);
	termios_new = termios_backup;
	termios_new.c_lflag &= ~(ICANON);
	termios_new.c_lflag &= ~(ECHO);
	termios_new.c_oflag |= ISIG;
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &termios_new);
	return (termios_backup);
}

static void	gnl_aux(int gnl_ret)
{
	signal(SIGINT, sig_when_waiting);
	if (gnl_ret == MALLOC_ERROR || gnl_ret == READ_ERROR)
		error_exit(FAILED_TO_GET_NEXT_LINE);
	if (gnl_ret == EOF_RETURN)
	{
		write(STDERR_FILENO, "exit\n", 6);
		exit(0);
	}
}

static int	gnl_read_loop(char **line)
{
	char	*substitute;
	int		gnl_ret;

	gnl_ret = get_line(line, "");
	while (gnl_ret == UP_ARROW_RETURN || gnl_ret == DOWN_ARROW_RETURN)
	{
		if (gnl_ret == UP_ARROW_RETURN)
			substitute = on_up_arrow();
		else if (gnl_ret == DOWN_ARROW_RETURN)
			substitute = on_down_arrow();
		gnl_ret = get_line(line, substitute);
	}
	return (gnl_ret);
}

static char	*gnl(char **old)
{
	char			*line;
	int				gnl_ret;
	struct termios	termios_backup;

	if (old != NULL)
		free(*old);
	if (isatty(STDERR_FILENO))
		ft_putstr_fd(PROMPT_TOKEN, STDERR_FILENO);
	signal(SIGINT, handle_signal);
	line = NULL;
	if (isatty(STDERR_FILENO) && dict_get("TERM") != NULL)
	{
		termios_backup = set_up_termcaps(dict_get("TERM")->value);
		gnl_ret = gnl_read_loop(&line);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_backup);
	}
	else
		gnl_ret = get_next_line(STDIN_FILENO, &line);
	gnl_aux(gnl_ret);
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
	free(*lst);
}

t_list	**read_and_syntax(t_command cmd_meta)
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

void	reset_io_fds(int og_inout[2])
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

int	shell(t_builtin builtins)
{
	static int	cmd_num = 0;
	t_command	cmd_meta;
	t_list		**cmds;
	int			i;
	int			og_inout[2];

	cmd_meta.num = ++cmd_num;
	cmds = read_and_syntax(cmd_meta);
	if (!cmds)
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
