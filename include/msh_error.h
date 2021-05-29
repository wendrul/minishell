/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:46:23 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/29 14:22:35 by ede-thom         ###   ########.fr       */
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
# define SYNTAX_ERROR "Syntax error asshole."
# define SYNTAX_ERROR_UNEXPECTED "Syntax error asshole: unexpected "
# define IS_DIRECTORY_ERROR "Is a directory dumbass"

# define HOME_IS_NOT_SET "HOME is not set"
# define INVALID_PARAMETER_MESSAGE "Invalid parameter"
# define BAD_VARIABLE_MESSAGE "Bad variable name"
# define EMPTY_VARIABLE_MESSAGE "Variable name was left blank"
# define PWD_TOO_BIG_MESSAGE "Current directory path is too big to display"
# define UNSPECIFIED_ERROR "Unspecified msh error"
# define EXIT_MANY_ARGS "Bitch choose a code first and then I'll quit u prick"

/*
** Exit statuses
*/
# define SEGFAULT_STATUS 139
# define SIGQUIT_STATUS 131
# define SIGINT_STATUS 2

# define SEGFAULT_MESSAGE "uh oh, stinky segfault (core dumped)"
# define SIGQUIT_MESSAGE "Oh no! it `Quit` (core dumped)"
# define SIGINT_MESSAGE ""
# define UNKNOWN_STATUS_EXIT_MESSAGE "Unexpected exit with status: "

# define NO_HOME_VAR 10
# define INVALID_PARAMETER 11
# define BAD_VAR_NAME 12
# define EMPTY_VAR_NAME 13
# define PWD_TOO_BIG 14
# define EXIT_TOO_MANY_ARGUMENTS 15

# define EXPECTED_KEY_EQUALS_VALUE_STRING "Expected format of `[KEY]=[VALUE]`"

void		error_exit(char *str);
void		simple_error(char *msg, int cmd_no, char *cmd_name);
void		shell_error(char *msg, int cmd_no);
char		*msh_strerror(int error);
void		status_msg(int status);

#endif
