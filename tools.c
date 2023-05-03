/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:10:54 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/03 09:48:19 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **freedom(char **ted, void *ze, void *dom, void *style)
{
	if (ted)
    	freesplit(ted);
    if (ze)
        free(ze);
    if (dom)
	{
    	free(dom);
	}
	if (style)
		free(style);
	return(NULL);
}

int	get_cmd(char *str, int arg)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (arg < 1 && (str[i] == 34 || str[i] == 39))
			return (i);
		if (str[i] == '<' || str[i] == '>')
			return (i);
		if (str[i] == '|' || str[i] == 32)
			return (i);
		i++;
		if (arg < 0 && str[i] == '$')
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

char	*ft_strjoin_mod(char *str1, char *str2, int pos)
{
	size_t	len;
	char	*res;
	int		i;

	i = 0;
	len = (ft_strlen(str1 + pos) + ft_strlen(str2));
	if (len == 0)
	{
		free (str1);
		return (NULL);
	}
	res = ft_calloc(sizeof(char), (len + 1));
	if (!res)
		return (NULL);
	if (str1)
	{
		while (str1[pos])
			res[i++] = str1[pos++];
		free (str1);
	}
	pos = -1;
	if (str2)
		while (str2[++pos])
			res[i + pos] = str2[pos];
	return (res);
}

char *char_join(char *str, int c)
{
	char	*res;
	size_t	len;
	int		i;
	
	i = 0;
	len = ft_strlen(str);
	res = ft_calloc(sizeof(char), (len + 2));
	if (!res)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			res[i] = str[i];
			i++;			
		}
		free (str);
	}
	res[i] = c;
	return(res);
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