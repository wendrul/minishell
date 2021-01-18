/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:19:07 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 23:43:12 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	create(char *name, int (*method)(int, char**), t_builtin next)
{
	t_builtin new;

	if (!(new = (t_builtin)malloc(sizeof(struct s_builtin))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_memmove(new->name, name, ft_strlen(name));
	new->method = method;
	new->next = next;
	return (new);
}

void	add_builtin(t_builtin *list, char *name, int (*method)(int, char**))
{
	t_builtin cur;
	printf("abbbb\n");

	if (*list == NULL)
	{
		*list = create(name, method, NULL);
		return ;
	}
	cur = *list;
	printf("bbbb\n");
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = create(name, method, NULL);
	*list = cur;
}

int		run_builtin(t_builtin builtin, char *name, t_command cmd)
{
	while (builtin != NULL)
	{
		if (name_cmp(name, builtin->name))
		{
			builtin->method(cmd.argc, cmd.argv);
			return (1);
		}
		builtin = builtin->next;
	}
	return (0);
}

int		name_cmp(char *str1, char *str2)
{
	return (ft_strncmp(str1, str2, ft_strlen(str1)) == 0);
}