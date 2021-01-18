/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:00:26 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 17:00:26 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define MSH_BUFF_SIZE 4096

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <unistd.h>

# include "libft.h"
# include "get_next_line.h"

typedef struct	s_shell
{
		char	buf[MSH_BUFF_SIZE];
		int		i;
}			*	t_shell;

int		shell();
#endif