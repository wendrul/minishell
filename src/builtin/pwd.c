/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:03:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/17 13:47:42 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_pwd(void)
{
	char dir[PWD_BUFF_SIZE];

	if (getcwd(dir, PWD_BUFF_SIZE) == NULL)
	{
		g_msh->err_no = PWD_TOO_BIG;
		return (-1);
	}
	ft_putendl_fd(dir, STDOUT_FILENO);
	return (0);
}
