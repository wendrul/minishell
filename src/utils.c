/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:18:14 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/07 16:37:04 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	lst_append(t_list **head, t_list *tail)
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

int		lst_indexof(int type, t_list *cmd)
{
	int i;
	t_cmd_element e;

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

int		separate(char **half1, char **half2, char sep, char *line)
{
	//can probably be deleted
	int		pos;

	if ((pos = ft_indexof(sep, line)) == -1 )
		return (0);
	*half1 = ft_substr(line, 0, pos);
	*half2 = ft_substr(line, pos + 1, ft_strlen(line));
	if (!*half1 || !*half2)
		error_exit(MALLOC_FAIL_ERROR);
	return (1);
}

int		separate_at(int index, t_list *cmd, t_list **left, t_list **right)
{
	int	i;

	*right = NULL;
	*left = NULL;
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