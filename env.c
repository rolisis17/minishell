/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/18 14:10:52 by mstiedl          ###   ########.fr       */
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

void	set_path_env(char **envp, char *av1)
{
	char	*str;

	g_glob.environ = envp;
	g_glob.exit_status = 0;
	if (getenv("_"))
	{
		keep_history(NULL, 1);
		g_glob.kurva = getenv("_");
	}
	if (g_glob.kurva && back_check(g_glob.kurva, "minishell") == 0)
		return ;
	else
	{
		str = this_folder_is(1);
		g_glob.kurva = ft_strjoin(str, av1 + 1);
		free (str);
		if (getenv("_"))
			ft_strlcpy(getenv("_"), g_glob.kurva, ft_strlen(g_glob.kurva) + 1);
		else
			set_under_noenv();
		free (g_glob.kurva);
		g_glob.kurva = getenv("_");
	}
	if (access(g_glob.kurva, F_OK) == -1)
		g_glob.kurva = NULL;
}

void	set_under_noenv()
{
	char	**cmd;
	char	*args[2];
	
	args[0] = ft_strjoin("_=", g_glob.kurva);
	args[1] = NULL;
	cmd = ft_split(" ", 32);
	if (execve(g_glob.kurva, cmd, args) == -1)
	{
		perror("execve");
		cmd = freedom("sss", cmd, args);
	}
}