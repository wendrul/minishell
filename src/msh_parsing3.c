/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:08 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/20 10:22:10 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	memmoves_for_replace(char **str, char *o, int var_start, char *val)
{
	ft_memmove(*str, o, var_start);
	ft_memmove(*str + var_start, val, ft_strlen(val));
}

static char	*get_val(char *key)
{
	char	*val;

	if (!(dict_get(key)))
		val = "";
	else
		val = dict_get(key)->value;
	return (val);
}

void	replace_special(char **str, int *var_start)
{
	char	*key;
	char	*val;
	char	*o;
	int		ve;
	int		len;

	o = *str;
	len = ft_strlen(o);
	ve = *var_start + 2;
	key = ft_substr(*str, *var_start + 1, ve - *var_start - 1);
	if (!key)
		error_exit(MALLOC_FAIL_ERROR);
	len -= (ft_strlen(key) + 1);
	val = get_val(key);
	len += ft_strlen(val);
	*str = malloc(sizeof(char) * (len + 1));
	if (!(*str))
		error_exit(MALLOC_FAIL_ERROR);
	ft_bzero(*str, len + 1);
	memmoves_for_replace(str, o, *var_start, val);
	ft_memmove(*str + *var_start + ft_strlen(val), o + ve, ft_strlen(o) - ve);
	free(key);
	free(o);
	*var_start += ft_strlen(val) - 1;
}

void	replace_evar(char **str, int *var_start)
{
	char	*key;
	char	*val;
	char	*o;
	int		ve;
	int		len;

	o = *str;
	len = ft_strlen(o);
	ve = *var_start;
	while ((*str)[++ve] && (ft_indexof((*str)[ve], ALLOWED_VAR_CHARS) != -1))
		;
	key = ft_substr(*str, *var_start + 1, ve - *var_start - 1);
	if (!key)
		error_exit(MALLOC_FAIL_ERROR);
	len -= (ft_strlen(key) + 1);
	val = get_val(key);
	len += ft_strlen(val);
	*str = malloc(sizeof(char) * (len + 1));
	if (!*str)
		error_exit(MALLOC_FAIL_ERROR);
	ft_bzero(*str, len + 1);
	ft_memmove(*str, o, *var_start);
	ft_memmove(*str + *var_start, val, ft_strlen(val));
	ft_memmove(*str + *var_start + ft_strlen(val), o + ve, ft_strlen(o) - ve);
	free(key);
	free(o);
	*var_start += ft_strlen(val) - 1;
}

char	*place_vars(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	ret = ft_strdup(str);
	if (!ret)
		error_exit(MALLOC_FAIL_ERROR);
	while (ret[++i])
	{
		if (ret[i] == '$')
		{
			if (ret[i + 1] == '?')
				replace_special(&ret, &i);
			else
			{
				if (!(ft_isalpha(ret[i + 1]) || ret[i + 1] == '_')
					|| ft_iswhitespace(ret[i + 1]) || !ret[i + 1])
					continue ;
				replace_evar(&ret, &i);
			}
		}
	}
	return (ret);
}
