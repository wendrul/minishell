/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:08:41 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/20 10:49:23 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	get_hash(char *key)
{
	int				i;
	unsigned int	hash;

	i = -1;
	hash = 0;
	while (key[++i])
		hash = *key + 31 * hash;
	return (hash % HASHSIZE);
}

t_var_dict	dict_get(char *key)
{
	t_var_dict	var;

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
	t_var_dict		new;
	unsigned int	hash;

	new = dict_get(key);
	if (!new)
	{
		new = (t_var_dict)malloc(sizeof(struct s_var_dict));
		if (!new)
			error_exit(MALLOC_FAIL_ERROR);
		new->key = ft_strdup(key);
		if (!new->key)
			error_exit(MALLOC_FAIL_ERROR);
		hash = get_hash(key);
		new->next = g_msh->dict[hash];
		new->is_env = 0;
		g_msh->dict[hash] = new;
	}
	else
		free((void *)new->value);
	new->value = ft_strdup(val);
	if (!new->value)
		error_exit(MALLOC_FAIL_ERROR);
	return (new);
}

int	del_if_match(char *key, t_var_dict *var_ptr, t_var_dict prev)
{
	t_var_dict	var;

	var = *var_ptr;
	if (name_cmp(key, var->key))
	{
		if (prev != NULL)
			prev->next = var->next;
		else
		{
			g_msh->dict[get_hash(key)] = var->next;
		}
		free(var->key);
		free(var->value);
		free(var);
		return (1);
	}
	return (0);
}

int	dict_rm(char *key)
{
	t_var_dict	var;
	t_var_dict	prev;

	prev = NULL;
	var = g_msh->dict[get_hash(key)];
	if (!var)
		return (0);
	while (var)
	{
		if (del_if_match(key, &var, prev))
			return (1);
		prev = var;
		var = var->next;
	}
	return (0);
}
