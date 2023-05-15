/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:08:04 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/15 17:11:06 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd)
{
	char	*the_path;
    char    *cmd_temp;
    char    **paths;
    int     i;

    i = -1;
	if (getenv("PATH"))
	{
		cmd_temp = ft_strjoin("/", cmd);
		paths = ft_split(getenv("PATH"), ':');
		while (paths[++i])
		{
			the_path = ft_strjoin(paths[i], cmd_temp);
			if (access(the_path, F_OK) == 0)
			{
				freedom("sa", paths, cmd_temp);
				return (the_path);
			}
			free (the_path);
		}
		freedom("sa", paths, cmd_temp);
	}
	return (NULL);
}

void	bad_cmd(char *path, char **cmd)
{
	ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(cmd[0], 2);
	cmd = freedom("sa", cmd, path);
	exit(127);
}

char	*env_shlvl(void)
{
	char	*shlvl;

	shlvl = NULL;
	if (getenv("SHLVL"))
		shlvl = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(getenv("SHLVL")) + 1));
	return (shlvl);
}

int	file_checker(char *path)
{
    struct stat	isreal;

	if (stat(path, &isreal) == 0)
	{
        if (S_ISDIR(isreal.st_mode))
		{
			ft_putstr_fd(path, 2);
			error(": Is a directory", 126);
			return (1);
		}
	}
	else
	{
		ft_putendl_fd("Error: No such file or directory", 2);
		g_glob.exit_status = 127;
		return (1);
	}
	return (0);
}
