/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:18:38 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 18:24:15 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_into_args(char *line, char ***argv)
{
	int i;

	*argv = ft_split_charset(line, "\f\t\n\r\v ");
	i = 0;
	while ((*argv)[i])
		i++;
	return i;
}