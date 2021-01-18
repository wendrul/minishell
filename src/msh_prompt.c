/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:06 by wendrul           #+#    #+#             */
/*   Updated: 2021/01/18 17:00:06 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell()
{
	char *line;
	printf("€ ");
	fflush(stdout);
	if (get_next_line(STDIN_FILENO, &line) == -1)
		exit(0);
	return printf("msh: %s:\n", line);
}