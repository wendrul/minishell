/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:08:41 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/27 23:40:18 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	var = g_msh->dict[hash(s)];
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
        np->next = g_msh->dict[hashval];
        g_msh->dict[hashval] = np;
    } else
        free((void *) np->value);
    if ((np->value = ft_strdup(defn)) == NULL)
       return NULL;
    return np;
}

void		dict_print(char **envp)
{
	char	*tmp;
	int		pos;

	while(envp)
	{
		pos = ft_indexof('=', *envp);
		if (!(tmp = ft_substr(*envp, 0, pos)))
			error_exit(MALLOC_FAIL_ERROR);
		printf("%s=%s", tmp, dict_get(tmp)->value);
		free(tmp);
		envp++;
	}
}