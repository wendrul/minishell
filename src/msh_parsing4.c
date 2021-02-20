/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:10 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 16:19:31 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*add_txt(char *line)
{
	t_list	*newlst;
	char	**arr;
	char	**ptr;
	char	*str;

	newlst = NULL;
	if (!(arr = ft_split_charset(line, " \f\t\n\r\v")))
		error_exit(SPLIT_FAIL_ERROR);
	ptr = arr;
	while (*arr)
	{
		str = place_vars(*arr);
		add_el(&newlst, str, TEXT);
		free(str);
		arr++;
	}
	free_arr(ptr);
	return (newlst);
}

int		typeof_token(char *str)
{
	if (str[0] == '|')
		return (PIPE);
	else if (str[0] == ';')
		return (SEMICOLON);
	else if (str[0] == '<')
		return (LESS);
	else if (str[0] == '>' && str[1] != '>')
		return (GREAT);
	else if (str[0] == '>' && str[1] == '>')
		return (GREATGREAT);
	return (-1);
}

t_list	*parse_token(char *str)
{
	t_list	*newlst;
	int		i;
	int		type;
	char	*tmp;
	int		start;
	int		tokensize;

	i = -1;
	start = 0;
	newlst = NULL;
	while (str[++i])
	{
		if (ft_indexof(str[i], "|><;") != -1)
		{
			tokensize = 0;
			type = typeof_token(&str[i]);
			if (type == GREATGREAT)
			{
				i++;
				tokensize++;
			}
			if (!(tmp = ft_substr(str, start, i - start - tokensize)))
				error_exit(MALLOC_FAIL_ERROR);
			lst_append(&newlst, add_txt(tmp));
			free(tmp);
			add_el(&newlst, "-TOKEN-", type);
			start = i + 1;
		}
	}
	if (!(tmp = ft_substr(str, start, i - start)))
		error_exit(MALLOC_FAIL_ERROR);
	lst_append(&newlst, add_txt(tmp));
	free(tmp);
	return (newlst);
}

t_list	*parse_tokens(t_list *old_lst, t_command cmd)
{
	t_list			*newlst;
	t_list			*cur;
	t_cmd_element	e;

	(void)&cmd;
	cur = old_lst;
	newlst = NULL;
	while (cur)
	{
		e = (t_cmd_element)cur->content;
		if (e->type != UNPARSED)
			add_el(&newlst, e->str, e->type);
		else
			lst_append(&newlst, parse_token(e->str));
		cur = cur->next;
	}
	ft_lstclear(&old_lst, del_element);
	return (newlst);
}
