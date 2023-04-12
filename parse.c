/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/12 21:06:08 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] != '\n' && line[f] != 32)
			return (1);
	}
	return (0);
}

char	*this_folder_is(int	check)
{
	char *buf;

	buf = NULL;
    if (getcwd(buf, sizeof(buf)) == NULL)
	{
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
	if (check == 0)
    	printf("%s\n", buf);
	return (buf);
}

char	*prev_folder(char *path)
{
	int	f;

	f = ft_strlen(path);
	while (path[--f] != '/');
	path[f + 1] = 0;
	return (path);
}

void	cd_command(char *str)
{
	char **splited;

	splited = ft_split(str, 32);
	if (splited[2])
		error_func2("cd: too many arguments");
	if (ft_strncmp(splited[1], "..", 2) == 0)
		path = prev_folder(this_folder_is(1));
	if (chdir(path) == -1)
	{
        perror("chdir");
        exit(EXIT_FAILURE);
    }
    printf("Current working directory changed.\n");
}

void	error_func2(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(-1);
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
