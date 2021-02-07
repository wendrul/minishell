/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:18:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/07 16:28:48 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		separate(char **half1, char **half2, char sep, char *line);
int		lst_indexof(int type, t_list *cmd);
int		separate_at(int index, t_list *cmd, t_list **left, t_list **right);
void 	lst_append(t_list **head, t_list *tail);

#endif