/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:17:25 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/20 10:51:40 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dict_print(t_var_dict *dict)
{
	t_var_dict	*i;
	t_var_dict	j;
	int			c;

	i = dict;
	c = 0;
	while (c < HASHSIZE)
	{
		j = *i;
		while (j)
		{
			if (j->is_env)
			{
				ft_putstr_fd(j->key, STDOUT_FILENO);
				ft_putstr_fd("=", STDOUT_FILENO);
				ft_putendl_fd(j->value, STDOUT_FILENO);
			}
			j = j->next;
		}
		c++;
		i++;
	}
}

t_var_dict	dict_strput(char *str)
{
	t_var_dict	entry;
	char		*key;
	char		*val;
	int			pos;

	pos = ft_indexof('=', str);
	if (pos == -1)
		return (NULL);
	key = ft_substr(str, 0, pos);
	if (!key)
		error_exit(MALLOC_FAIL_ERROR);
	val = ft_substr(str, pos + 1, ft_strlen(str));
	if (!val)
		error_exit(MALLOC_FAIL_ERROR);
	entry = dict_put(key, val);
	free(key);
	free(val);
	return (entry);
}
