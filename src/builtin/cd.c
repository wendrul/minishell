/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:02:13 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/25 10:55:14 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(int argc, char **argv)
{
	char	old_pwd[PWD_BUFF_SIZE];
	char	new_pwd[PWD_BUFF_SIZE];
	char	*path;

	if (!getcwd(old_pwd, PWD_BUFF_SIZE))
		return (1);
	if (!dict_get(ENV_HOME))
	{
		g_msh->err_no = NO_HOME_VAR;
		return (-1);
	}
	if (argc == 1)
		path = dict_get(ENV_HOME)->value;
	else
		path = argv[1];
	if (chdir(path))
		return (1);
	if (!getcwd(new_pwd, PWD_BUFF_SIZE))
		return (1);
	dict_put(ENV_OLDPWD, old_pwd);
	dict_put(ENV_PWD, new_pwd);
	return (0);
}
