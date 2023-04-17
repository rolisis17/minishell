/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:10:54 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/17 11:58:51 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **freedom(char **split, char *ze, char *dom)
{
	if (split)
    	freesplit(split);
    if (ze)
        free(ze);
    if (dom)
        free(dom);
    return (NULL);
}

int	get_cmd(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (i);
		if (str[i] == '|' || str[i] == 32)
			return (i);
	}
	return (i);
}