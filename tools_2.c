/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:18:29 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/16 10:09:03 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_search(int c)
{
	if (c == '|' || c == '<' || c == '>' || c == 32 || c == '\0')
		return (1);
	else
		return (0);
}

int	syntax_check(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == '|')
		i++;
	while (str[i + j] == 32)
		j++;
	if (str[i + j] == '|')
		return (i + j);
	else
		return (i);
}

int	word_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
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
		while (split[++i])
			res = ft_strjoin_mod(res, split[i], 0);
	}
	else
		res = ft_strdup(split[0]);
	freedom("sa", split, str);
	return (res);
}

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] == '|')
		{
			error("Syntax Error", 2);
			break ;
		}
		if (line[f] != '\n' && line[f] != 32)
			return (1);
	}
	freedom("a", line);
	return (0);
}
