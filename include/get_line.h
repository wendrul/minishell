/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:35:21 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/01 23:06:56 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# define LINE_BUFFER_SIZE 8192
# define NORMAL_RETURN 0
# define EOF_RETURN 1
# define MALLOC_ERROR -1

# define ASCII_ESC 27
# define ASCII_EOT 4
# define ASCII_FF 12


int	get_line(char **line, const char *substitute);


#endif