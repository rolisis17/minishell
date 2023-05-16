/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/16 13:33:41 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_shell *data)
{
	int	i;

	i = -1;
	while (g_glob.environ[++i])
	{
		printf("%s\n", g_glob.environ[i]);
	}
	keep_history(NULL, 2);
	data = freedom("da", data, data);
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
}
