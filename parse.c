/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/17 10:05:44 by mstiedl          ###   ########.fr       */
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

// char	*single_q(char *input, char *current, int fd)
// {
// 	char	*res;
// 	char	*end;
// 	int		len;
	
// 	if (current == NULL)
// 	{
// 		if (input[0] != 39)
// 		{
// 			end = ft_strchr(input, 32);
// 			len = end - input;
// 			res = ft_strlcpy(res, input, len);
// 			if (find_path(res) == NULL)
// 			{
// 				error(res, 1);
// 				return (NULL);
// 			}
// 			return (res);
// 		}
// 		end = ft_strchr(input[1], 39);	
// 	}
// 	else
// 		return ()
// }// okay this shit is fucked!!! echo still print shit like fuck"some"yes... 
//the whole thing so theres only a need ot parse that shit if theres a $ in the middle..