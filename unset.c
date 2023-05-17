/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:53:40 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char **cmd, int re)
{
	char	**args;
	char	**cmp;

	re = 0;
	args = new_unset_env(cmd);
	cmp = ft_split(" ", 32);
	if (cmp && g_glob.kurva)
		keep_history(NULL, 1);
	if (!g_glob.kurva || execve(g_glob.kurva, cmp, args) == -1)
	{
		perror("execve");
		freedom("ss", cmp, args);
	}
}

char	**new_unset_env(char **cmd)
{
	char	**args;
	char	*com;
	int		f = 0;

	com = NULL;
	args = copy_split(g_glob.environ, 1);
	while (cmd[++f])
	{
		if (getenv(cmd[f]) && (export_check_equal(cmd[f]) == -1) && unset_check_args(cmd[f], cmd + f) \
		&& (ft_strncmp(cmd[f], "_", 2) != 0))
		{
			com = ft_strjoin(cmd[f], "=");
			args = remove_split(args, com, 1);
			com = freedom("a", com);
		}
		else if (export_check_equal(cmd[f]) != -1)
			export_print_error(cmd[f]);
	}
	return (args);
}

int	unset_check_args(char *to_compare, char **cmd)
{
	int	u;

	u = 0;
	while (cmd[++u])
	{
		if (ft_strncmp(to_compare, cmd[u], ft_strlen(cmd[u])) == 0)
			return (0);
	}
	return (1);
}

// int	check_under_env(char *cmd)
// {
// 	int	f;

// 	f = -1;
// 	while (cmd[++f])
// 	{
// 		if (ft_strncmp(cmd,))
// 	}
// }