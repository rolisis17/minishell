/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:10:54 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/10 12:19:05 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	error(char *msg, int arg)
{
	g_glob.exit_status = arg;
	if (arg == 1)
	{
		perror(msg);
		return ;
	}
	if (arg == 0)
	{
		ft_putendl_fd(msg, 2);
		exit(arg);
	}
	else if (arg == 127)
		ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(msg, 2);
}

int	check_status(char *msg)
{
	if (ft_strncmp(msg, "execve", 6) == 0 || ft_strncmp(msg, "getcwd", 6) == 0 \
	|| ft_strncmp(msg, "chdir", 6) == 0)
		return (127);
	return (0);
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

char	*char_join(char *str, int c)
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
	return (res);
}
