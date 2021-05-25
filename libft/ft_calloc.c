/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:10:30 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/07 00:08:16 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}
