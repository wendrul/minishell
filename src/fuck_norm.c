/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 22:46:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/30 13:48:15 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		g_msh->clear_buf = 1;
		if (isatty(STDERR_FILENO))
		{
			write(STDERR_FILENO, "^C\n", 3);
			write(STDERR_FILENO, PROMPT_TOKEN, ft_strlen(PROMPT_TOKEN));
		}
	}
}

void	memmoves_for_replace(char **str, char *o, int var_start, char *val)
{
	ft_memmove(*str, o, var_start);
	ft_memmove(*str + var_start, val, ft_strlen(val));
}

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

void	gnl_aux2(int gnl_ret)
{
	signal(SIGINT, sig_when_waiting);
	if (gnl_ret == MALLOC_ERROR || gnl_ret == READ_ERROR)
		error_exit(FAILED_TO_GET_NEXT_LINE);
	if (gnl_ret == EOF_RETURN)
	{
		write(STDERR_FILENO, "exit\n", 6);
		exit(keep_status());
	}
}

int	gnl_read_loop(char **line)
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
