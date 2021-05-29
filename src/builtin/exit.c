/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:09:50 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/29 14:26:46 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exit(int argc, char **argv)
{
	int	exit_code;

	if (argc > 2)
	{
		g_msh->err_no = EXIT_TOO_MANY_ARGUMENTS;
		return (-1);
	}
	exit_code = argc != 2 ? 0 : ft_atoi(argv[1]);
	exit(exit_code);
}
