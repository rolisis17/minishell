/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/13 14:43:40 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] != '\n' && line[f] != 32 && line[f] != '.')
			return (1);
	}
	return (0);
}

char	*to_trim_quotes(char *str, int quote)
{
	char	*trimmed;
	int		end;
	int		start;
	int		u;
	// 34 == "
	// 36 == $
	// 39 == '

	trimmed = NULL;
	start = searchforquotes(str, quote, 1);
	end = searchforquotes(str, quote, 2);
	u = -1;
	if (searchforquotes(str, quote, 0) > 1)
	{
		trimmed = ft_calloc(end - start + 1, sizeof(char));
		while (start < end)
		{
			trimmed[++u] = str[start];
			start++;
		}
	}
	return (trimmed);
}

int	searchforquotes(char *str, int quote, int start)
{
	int	f;
	int	counter;

	f = 0;
	counter = 0;
	while (str[f])
	{
		if (str[f] == quote)
			counter++;
		if ((start == 2 && counter == 2))
			return (f);
		f++;
		if (start == 1 && counter == 1)
			return (f);
	}
	// if (start == 2)
	// 	return (0);
	return (counter);
}

void	error_func2(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(-1);
}
