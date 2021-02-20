/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:04 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 15:34:15 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_el(void *ptr)
{
	t_cmd_element e;

	e = (t_cmd_element)ptr;
	printf("(%s, %s), ", e->str, type_name(e->type));
}

void	add_el(t_list **lst, char *str, int type)
{
	t_list *new;

	if (!str || str[0] == '\0')
		return ;
	if (!(new = ft_lstnew(new_el(str, type))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_lstadd_back(lst, new);
}

t_list	*parse_quotes(char *line, t_command cmd)
{
	t_list	*elements;
	char	*tmp;
	int		i;
	int		j;
	int		start;
	char	quote;
	char	*str;

	i = -1;
	start = 0;
	elements = NULL;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			if (!(tmp = ft_substr(line, start, i - start)))
				error_exit(MALLOC_FAIL_ERROR);
			add_el(&elements, tmp, UNPARSED);
			free(tmp);
			j = i;
			while (line[++j] != line[i])
			{
				if (!line[j])
				{
					shell_error(SYNTAX_ERROR, cmd.num);
					return (NULL);
				}
			}
			if (!(tmp = ft_substr(line, i + 1, j - i - 1)))
				error_exit(MALLOC_FAIL_ERROR);
			if (quote == '"')
			{
				str = place_vars(tmp);
				add_el(&elements, str, TEXT);
				free(str);
			}
			else
				add_el(&elements, tmp, TEXT);
			free(tmp);
			start = j + 1;
			i = start - 1;
		}
	}
	if (!(tmp = ft_substr(line, start, i - start)))
		error_exit(MALLOC_FAIL_ERROR);
	add_el(&elements, tmp, UNPARSED);
	free(tmp);
	return (elements);
}
