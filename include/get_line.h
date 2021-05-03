/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:35:21 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/03 16:57:22 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# define LINE_BUFFER_SIZE 8192
# define NORMAL_RETURN 0
# define UP_ARROW_RETURN 65
# define DOWN_ARROW_RETURN 66
# define EOF_RETURN 1
# define MALLOC_ERROR -1
# define READ_ERROR -2

# define ASCII_ESC 27
# define ASCII_EOT 4
# define ASCII_FF 12


int	get_line(char **line, const char *substitute);


#endif