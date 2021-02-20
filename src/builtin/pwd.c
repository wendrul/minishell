/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:03:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/27 22:35:27 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_pwd(void)
{
	char dir[PWD_BUFF_SIZE];

	if (getcwd(dir, PWD_BUFF_SIZE) == NULL)
		return (-1);
	printf("%s\n", dir);
	return (0);
}
