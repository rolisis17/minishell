/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 06:48:55 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/28 22:11:37 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int word_count(char **split);

char **add_split(char **split, char *new)
{
    int     i;
    int     len;
    char    **new_split;

    if (split[0] == NULL) // this might not be needed now its fixed
        return (ft_split(new, 32));
    i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * (i + 2));
    if (!new_split)
		return (0);
    i = -1;
    while (split[++i])
    {
        len = ft_strlen(split[i]);
        new_split[i] = ft_calloc(len + 1, sizeof(char));
        ft_strlcpy(new_split[i], split[i], len + 1);
    }
    len = ft_strlen(new);
    new_split[i] = ft_calloc(len + 1, sizeof(char));
    ft_strlcpy(new_split[i], new, len + 1);
    new_split[++i] = NULL;
    freesplit(split);
    return(new_split);
}

static int word_count(char **split)
{
    int i;

    i = 0;
    while (split[i])
        i++;
    return (i);
}

void	freesplit(char **splited)
{
	int	counter;

	counter = 0;
	while (splited[counter])
	{
		free(splited[counter]);
		counter++;
	}
	free (splited);
}

char	*split_n_join(char *str, char **split, int spliter)
{
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	if (!split)
		split = ft_split(str, spliter);
	if (split[1] != NULL)
	{
		while(split[++i])
			res = ft_strjoin_mod(res, split[i], 0);
	}
	else 
		res = ft_strdup(split[0]);
	freedom(split, str, NULL, NULL);
	return (res);
}
