/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:18:39 by ede-thom          #+#    #+#             */
/*   Updated: 2021/02/20 13:55:17 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		lst_indexof(int type, t_list *cmd);
int		separate_at(int index, t_list *cmd, t_list **left, t_list **right);
void	lst_append(t_list **head, t_list *tail);

#endif
