/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/07 19:31:06 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (g_glob.environ[++i])
	{
		printf("%s\n", g_glob.environ[i]);
	}
	cmd = freedom("s", cmd);
	exit (0);
}

void	set_path_env(char **envp)
{
	char	*path;

	g_glob.environ = envp;
	if (!(g_glob.kurva))
	{
		keep_history(NULL, 1);
		path = this_folder_is(1);
		path = ft_strjoin(this_folder_is(1), "/minishell");
		g_glob.kurva = path;
	}
}
