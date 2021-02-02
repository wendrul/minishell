/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:18:14 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/02 19:18:23 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		separate(char **half1, char **half2, char sep, char *line)
{
	int		pos;

	if ((pos = ft_indexof(sep, line)) == -1 )
		return (0);
	*half1 = ft_substr(line, 0, pos);
	*half2 = ft_substr(line, pos + 1, ft_strlen(line));
	if (!*half1 || !*half2)
		error_exit(MALLOC_FAIL_ERROR);
	return (1);
}