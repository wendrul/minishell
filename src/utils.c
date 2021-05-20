/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:18:14 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/20 10:53:29 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_append(t_list **head, t_list *tail)
{
	t_list	*cur;

	if (!head)
		return ;
	if (!*head)
	{
		*head = tail;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = tail;
}

int	lst_indexof(int type, t_list *cmd)
{
	int				i;
	t_cmd_element	e;

	i = 0;
	while (cmd)
	{
		e = (t_cmd_element)cmd->content;
		if (e->type == type)
			return (i);
		i++;
		cmd = cmd->next;
	}
	return (-1);
}

int	separate_at(int index, t_list *cmd, t_list **left, t_list **right)
{
	int	i;

	if (index < 0)
		return (0);
	if (index == 0)
	{
		*right = cmd->next;
		ft_lstdelone(cmd, del_element);
		return (1);
	}
	i = -1;
	*left = cmd;
	while (cmd && ++i < index - 1)
		cmd = cmd->next;
	if (i == index - 1)
	{
		if (!cmd->next && !cmd->next->next)
			return (0);
		*right = cmd->next->next;
		ft_lstdelone(cmd->next, del_element);
		cmd->next = NULL;
		return (1);
	}
	else
		return (0);
}
