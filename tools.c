/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:10:54 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/21 16:05:57 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **freedom(char **ted, void *ze, void *dom)
{
	if (ted)
    	freesplit(ted);
    if (ze)
        free(ze);
    if (dom)
        free(dom);
    return (NULL);
}

int	get_cmd(char *str, int arg)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (arg == 0 && (str[i] == 34 || str[i] == 39))
			return (i);
		if (str[i] == '<' || str[i] == '>')
			return (i);
		if (str[i] == '|' || str[i] == 32)
			return (i);
	}
	return (i);
}

char	*find_quote(char *str, int len)
{
	int		i;
	
	i = 0;
	while (i != len)
	{
		if (str[i] == 34)
			return (&str[i]);
		if (str[i] == 39)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void	error(char *msg, int arg)
{
	if (arg == 0)
	{
		ft_putendl_fd(msg, 2);
		exit(-1);
	}
	else if (arg == 1)
		ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(msg, 2);
}

// int	word_count(char const *str, char c)
// {
// 	int	words;
// 	int	len;

// 	words = 0;
// 	while (*str != '\0')
// 	{
// 		while (*str == c && *str != '\0')
// 			str++;
// 		if (*str != '\0')
// 			words++;
// 		len = 0;
// 		while (str[len] != c && str[len] != '\0')
// 			len++;
// 		str += len;
// 	}
// 	return (words);
// }