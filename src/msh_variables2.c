/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:17:25 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 14:17:35 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dict_print(t_var_dict *dict)
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
				printf("%s=%s\n", j->key, j->value);
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

	if ((pos = ft_indexof('=', str)) == -1)
	{
		if (g_msh->verbose)
			simple_error(EXPECTED_KEY_EQUALS_VALUE_STRING, -69, "debug");
		return (NULL);
	}
	if (!(key = ft_substr(str, 0, pos)))
		error_exit(MALLOC_FAIL_ERROR);
	if (!(val = ft_substr(str, pos + 1, ft_strlen(str))))
		error_exit(MALLOC_FAIL_ERROR);
	entry = dict_put(key, val);
	free(key);
	free(val);
	return (entry);
}
