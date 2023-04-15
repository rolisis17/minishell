/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:10:54 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/15 15:18:41 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **freedom(char **split, char *ze, char *dom)
{
    freesplit(split);
    if (ze)
        free(ze);
    if (dom)
        free(dom);
    return (NULL);
}