/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:30:06 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/01 21:38:53 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    insert_front(char *value)
{
    t_node tmp;

    tmp = (t_node)malloc(sizeof(t_node));
    if (!tmp)
        error_exit(MALLOC_FAIL_ERROR);
	tmp->value = value;
	tmp->prev = NULL;
	tmp->next = NULL;
	if (g_msh->head == NULL)
    {
		g_msh->head = tmp;
		return ;
	}
	g_msh->head->prev = tmp;
	tmp->next = g_msh->head; 
	g_msh->head = tmp;
}