/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:33:35 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/25 14:14:38 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_char(char *buf, int *cur)
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

void	clear_line(int len)
{
	int		i;
	int		k;
	char	*del_seq;

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

int	escape_seq(char *buf, int *cur)
{
	char	c;

	buf[*cur] = '\0';
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
	(*cur)--;
	return (NORMAL_RETURN);
}

int	alloc_line_and_quit(char *buf, char **line, int cur)
{
	buf[cur] = '\0';
	write(STDERR_FILENO, "\n", 1);
	*line = ft_strdup(buf);
	if (line == NULL)
		return (MALLOC_ERROR);
	if (ft_strlen(buf) > 0 && !is_same_as_last(*line))
		insert_front(*line);
	g_msh->cur = NULL;
	return (NORMAL_RETURN);
}

void	clear_buf(char *buf, int *cur)
{
	char	c;

	c = buf[*cur];
	ft_bzero(buf, ft_strlen(buf));
	*cur = 0;
	buf[*cur] = c;
	g_msh->clear_buf = 0;
}
