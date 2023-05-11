/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/11 17:06:48 by marvin           ###   ########.fr       */
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

	f = -1;
	while (str[++f] != c);
	return (f);
}

char	**read_folder(char *str)
{
	char			**folder;
	DIR				*dir;
	struct dirent	*entry;
	int				f;

	dir = opendir(".");
	folder = NULL;
	if (dir)
	{
		f = strintchr(str, '*');
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (ft_strncmp(entry->d_name, str, f) == 0)
			folder = ft_addsplit(folder, entry->d_name, 0);
		}
        closedir(dir);
		return (folder);
    }
	else
        return (NULL);
}
