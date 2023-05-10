/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/10 20:37:46 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char **cmd)
{
	char	**args;
	char	**cmp;
	char	*com;
	int		f;

	f = 0;
	// if (g_glob.environ)
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
	if (com)
		free (com);
	com = NULL;
}
