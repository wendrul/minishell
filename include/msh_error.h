/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:46:23 by ede-thom          #+#    #+#             */
/*   Updated: 2021/01/18 18:14:55 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ERROR_H
# define MSH_ERROR_H

/* Fatal Errors */
# define MALLOC_FAIL_ERROR "malloc funtion failed to allocate memory, exiting"

/* Normal Errors */
# define NOT_FOUND_ERROR "not found"


void		error_exit(char *str);
void		simple_error(char *msg, int cmd_no, char *cmd_name);

#endif