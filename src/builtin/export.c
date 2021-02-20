/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:53:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 18:00:12 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	errorset(int error)
{
	g_msh->err_no = error;
	return (-1);
}

int			msh_export(int argc, char **argv)
{
	int			i;
	int			pos;
	int			j;
	int			status;
	t_var_dict	var;

	i = 0;
	status = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == '=')
				break ;
			if (ft_indexof(argv[i][j], ALLOWED_VAR_CHARS) == -1 || ft_isdigit(argv[i][0]))
			{
				status = errorset(BAD_VAR_NAME);
				continue ;
			}
		}
		if (!((pos = ft_indexof('=', argv[i])) == -1))
		{
			if (pos == 0)
			{
				status = errorset(EMPTY_VAR_NAME);
				continue ;
			}
			else
				dict_strput(argv[i])->is_env = 1;
		}
		else if ((var = dict_get(argv[1])))
			var->is_env = 1;
	}
	return (status);
}
