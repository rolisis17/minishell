/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/12 17:30:50 by dcella-d         ###   ########.fr       */
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
	char	ass[256];
	int				f;

	dir = opendir(ft_strjoin_mod(this_folder_is(1), "/", 0));
	// ft_putendl_fd(this_folder_is(1), 2);
	folder = NULL;
	if (dir)
	{
		f = strintchr(str, '*');
		// entry = readdir(dir);
		while ((entry = readdir(dir)) != NULL)
		{
			ft_strlcpy(ass, entry->d_name, ft_strlen(entry->d_name) + 1);
			if (ft_strncmp(ass, str, f) == 0)
			{
				if (!folder)
					folder = ft_split(ass, 1);
				else
					folder = add_split(folder, ass, 0);
				// ft_putendl_fd(folder[0], 2);
			}
			// ft_putendl_fd(ass, 2);
			
			// free (ass);
			// entry = readdir(dir);
		}
        closedir(dir);
		// f = -1;
		return (folder);
    }
	else
        return (NULL);
}

char	**wild_cards(char **cmd)
{
	char	**folder;
	char	**res;
	int		f;
	int i = -1;

	f = 0;
	folder = NULL;
	res = NULL;
	while (cmd[++f])
	{
		if (strintchr(cmd[f], '*'))
		{
			ft_putendl_fd("MAIAS", 2);
			folder = read_folder(cmd[f]);
			if (!res)
				res = merge_split(cmd, folder, 0, f);
			else
				res = merge_split(res, folder, 0, word_count(res));
		}
		i = -1;
	}
	// while (res[++i])
	if (!res)
		return (cmd);
	return (res);
}
