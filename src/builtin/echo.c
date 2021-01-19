/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 23:43:58 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/19 15:18:58 by ede-thom         ###   ########.fr       */
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
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
	}
	if (endl)
		printf("\n");
	fflush(stdout);
	return (0);
}