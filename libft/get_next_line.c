/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:29:04 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/06 14:41:25 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_mod(char *str1, char *str2, int pos);
static char	*get_it_all(int fd, char *text);
static int	checker(char *str);
static char	*not_keep(char *text);

char	*get_next_line(int fd)
{
	static char	*text;
	char		*res;

	if (BUFFER_SIZE <= 0 || fd > 1024 || fd < 0)
		return (NULL);
	if (checker(text) == 0)
		text = get_it_all(fd, text);
	if (!text || !*text)
		return (NULL);
	res = not_keep(text);
	if (checker(text) != 0)
		text = ft_strjoin_mod(text, NULL, checker(res));
	else
	{
		free (text);
		text = NULL;
	}
	return (res);
}

static char	*not_keep(char *text)
{
	int		len;
	int		i;
	char	*res;

	if (checker(text) != 0)
		len = checker(text);
	else
		len = ft_strlen(text);
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (++i < len)
		res[i] = text[i];
	return (res);
}

static char	*get_it_all(int fd, char *text)
{
	char	*buffer;
	int		is;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	is = 1;
	while (is > 0)
	{
		if (checker(buffer) != 0)
			break ;
		is = read(fd, buffer, BUFFER_SIZE);
		if (is < 0)
		{
			if (text)
				free (text);
			text = NULL;
			break ;
		}
		buffer[is] = '\0';
		text = ft_strjoin_mod(text, buffer, 0);
	}
	free (buffer);
	return (text);
}

static int	checker(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*ft_strjoin_mod(char *str1, char *str2, int pos)
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
