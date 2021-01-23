/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:03:41 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/23 18:23:35 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_VARIABLES_H
# define MSH_VARIABLES_H

# define HASHSIZE 4

# include "minishell.h"

typedef struct	s_var_dict
{
	struct s_var_dict	*next;
	char				*name;
	char				*value;
}			*	t_var_dict;

t_var_dict g_hashtab[HASHSIZE];

t_var_dict	dict_get(char *s);
t_var_dict	dict_put(char *name, char *defn);

#endif