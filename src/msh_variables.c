/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:08:41 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/16 17:15:25 by ede-thom         ###   ########.fr       */
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
		new->is_env = 0;
        g_msh->dict[hash] = new;
    }
	else
        free((void *) new->value);
    if (!(new->value = ft_strdup(val)))
       error_exit(MALLOC_FAIL_ERROR);
    return new;
}

int		dict_rm(char *key)
{
	t_var_dict var;
	t_var_dict prev;

	var = g_msh->dict[get_hash(key)];
	if (var && name_cmp(key, var->key))
	{
		g_msh->dict[get_hash(key)] = var->next;
		free(var->key);
		free(var->value);
		free(var);
		return (1);
	}
	prev = NULL;
	while (var)
	{
		if (name_cmp(key, var->key))
		{
			if (prev != NULL)
				prev->next = var->next;
			free(var->key);
			free(var->value);
			free(var);
			return (1);
		}
		prev = var;
		var = var->next;
	}
	return (0);
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