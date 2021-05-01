/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:30:06 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/01 22:30:40 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*on_up_arrow(void)
{
	if (g_msh->head == NULL)
		return (NULL);
	if (g_msh->cur == NULL)
	{
		g_msh->cur = g_msh->head;
		return (g_msh->cur->value);
	}
	if (g_msh->cur->next == NULL)
		return (NULL);
	g_msh->cur = g_msh->cur->next;
	return (g_msh->cur->value);
}

char	*on_down_arrow(void)
{
	if (g_msh->head == NULL || g_msh->cur == NULL)
		return (NULL);
	if (g_msh->cur->prev == NULL)
	{
		g_msh->cur = NULL;
		return ("");
	}
	g_msh->cur = g_msh->cur->prev;
	return (g_msh->cur->value);
}

void	insert_front(char *value)
{
	t_node tmp;

	tmp = (t_node)malloc(sizeof(struct s_node));
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
	g_msh->cur = NULL;
}
