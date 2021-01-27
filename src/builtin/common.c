/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:19:07 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/27 22:36:28 by agoodwin         ###   ########.fr       */
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

	if (*list == NULL)
	{
		*list = create(name, method, NULL);
		return ;
	}
	cur = *list;
	while (cur->next != NULL)
		cur = cur->next;

	cur->next = create(name, method, NULL);
}

int		run_builtin(t_builtin builtin, char *name, t_command cmd)
{
	while (builtin != NULL)
	{
		if (name_cmp(name, builtin->name))
		{
			if (builtin->method(cmd.argc, cmd.argv))
				simple_error(strerror(errno), cmd.num, cmd.name);
			return (1);
		}
		builtin = builtin->next;
	}
	return (0);
}

int		name_cmp(char *str1, char *str2)
{
	int		len;

	len = ft_min(ft_strlen(str1), ft_strlen(str2));
	len++;
	return (ft_strncmp(str1, str2, len) == 0);
}

void	free_arr(char **ptr)
{
	char	**start;

	start = ptr; 
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(start);
}

void	print_arr(char **s)
{
	while (*s)
		printf("%s\n", *(s++));
}

int		arr_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}