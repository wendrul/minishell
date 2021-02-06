/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:16 by wendrul           #+#    #+#             */
/*   Updated: 2021/02/06 03:55:52 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSING_H
# define MSH_PARSING_H


# define UNPARSED 0
# define TEXT 1
# define PIPE 2
# define GREAT 3
# define GREATGREAT 4
# define LESS 5

typedef struct	s_command
{
	char		*name;
	int			argc;
	char		**argv;
	int			num;
}				t_command;

typedef struct	s_cmd_element
{
	char		*str;
	int			type;
}			*	t_cmd_element;

typedef struct	dirent t_dirent;

int		parse_into_args(char *line, char ***argv);
char	*getcmd_path(t_command cmd);
void	del_element(void *ptr);
t_cmd_element new_el(char *str, int type);
void	print_el(void *ptr);

t_list	*parse_quotes(char *line, t_command cmd);
t_list *parse_tokens(t_list *old_lst, t_command cmd);
t_list	**get_cmds(t_list *elements);


#endif