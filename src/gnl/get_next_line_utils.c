/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:15:07 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/24 15:51:31 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		initialize_node(t_buf_hist cur, int fd)
{
	cur->fd = fd;
	cur->buf[0] = '\0';
	cur->next = NULL;
}

char		*get_last_from_fd(int fd, t_buf_hist *hist)
{
	t_buf_hist	cur;

	if (*hist == NULL)
	{
		if (!(cur = (t_buf_hist)malloc(sizeof(*cur))))
			return (NULL);
		initialize_node(cur, fd);
		*hist = cur;
		return (cur->buf);
	}
	if ((cur = *hist) && cur->fd == fd)
		return (cur->buf);
	while (cur->next)
	{
		if (cur->next->fd == fd)
			return (cur->next->buf);
		cur = cur->next;
	}
	if (!(cur->next = (t_buf_hist)malloc(sizeof(**hist))))
		return (NULL);
	cur = cur->next;
	initialize_node(cur, fd);
	return (cur->buf);
}

t_buf_hist	remove_fd_from_hist(int fd, t_buf_hist element)
{
	t_buf_hist	tmp;

	if (element == NULL)
		return (NULL);
	if (element->fd == fd)
	{
		tmp = element->next;
		free(element);
		return (tmp);
	}
	element->next = remove_fd_from_hist(fd, element->next);
	return (element);
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*desert;
	char	*sauce;

	desert = (char*)dest;
	sauce = (char*)src;
	if (desert > sauce)
		while (n--)
			desert[n] = sauce[n];
	else
		while (n--)
			*desert++ = *sauce++;
	return (dest);
}
