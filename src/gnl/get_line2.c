/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:13:04 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/27 13:57:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_the_char(int c)
{
	write(STDERR_FILENO, &c, 1);
	return (c);
}

void	screen_clear(char *buf, int *cur)
{
	char	*clear;

	buf[*cur] = '\0';
	(*cur)--;
	clear = tgetstr("cl", NULL);
	tputs(clear, 1, put_the_char);
	ft_putstr_fd(PROMPT_TOKEN, STDERR_FILENO);
	ft_putstr_fd(buf, STDERR_FILENO);
}

static int	get_line2(char *buf, int *cur, char **line)
{
	int	ret;

	if (buf[*cur] == ASCII_ESC)
	{
		ret = escape_seq(buf, cur);
		if (ret != NORMAL_RETURN)
			return (ret);
	}
	else if (buf[*cur] == '\n')
		return (alloc_line_and_quit(buf, line, *cur));
	else if (buf[*cur] == ASCII_EOT && *cur == 0)
		return (EOF_RETURN);
	else if (buf[*cur] == ASCII_FF)
		screen_clear(buf, cur);
	else if (!ft_isprint(buf[*cur]))
		buf[(*cur)--] = 0;
	else if (*cur < LINE_BUFFER_SIZE)
		write(STDERR_FILENO, buf + *cur, 1);
	return (DONT_RETURN);
}

static int	setup_line(const char *substitute, char *buf, int cur)
{
	if (substitute != NULL)
	{
		ft_bzero(buf, LINE_BUFFER_SIZE);
		ft_memmove(buf, substitute, ft_strlen(substitute));
		cur = ft_strlen(substitute);
	}
	ft_putstr_fd(buf, STDIN_FILENO);
	return (cur);
}

int	get_line(char **line, const char *substitute)
{
	static char	buf[LINE_BUFFER_SIZE];
	static int	cur = 0;
	int			ret;

	cur = setup_line(substitute, buf, cur);
	ret = read(STDIN_FILENO, buf + cur, 1);
	while (ret)
	{
		if (g_msh->clear_buf)
			clear_buf(buf, &cur);
		if (ret == -1)
			return (READ_ERROR);
		if (buf[cur] == 127 || buf[cur] == '\b')
			erase_char(buf, &cur);
		else
		{
			ret = get_line2(buf, &cur, line);
			if (ret != DONT_RETURN)
				return (ret);
		}
		if (cur < LINE_BUFFER_SIZE)
			cur++;
		ret = read(STDIN_FILENO, buf + cur, 1);
	}
	return (NORMAL_RETURN);
}
