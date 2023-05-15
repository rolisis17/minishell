/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/15 17:02:46 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char **cmd, int f)
{
	char	**args;
	char	**cmp;
	char	*com;

	args = copy_split(g_glob.environ, 1);
	com = NULL;
	while (cmd[++f])
	{
		if (export_check_equal(cmd[f]) == -1)
		{
			keep_history(NULL, 1);
			cmp = ft_split(" ", 32);
			com = ft_strjoin(cmd[f], "=");
			args = remove_split(args, com, 1);
		}
		else
			export_print_error(cmd[f]);
	}
	if (com && (!g_glob.kurva || execve(g_glob.kurva, cmp, args) == -1))
	{
		perror("execve");
		freedom("ssa", cmp, args, com);
	}
	com = freedom("a", com);
}
