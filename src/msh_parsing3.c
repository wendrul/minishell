/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:08 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 15:33:50 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_special(char **str, int *var_start)
{
	char *key;
	char *val;
	char *old;
	int var_end;
	int len;

	old = *str;
	len = ft_strlen(old);
	var_end = *var_start + 2;
	if (!(key = ft_substr(*str, *var_start + 1, var_end - *var_start - 1)))
		error_exit(MALLOC_FAIL_ERROR);
	len -= (ft_strlen(key) + 1);
	if (!(dict_get(key)))
		val = "";
	else
		val = dict_get(key)->value;
	len += ft_strlen(val);
	if (!(*str = malloc(sizeof(char) * (len + 1))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_bzero(*str, len + 1);
	ft_memmove(*str, old, *var_start);
	ft_memmove(*str + *var_start, val, ft_strlen(val));
	ft_memmove(*str + *var_start + ft_strlen(val), old + var_end, ft_strlen(old) - var_end);
	free(key);
	free(old);
	*var_start += ft_strlen(val) - 1;
}

void	replace_evar(char **str, int *var_start)
{
	char *key;
	char *val;
	char *old;
	int var_end;
	int len;

	old = *str;
	len = ft_strlen(old);
	var_end = *var_start;
	while ((*str)[++var_end] && ft_isalnum((*str)[var_end]));
	if (!(key = ft_substr(*str, *var_start + 1, var_end - *var_start - 1)))
		error_exit(MALLOC_FAIL_ERROR);
	len -= (ft_strlen(key) + 1);
	if (!(dict_get(key)))
		val = "";
	else
		val = dict_get(key)->value;
	len += ft_strlen(val);
	if (!(*str = malloc(sizeof(char) * (len + 1))))
		error_exit(MALLOC_FAIL_ERROR);
	ft_bzero(*str, len + 1);
	ft_memmove(*str, old, *var_start);
	ft_memmove(*str + *var_start, val, ft_strlen(val));
	ft_memmove(*str + *var_start + ft_strlen(val), old + var_end, ft_strlen(old) - var_end);
	free(key);
	free(old);
	*var_start += ft_strlen(val) - 1;
}

char	*place_vars(char *str)
{
	int i;
	char *ret;

	i = -1;
	if (!(ret = ft_strdup(str)))
		error_exit(MALLOC_FAIL_ERROR);
	while (ret[++i])
	{
		if (ret[i] == '$')
		{
			if (ret[i + 1] == '?')
				replace_special(&ret, &i);
			else
			{
				if (!ft_isalpha(ret[i + 1]) || ft_iswhitespace(ret[i + 1]) || !ret[i + 1])
					continue;
				replace_evar(&ret, &i);
			}
		}
	}
	return (ret);
}
