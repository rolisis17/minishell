/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/14 14:03:09 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(char **cmd)
{
	char	**args;
	char	**cmp;
	int		f;

	f = 0;	
	args = copy_split(g_glob.environ, 1);
	cmp = NULL;
	while (cmd[++f])
	{
		if (export_check_equal(cmd[f]) == 1 && !(export_varmod(cmd[f])) \
		&& export_check_args(f, cmd))
		{
			cmp = ft_split(" ", 02);
			args = add_split(args, cmd[f], 0);
		}
		if (!export_check_equal(cmd[f]))
			export_print_error(cmd[f]);
	}
	if (cmp)
	{
		keep_history(NULL, 1);
		if (execve(g_glob.kurva, cmp, args) == -1 || !g_glob.kurva)
		{
			perror("execve");
			cmd = freedom("ss", cmd, args);
		}
	}
	if (!cmd[1])
		export_get_seclow(g_glob.environ, \
		export_get_lower(g_glob.environ, NULL));
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
