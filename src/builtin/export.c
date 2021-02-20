/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:53:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/28 22:30:32 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_export(int argc, char **argv)
{
	int			i;
	int			pos;
	t_var_dict	var;

	i = 1;
	while (i < argc)
	{
		if (!(pos = ft_indexof('=', argv[i]) == -1))
			dict_strput(argv[i])->is_env = 1;
		else if ((var = dict_get(argv[1])))
			var->is_env = 1;
		i++;
	}
	return (0);
}
