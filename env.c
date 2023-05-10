/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/10 20:20:51 by dcella-d         ###   ########.fr       */
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
	g_glob.environ = envp;
	printf("%s\n", this_folder_is(1));
	g_glob.exit_status = 0;
	if (getenv("_"))
	{
		keep_history(NULL, 1);
		g_glob.kurva = getenv("_");
	}
}
