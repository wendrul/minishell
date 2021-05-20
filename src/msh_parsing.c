/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:18:38 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/20 10:12:26 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_into_args(t_list *cmd, char ***argv)
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
		(*argv)[i] = ft_strdup(e->str);
		if (!(*argv)[i])
			error_exit(MALLOC_FAIL_ERROR);
		i++;
		cmd = cmd->next;
	}
	(*argv)[i] = NULL;
	return (size);
}

int	check_dir(t_command *cmd, DIR *dir, char *cur_path)
{
	t_dirent	*dir_ent;
	char		*path;

	dir_ent = readdir(dir);
	while (dir_ent)
	{
		if (name_cmp(dir_ent->d_name, cmd->name))
		{
			path = ft_strjoin(cur_path, "/");
			if (path == NULL)
				error_exit(MALLOC_FAIL_ERROR);
			cmd->name = ft_strjoin(path, cmd->name);
			if (cmd->name == NULL)
				error_exit(MALLOC_FAIL_ERROR);
			free(path);
			closedir(dir);
			return (1);
		}
		dir_ent = readdir(dir);
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
	pathv = ft_split(path, ':');
	if (!pathv)
		error_exit(SPLIT_FAIL_ERROR);
	i = -1;
	while (pathv[++i])
	{
		dir = opendir(pathv[i]);
		if (dir == NULL)
			continue ;
		if (check_dir(&cmd, dir, pathv[i]))
			break ;
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
