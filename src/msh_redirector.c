/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:04:33 by agoodwin          #+#    #+#             */
/*   Updated: 2021/05/29 15:19:59 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_greats(char *filename, int type, t_command cmd_meta)
{
	int	fd;
	int	flags;

	flags = O_CREAT | O_RDWR;
	if (type == GREAT)
		flags |= O_TRUNC;
	else if (type == GREATGREAT)
		flags |= O_APPEND;
	else
		error_exit("Expected > or >>");
	fd = open(filename, flags, 0777);
	if (fd == -1)
	{
		shell_error(better_strerror(errno), cmd_meta.num);
		return (0);
	}
	g_msh->redir_out_fd = fd;
	dup2(fd, STDOUT_FILENO);
	return (1);
}

int	handle_less(char *filename, t_command cmd_meta)
{
	int	fd;

	if (g_msh->redir_in_fd != -1)
		close(g_msh->redir_in_fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		shell_error(better_strerror(errno), cmd_meta.num);
		return (0);
	}
	g_msh->redir_in_fd = fd;
	dup2(fd, STDIN_FILENO);
	return (1);
}

int	redirect(char *filename, int type, t_command cmd_meta)
{
	if ((type == GREAT || type == GREATGREAT) && g_msh->redir_out_fd != -1)
		close(g_msh->redir_out_fd);
	if (type == GREAT || type == GREATGREAT)
		return (handle_greats(filename, type, cmd_meta));
	else if (type == LESS)
		return (handle_less(filename, cmd_meta));
	return (1);
}

int	redirections(t_list **cmd_ptr, t_command m)
{
	t_list			*after_redir;
	t_list			**t;
	t_cmd_element	e;

	t = cmd_ptr;
	while (*t)
	{
		e = (t_cmd_element)(*t)->content;
		if (e->type == GREAT || e->type == GREATGREAT || e->type == LESS)
		{
			if (!redirect(((t_cmd_element)(*t)->next->content)->str,
				e->type, m))
				return (-1);
			after_redir = (*t)->next->next;
			ft_lstdelone((*t)->next, del_element);
			ft_lstdelone(*t, del_element);
			*t = after_redir;
			continue ;
		}
		t = &((*t)->next);
	}
	return (0);
}
