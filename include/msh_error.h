/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:46:23 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/01 23:36:54 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ERROR_H
# define MSH_ERROR_H

/* Fatal Errors */
# define MALLOC_FAIL_ERROR "malloc funtion failed to allocate memory, exiting"
# define FAILED_TO_GET_NEXT_LINE "Failed on get_next_line (malloc?)"
# define SPLIT_FAIL_ERROR "Failed to split string (malloc or null string input probably)"

/* Normal Errors */
# define NOT_FOUND_ERROR "not found"

# define EXPECTED_KEY_EQUALS_VALUE_STRING "Expected string of type \
								'[KEY]=[VALUE]' but no `=` was found"


void		error_exit(char *str);
void		simple_error(char *msg, int cmd_no, char *cmd_name);

#endif