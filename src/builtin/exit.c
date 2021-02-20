/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:09:50 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 21:10:42 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	exit(0);
}
