/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:33:35 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/03 17:36:36 by ede-thom         ###   ########.fr       */
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

void clear_line(int len)
{
	int i;
	int k;
	char *del_seq;

	i = 0;
	del_seq = "\b \b";
	while (i < (int)ft_strlen(del_seq))
	{
		k = -1;
		while (++k < len)
			write(STDERR_FILENO, del_seq + i, 1);
		i++;
	}
}

int escape_seq(char *buf, int cur)
{
	char c;

	buf[cur] = '\0';
	if (read(STDIN_FILENO, &c, 1) != 1)
		return (READ_ERROR);
	if (c != 91)
		return (NORMAL_RETURN);
	if (read(STDIN_FILENO, &c, 1) != 1)
		return (READ_ERROR);
	if (c == 65)
	{
		clear_line(ft_strlen(buf));
		return (UP_ARROW_RETURN);
	}
	else if (c == 66)
	{
		clear_line(ft_strlen(buf));
		return (DOWN_ARROW_RETURN);
	}
	return (NORMAL_RETURN);
}

static int alloc_line_and_quit(char *buf, char **line, int cur)
{
	buf[cur] = '\0';
	write(STDERR_FILENO, "\n", 1);
	*line = ft_strdup(buf);
	if (line == NULL)
		return (MALLOC_ERROR);
	insert_front(*line);
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
	static char buf[LINE_BUFFER_SIZE];
	static int cur = 0;
	int ret;

	if (substitute != NULL)
	{
		ft_bzero(buf, LINE_BUFFER_SIZE);
		ft_memmove(buf, substitute, ft_strlen(substitute));
		cur = ft_strlen(substitute);
	}
	ft_putstr_fd(buf, STDIN_FILENO);
	while ((ret = read(STDIN_FILENO, buf + cur, 1)))
	{
		if (ret == -1)
			return (READ_ERROR);
		if (buf[cur] == 127 || buf[cur] == '\b')
			erase_char(buf, &cur);
		else if (cur < LINE_BUFFER_SIZE && ft_isprint(buf[cur]))
			write(STDERR_FILENO, buf + cur, 1);
		else if (buf[cur] == ASCII_ESC)
		{
			if ((ret = escape_seq(buf, cur)) != NORMAL_RETURN)
				return (ret);
		}
		else if (buf[cur] == '\n')
			return (alloc_line_and_quit(buf, line, cur));
		else if (buf[cur] == ASCII_EOT && cur == 0)
			return (EOF_RETURN);
		else if (buf[cur] == ASCII_FF)
			screen_clear(buf);
		if (cur < LINE_BUFFER_SIZE)
			cur++;
	}
	return (NORMAL_RETURN);
}