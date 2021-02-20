/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:46:23 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 14:33:23 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ERROR_H
# define MSH_ERROR_H

/*
** Fatal Errors
*/
# define MALLOC_FAIL_ERROR "malloc funtion failed to allocate memory, exiting"
# define FAILED_TO_GET_NEXT_LINE "Failed on get_next_line (malloc?)"
# define SPLIT_FAIL_ERROR "Failed to split string (malloc or null string input)"
# define FAILED_TO_CREATE_PIPE "Failed to create pipe"
# define FAILED_FORK "Failed to fork"

/*
** Normal Errors
*/
# define NOT_FOUND_ERROR "not found"
# define SYNTAX_ERROR "Syntax error."
# define SYNTAX_ERROR_UNEXPECTED "Syntax error: unexpected "
# define IS_DIRECTORY_ERROR "Is a directory dumbass"
# define HOME_IS_NOT_SET "HOME is not set"
# define UNSPECIFIED_ERROR "Unspecified msh error"

/*
** Exit statuses
*/
# define SEGFAULT_STATUS 139
# define SIGQUIT_STATUS 131
# define SIGINT_STATUS 2

# define SEGFAULT_MESSAGE "Segfault (core dumped)"
# define SIGQUIT_MESSAGE "Quit (dump)"
# define SIGINT_MESSAGE ""
# define UNKNOWN_STATUS_EXIT_MESSAGE "Unexpected exit with status: "

# define NO_HOME_VAR 10

# define EXPECTED_KEY_EQUALS_VALUE_STRING "Expected format of '[KEY]=[VALUE]'"

void		error_exit(char *str);
void		simple_error(char *msg, int cmd_no, char *cmd_name);
void		shell_error(char *msg, int cmd_no);
char		*msh_strerror(int error);
void		status_msg(int status);

#endif
