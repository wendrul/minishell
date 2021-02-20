/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:18:38 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 16:02:01 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_into_args(t_list *cmd, char ***argv)
{
	int				size;
	int				i;
	t_cmd_element	e;

	size = ft_lstsize(cmd);
	*argv = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (cmd)
	{
		e = (t_cmd_element)cmd->content;
		if (!((*argv)[i] = ft_strdup(e->str)))
			error_exit(MALLOC_FAIL_ERROR);
		i++;
		cmd = cmd->next;
	}
	(*argv)[i] = NULL;
	return (size);
}

int		check_dir(t_command *cmd, DIR *dir, char *cur_path)
{
	t_dirent	*dir_ent;
	char		*path;

	while ((dir_ent = readdir(dir)))
	{
		if (name_cmp(dir_ent->d_name, cmd->name))
		{
			if ((path = ft_strjoin(cur_path, "/")) == NULL)
				error_exit(MALLOC_FAIL_ERROR);
			if ((cmd->name = ft_strjoin(path, cmd->name)) == NULL)
				error_exit(MALLOC_FAIL_ERROR);
			free(path);
			closedir(dir);
			return (1);
		}
	}
	return (0);
}

char	*getcmd_path(t_command cmd)
{
	char		*path;
	char		**pathv;
	int			i;
	DIR			*dir;

	if (!dict_get(ENV_PATH))
		return (cmd.name);
	path = dict_get(ENV_PATH)->value;
	if (!(pathv = ft_split(path, ':')))
		error_exit(SPLIT_FAIL_ERROR);
	i = -1;
	while (pathv[++i])
	{
		if ((dir = opendir(pathv[i])) == NULL)
			continue ;
		if (check_dir(&cmd, dir, pathv[i]))
		{
			free_arr(pathv);
			return (cmd.name);
		}
		closedir(dir);
	}
	free_arr(pathv);
	return (cmd.name);
}

char	*type_name(int type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == GREAT)
		return ("GREAT");
	else if (type == GREATGREAT)
		return ("GREATGREAT");
	else if (type == LESS)
		return ("LESS");
	else if (type == TEXT)
		return ("TEXT");
	else if (type == UNPARSED)
		return ("UNPARSED");
	else if (type == SEMICOLON)
		return ("SEMICOLON");
	else
		return ("undef");
}
