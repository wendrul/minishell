/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:59:27 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/19 19:23:27 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **ptr)
{
	char	**start;

	start = ptr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(start);
}

void	print_arr(char **s)
{
	while (*s)
		ft_putendl_fd(*(s++), STDOUT_FILENO);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
