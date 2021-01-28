/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:08:41 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/28 20:27:03 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned	get_hash(char *key)
{
	int i;
	unsigned hash;

	i = -1;
	hash = 0;
	while (key[++i])
		hash = *key + 31 * hash;
	return (hash % HASHSIZE);
}

t_var_dict		dict_get(char *key)
{
	t_var_dict var;

	var = g_msh->dict[get_hash(key)];
	while (var)
	{
		if (name_cmp(key, var->key))
			return (var);
		var = var->next;
	}
	return (NULL);
}

t_var_dict	dict_put(char *key, char *val)
{
    t_var_dict	new;
    unsigned	hash;

    if (!(new = dict_get(key))) 
	{
        new = (t_var_dict) malloc(sizeof(*new));
        if (!new || !(new->key = ft_strdup(key)))
			error_exit(MALLOC_FAIL_ERROR);
        hash = get_hash(key);
        new->next = g_msh->dict[hash];
        g_msh->dict[hash] = new;
    }
	else
        free((void *) new->value);
    if (!(new->value = ft_strdup(val)))
       error_exit(MALLOC_FAIL_ERROR);
    return new;
}

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