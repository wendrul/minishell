/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:50:40 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 15:27:13 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_unset(int argc, char **argv)
{
	int i;
	int j;
	int status;

	i = 1;
	status = 0;
	while (i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_indexof(argv[i][j], ALLOWED_VAR_CHARS) == -1)
			{
				g_msh->err_no = INVALID_PARAMETER;
				status = -1;
			}
		}
		if (dict_rm(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (status);
}
