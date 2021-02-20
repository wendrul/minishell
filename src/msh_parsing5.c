/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:12 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 16:20:40 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_semicolons(t_list *elements)
{
	int				size;
	t_cmd_element	e;

	size = 0;
	while (elements->next)
	{
		e = (t_cmd_element)elements->content;
		if (e->type == SEMICOLON && elements)
			size++;
		elements = elements->next;
	}
	return (size);
}

t_list	**get_cmds(t_list *elements)
{
	int		size;
	t_list	**cmds;
	t_list	*cur;
	int		i;

	size = count_semicolons(elements);
	if (!(cmds = (t_list **)malloc(sizeof(*cmds) * (size + 2))))
		error_exit(MALLOC_FAIL_ERROR);
	i = -1;
	while (++i < size + 1)
	{
		cmds[i] = elements;
		cur = elements;
		while (cur->next)
		{
			if (((t_cmd_element)cur->next->content)->type == SEMICOLON)
			{
				elements = cur->next->next;
				ft_lstdelone(cur->next, del_element);
				cur->next = NULL;
				break ;
			}
			cur = cur->next;
		}
	}
	cmds[i] = NULL;
	return (cmds);
}

int		syntaxerror_msg(int type, t_command cmd)
{
	char *msg;
	char *token;

	if (type == PIPE)
		token = "\"|\"";
	else if (type == GREAT)
		token = "\">\"";
	else if (type == GREATGREAT)
		token = "\">>\"";
	else if (type == LESS)
		token = "\"<\"";
	else if (type == SEMICOLON)
		token = "\";\"";
	else
	{
		shell_error(SYNTAX_ERROR, cmd.num);
		return (0);
	}
	if (!(msg = ft_strjoin(SYNTAX_ERROR_UNEXPECTED, token)))
		error_exit(MALLOC_FAIL_ERROR);
	shell_error(msg, cmd.num);
	free(msg);
	return (0);
}

int		syntax_check(t_list *elements, t_command cmd)
{
	t_cmd_element prev;
	t_cmd_element e;

	prev = NULL;
	while (elements)
	{
		e = (t_cmd_element)elements->content;
		if (e->type != TEXT)
		{
			if (!prev || prev->type != TEXT)
				return (syntaxerror_msg(e->type, cmd));
			if (prev && prev->type != SEMICOLON && !elements->next)
				return (syntaxerror_msg(e->type, cmd));
		}
		prev = e;
		elements = elements->next;
	}
	return (1);
}
