/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:16 by wendrul           #+#    #+#             */
/*   Updated: 2021/01/18 18:24:09 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSING_H
# define MSH_PARSING_H

typedef struct	s_command
{
	int			argc;
	char		**argv;
	int			num;
}				t_command;

int	parse_into_args(char *line, char ***argv);

#endif