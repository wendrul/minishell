/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:02:13 by agoodwin          #+#    #+#             */
/*   Updated: 2021/01/27 22:41:45 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_cd(int argc, char **argv)
{
    if (argc == 1)
    {
        chdir(dict_get("HOME")->value);
        return (0);
    }
    return (chdir(argv[1]));
}