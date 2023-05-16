/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/16 13:52:05 by dcella-d         ###   ########.fr       */
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
	g_glob.exit_status = 0;
	if (getenv("_"))
	{
		keep_history(NULL, 1);
		g_glob.kurva = getenv("_");
	}
	if (back_check(g_glob.kurva, "minishell") == 0)
		return ;
	else
	{
		g_glob.kurva = ft_strjoin(this_folder_is(1), "/minishell");;
		ft_strlcpy(getenv("_"), g_glob.kurva, ft_strlen(g_glob.kurva) + 1);
		free (g_glob.kurva);
		g_glob.kurva = getenv("_");
	}
	if (access(g_glob.kurva, F_OK) == -1)
		g_glob.kurva = NULL;
	printf("%s\n", g_glob.kurva);
}

