/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 23:43:58 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/02 18:32:15 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_echo(int argc, char **argv)
{
	int i;
	int endl;

	endl = 1;
	if (argc >= 2)
		endl = !name_cmp(argv[1], "-n");
	i = endl ? 0 : 1;
	while (++i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (endl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
