/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:59:16 by wendrul           #+#    #+#             */
/*   Updated: 2021/05/25 13:43:56 by ede-thom         ###   ########.fr       */
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
# define SEMICOLON 6

typedef struct s_command
{
	char		*name;
	int			argc;
	char		**argv;
	int			num;
}t_command;

typedef struct s_cmd_element
{
	char		*str;
	int			type;
}*t_cmd_element;

typedef typeof(struct dirent)	t_dirent;

int				parse_into_args(t_list *cmd, char ***argv);
char			*getcmd_path(t_command cmd);
void			del_element(void *ptr);
t_cmd_element	new_el(char *str, int type);

t_list			*parse_quotes(char *line, t_command cmd);
t_list			*parse_tokens(t_list *old_lst, t_command cmd);
t_list			**get_cmds(t_list *elements);
int				syntax_check(t_list *elements, t_command cmd);
char			*place_vars(char *str);

#endif
