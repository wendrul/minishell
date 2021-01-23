/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:08:41 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/23 18:27:45 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_variables.h"

unsigned	hash(char *s)
{
	int i;
	unsigned hashval;

	i = -1;
	while (s[++i])
		hashval = *s + 31 * hashval;
	return (hashval % HASHSIZE);
}

t_var_dict		dict_get(char *s)
{
	t_var_dict var;

	var = g_hashtab[hash(s)];
	while (var != NULL)
	{
		if (name_cmp(s, var->name))
			return (var);
		var = var->next;
	}
	return (NULL);
}

t_var_dict	dict_put(char *name, char *defn)
{
    t_var_dict np;
    unsigned hashval;
    if ((np = dict_get(name)) == NULL) 
	{
        np = (t_var_dict) malloc(sizeof(*np));
        if (np == NULL || (np->name = ft_strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = g_hashtab[hashval];
        g_hashtab[hashval] = np;
    } else
        free((void *) np->value);
    if ((np->value = ft_strdup(defn)) == NULL)
       return NULL;
    return np;
}
