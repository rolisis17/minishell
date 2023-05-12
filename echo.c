/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/12 19:48:42 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char **cmd)
{
	int	f;
	int	checker;

	f = 0;
	checker = 0;
	while (cmd[++f])
	{
		if (ft_strncmp(cmd[f], "-n", 3) == 0)
			checker = 1;
		else
			break ;
	}
	while (cmd[f])
	{
		printf("%s", cmd[f]);
		if (cmd[f + 1])
			printf(" ");
		f++;
	}
	if (!checker)
		printf("\n");
	exit (0);
}

int	strintchr(char	*str, int c)
{
	int	f;

	f = 0;
	// ft_putendl_fd(str, 2);
	while (str[f] && str[f] != c)
		f++;
	if (!str[f])
		f = 0;
	// ft_putnbr_fd(f, 2);
	return (f);
}

char	**read_folder(char *str)
{
	char			**folder;
	DIR				*dir;
	struct dirent	*entry;
	// char	ass[256];
	int				f;

	dir = opendir(ft_strjoin_mod(this_folder_is(1), "/", 0));
	folder = NULL;
	if (dir)
	{
		f = strintchr(str, '*');
		// entry = readdir(dir);
		while ((entry = readdir(dir)) != NULL)
		{
			// ft_strlcpy(ass, entry->d_name, ft_strlen(entry->d_name) + 1);
			if (ft_strncmp(entry->d_name, str, f) == 0 && back_check(entry->d_name, str) == 0)
			{
				if (!folder)
					folder = ft_split(entry->d_name, 1);
				else
					folder = add_split(folder, entry->d_name, 0);
			}
			// entry = readdir(dir);
		}
        closedir(dir);
		return (folder);
    }
	else
        return (NULL);
}

char	**wild_cards(char **cmd)
{
	char	**folder;
	// char	**res;
	int		f;

	f = -1;
	// res = NULL;
	while (cmd[++f])
	{
		if (ft_strchr(cmd[f], '*') != NULL)
		{
			folder = read_folder(cmd[f]);
			if (folder)
			{
				// if (!res)
				cmd = merge_split(cmd, folder, 0, f);
				// else
				// 	cmd = merge_split(res, folder, 0, word_count(res));
			}
		}
	}
	// if (!res)
	return (cmd);
	// return (res);
}

int	back_check(char *str, char *check)
{
	int	i;
	int	f;

	i = ft_strlen(check);
	f = ft_strlen(str);
	while (i > 0)
	{
		if (check[i] == '*')
			break ;
		if (check[i] != str[f])
			return (i);
		i--;
		f--;
	}
	return (0);
}
