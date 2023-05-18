/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/18 13:33:35 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(char **cmd)
{
	char	**args;
	char	**cmp;

	if (!cmd[1])
		export_get_seclow(g_glob.environ, \
		export_get_lower(g_glob.environ, NULL));
	else
	{
		cmp = ft_split(" ", 32);
		args = new_export_env(cmd);
		keep_history(NULL, 1);
		if (!g_glob.kurva || execve(g_glob.kurva, cmp, args) == -1)
		{
			perror("execve");
			cmd = freedom("sss", cmd, args, cmp);
		}
	}
}

char	**new_export_env(char **cmd)
{
	char	**args;
	int		f;

	f = 0;
	args = copy_split(g_glob.environ, 1);
	while (cmd[++f])
	{
		if (export_check_equal(cmd[f]) == 1 && export_check_args(cmd[f], \
		cmd + f) && !(export_varmod(cmd[f])))
			args = add_split(args, cmd[f]);
		else if (export_varmod(cmd[f]))
			args = modify_split(args, cmd[f], 0, '=');
		if (!export_check_equal(cmd[f]))
			export_print_error(cmd[f]);
	}
	return (args);
}

char	*export_get_lower(char **env, char *to_compare)
{
	int	f;

	f = -1;
	while (env[++f])
	{
		if (to_compare && ft_strncmp(env[f], to_compare, \
		ft_strlen(to_compare)) < 0)
			to_compare = env[f];
		if (!to_compare)
			to_compare = env[f];
	}
	very_trash(to_compare, '=', 34);
	return (to_compare);
}

char	*export_get_seclow(char **env, char *to_compare)
{
	char	*low;
	int		f;

	f = -1;
	while (env[++f] && ft_strncmp(env[f], to_compare, \
	ft_strlen(to_compare)) < 0)
		;
	low = export_get_big(g_glob.environ, to_compare);
	f = -1;
	while (env[++f] && to_compare)
	{
		if (ft_strncmp(env[f], to_compare, ft_strlen(to_compare)) > 0 && \
		ft_strncmp(env[f], low, ft_strlen(low)) < 0)
			low = env[f];
	}
	very_trash(low, '=', 34);
	if (low != export_get_big(g_glob.environ, to_compare))
		export_get_seclow(g_glob.environ, low);
	return (low);
}

char	*export_get_big(char **env, char *to_compare)
{
	int	f;

	f = -1;
	while (env[++f])
	{
		if (to_compare && ft_strncmp(env[f], to_compare, \
		ft_strlen(to_compare)) > 0)
			to_compare = env[f];
		if (!to_compare)
			to_compare = env[f];
	}
	return (to_compare);
}
