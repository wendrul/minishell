/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:30:06 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/20 10:51:57 by ede-thom         ###   ########.fr       */
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
	t_node	tmp;

	tmp = (t_node)malloc(sizeof(struct s_node));
	if (!tmp)
		error_exit(MALLOC_FAIL_ERROR);
	tmp->value = ft_strdup(value);
	if (tmp->value == NULL)
		error_exit(MALLOC_FAIL_ERROR);
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

int	is_same_as_last(char *s)
{
	if (g_msh->head == NULL)
		return (0);
	return (name_cmp(s, g_msh->head->value));
}
