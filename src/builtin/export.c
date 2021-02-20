/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:53:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 18:25:20 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_name(char *str)
{
	int j;

	j = -1;
	while (str[++j])
	{
		if (str[j] == '=')
			break ;
		if (ft_indexof(str[j], ALLOWED_VAR_CHARS) == -1 || ft_isdigit(str[0]))
			return (0);
	}
	return (1);
}

static int	set_envvar(char *str)
{
	int			pos;
	t_var_dict	var;

	if (!((pos = ft_indexof('=', str)) == -1))
	{
		if (pos == 0)
			return (0);
		else
			dict_strput(str)->is_env = 1;
	}
	else if ((var = dict_get(str)))
		var->is_env = 1;
	return (1);
}

int			msh_export(int argc, char **argv)
{
	int			i;
	int			status;

	i = 0;
	status = 0;
	while (++i < argc)
	{
		if (!is_valid_var_name(argv[i]))
		{
			status = -1;
			g_msh->err_no = BAD_VAR_NAME;
			continue ;
		}
		if (!set_envvar(argv[i]))
		{
			status = -1;
			g_msh->err_no = EMPTY_VAR_NAME;
		}
	}
	return (status);
}
