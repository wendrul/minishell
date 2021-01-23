/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:18:38 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/23 00:53:56 by ede-thom         ###   ########.fr       */
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
	return (i);
}

char	*getcmd_path(t_command cmd)
{
	char		*path;
	char		**pathv;
	int			i;
	DIR			*dir;
	t_dirent	*dir_ent;

	path = lookup("PATH");
	if (!(pathv = ft_split_charset(path, ":")))
		error_exit(MALLOC_FAIL_ERROR);
	i = -1;
	while (pathv[++i])
	{
		if ((dir = opendir(pathv[i])) == NULL)
			break ;
		while (dir_ent != NULL)
		{
			dir_ent = readdir(dir);
			if (name_cmp(dir_ent->d_name, cmd.name))
			{
				if ((cmd.name = ft_strjoin(pathv[i], cmd.name)) == NULL)
					error_exit(MALLOC_FAIL_ERROR);
				closedir(dir);
				free_arr(pathv);
				return (cmd.name);
			}
		}
		closedir(dir);
		free_arr(pathv);
		return (cmd.name);
	}	
}
