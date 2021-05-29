/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:09:50 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/29 22:15:50 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	msh_exit(int argc, char **argv)
{
	int	exit_code;

	if (argc > 2)
	{
		g_msh->err_no = EXIT_TOO_MANY_ARGUMENTS;
		return (-1);
	}
	exit_code = 0;
	if (argc == 2)
	{
		if (!is_numeric(argv[1]))
		{
			g_msh->err_no = EXIT_NOT_NUMERIC;
			return (-1);
		}
		exit_code = ft_atoi(argv[1]);
	}
	exit(exit_code);
}
