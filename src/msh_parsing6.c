/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:36:02 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/20 10:34:11 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_element(void *ptr)
{
	t_cmd_element	e;

	e = (t_cmd_element)ptr;
	free(e->str);
	free(e);
}

t_cmd_element	new_el(char *str, int type)
{
	t_cmd_element	e;

	e = (t_cmd_element)malloc(sizeof(*e));
	if (!e)
		error_exit(MALLOC_FAIL_ERROR);
	e->str = ft_strdup(str);
	if (!e->str)
		error_exit(MALLOC_FAIL_ERROR);
	e->type = type;
	return (e);
}
