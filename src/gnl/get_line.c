/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:33:35 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/01 23:23:22 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void erase_char(char *buf, int *cur)
{
	buf[*cur] = '\0';
	(*cur)--;
	if (*cur >= 0)
	{
		buf[*cur] = '\0';
		(*cur)--;
		write(STDERR_FILENO, "\b \b", 3);
	}
	else
		write(STDERR_FILENO, "\a", 1);
}

int escape_seq(char *buf, int cur)
{
	(void)buf;
	(void)cur;
	return (NORMAL_RETURN);
}

static int alloc_line_and_quit(char *buf, char **line)
{
	write(STDERR_FILENO, "\n", 1);
	*line = ft_strdup(buf);
	if (line == NULL)
		return (MALLOC_ERROR);
	return (NORMAL_RETURN);
}

int	put_the_char(int c)
{
	write(STDERR_FILENO, &c, 1);
	return (c);
}

void screen_clear(char *buf)
{
	char *clear;

	clear = tgetstr("cl", NULL);
	tputs(clear, 1, put_the_char);
	ft_putstr_fd(PROMPT_TOKEN, STDERR_FILENO);
	//free(clear);
	ft_putstr_fd(buf, STDERR_FILENO);
}

int	get_line(char **line, const char *substitute)
{
	char buf[LINE_BUFFER_SIZE];
	int cur;
	int ret;

	ft_bzero(buf, LINE_BUFFER_SIZE);
	ft_memmove(buf, substitute, ft_strlen(substitute));
	cur = ft_strlen(substitute);
	ft_putstr_fd(buf, STDIN_FILENO);
	while (read(STDIN_FILENO, buf + cur, 1))
	{
		if (buf[cur] == 127 || buf[cur] == '\b')
			erase_char(buf, &cur);
		else if (cur < LINE_BUFFER_SIZE && ft_isprint(buf[cur]))
			write(STDERR_FILENO, buf + cur, 1);
		else if (cur == ASCII_ESC)
		{
			if ((ret = escape_seq(buf, cur)) != NORMAL_RETURN)
				return (ret);
		}
		else if (buf[cur] == '\n')
			return (alloc_line_and_quit(buf, line));
		else if (buf[cur] == ASCII_EOT && cur == 0)
			return (EOF_RETURN);
		else if (buf[cur] == ASCII_FF)
			screen_clear(buf);
		if (cur < LINE_BUFFER_SIZE)
			cur++;
	}
	return (NORMAL_RETURN);
}