/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:47:59 by marvin            #+#    #+#             */
/*   Updated: 2021/01/15 10:47:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_shell sh;
	if (!(sh = (t_shell)malloc(sizeof(struct s_shell))))
	exit(0);
	while (1)
		shell(sh);
	free(sh);
	return (0);
}