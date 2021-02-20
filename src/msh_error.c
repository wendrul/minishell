/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 22:12:10 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 14:05:18 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

void	simple_error(char *msg, int cmd_no, char *cmd_name)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putnbr_fd(cmd_no, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	shell_error(char *msg, int cmd_no)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putnbr_fd(cmd_no, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

char	*msh_strerror(int error)
{
	if (error == NO_HOME_VAR)
		return (HOME_IS_NOT_SET);
	return (UNSPECIFIED_ERROR);
}

void	status_msg(int status)
{
	if (status == SEGFAULT_STATUS)
		ft_putstr_fd(SEGFAULT_MESSAGE, STDERR_FILENO);
	else if (status == SIGQUIT_STATUS)
		ft_putstr_fd(SIGQUIT_MESSAGE, STDERR_FILENO);
	else
	{
		ft_putstr_fd(UNKNOWN_STATUS_EXIT_MESSAGE, STDERR_FILENO);
		ft_putnbr_fd(status, STDERR_FILENO);
	}
	write(STDERR_FILENO, "\n", 1);
}
