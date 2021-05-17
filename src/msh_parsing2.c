/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:04 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/17 13:54:43 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_el(t_list **lst, char *str, int type)
{
	t_list *new;

	if (!str || str[0] == '\0')
		return ;
	if (!(new = ft_lstnew(new_el(str, type))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_lstadd_back(lst, new);
}

static int	quote_loop_logic(char *line, t_command cmd, int i,
								t_list **elements)
{
	char	*str;
	char	*tmp;
	int		quote;
	int		j;

	j = i;
	quote = line[i];
	while (line[++j] != line[i])
		if (!line[j])
		{
			shell_error(SYNTAX_ERROR, cmd.num);
			return (-5);
		}
	if (!(tmp = ft_substr(line, i + 1, j - i - 1)))
		error_exit(MALLOC_FAIL_ERROR);
	if (quote == '"')
	{
		str = place_vars(tmp);
		add_el(elements, str, TEXT);
		free(str);
	}
	else
		add_el(elements, tmp, TEXT);
	free(tmp);
	return (j);
}

t_list		*parse_quotes(char *line, t_command cmd)
{
	t_list	*elements;
	char	*tmp;
	int		i;
	int		start;

	i = -1;
	start = 0;
	elements = NULL;
	while (line[++i])
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!(tmp = ft_substr(line, start, i - start)))
				error_exit(MALLOC_FAIL_ERROR);
			add_el(&elements, tmp, UNPARSED);
			free(tmp);
			if ((start = quote_loop_logic(line, cmd, i, &elements) + 1) < 0)
				return (NULL);
			i = start - 1;
		}
	if (!(tmp = ft_substr(line, start, i - start)))
		error_exit(MALLOC_FAIL_ERROR);
	add_el(&elements, tmp, UNPARSED);
	free(tmp);
	return (elements);
}
