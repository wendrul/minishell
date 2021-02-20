/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:32:08 by agoodwin          #+#    #+#             */
/*   Updated: 2021/02/20 17:49:41 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!(key = ft_substr(*str, *var_start + 1, ve - *var_start - 1)))
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
	ft_memmove(*str, o, *var_start);
	ft_memmove(*str + *var_start, val, ft_strlen(val));
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
	if (!(key = ft_substr(*str, *var_start + 1, ve - *var_start - 1)))
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
				if (!(ft_isalpha(ret[i + 1]) || ret[i + 1] == '_') 
						|| ft_iswhitespace(ret[i + 1]) || !ret[i + 1])
					continue;
				replace_evar(&ret, &i);
			}
		}
	}
	return (ret);
}
