/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:19:07 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 14:02:17 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	create(char *name, int (*method)(int, char**),
							t_builtin next)
{
	t_builtin	new;
	int			i;

	if (!(new = (t_builtin)malloc(sizeof(struct s_builtin))))
		error_exit(MALLOC_FAIL_ERROR);
	i = -1;
	while (++i < 256)
		new->name[i] = 0;
	ft_memmove(new->name, name, ft_strlen(name));
	new->method = method;
	new->next = next;
	return (new);
}

void				add_builtin(t_builtin *list, char *name,
							int (*method)(int, char**))
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

int					run_builtin(t_builtin builtin, char *name,
							t_command cmd, int *status)
{
	while (builtin != NULL)
	{
		if (name_cmp(name, builtin->name))
		{
			if ((*status = builtin->method(cmd.argc, cmd.argv)))
			{
				if (*status == -1)
				{
					*status = 1;
					simple_error(msh_strerror(g_msh->err_no),
												cmd.num, cmd.name);
				}
				else
					simple_error(strerror(errno), cmd.num, cmd.name);
			}
			return (1);
		}
		builtin = builtin->next;
	}
	return (0);
}

int					name_cmp(char *str1, char *str2)
{
	int		len;

	len = ft_min(ft_strlen(str1), ft_strlen(str2));
	len++;
	return (ft_strncmp(str1, str2, len) == 0);
}
