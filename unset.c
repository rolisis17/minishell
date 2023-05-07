/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/07 19:31:47 by dcella-d         ###   ########.fr       */
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
	args = copy_split(g_glob.environ, 1);
	while (g_glob.kurva && cmd[++f] && getenv(cmd[f]))
	{
		keep_history(NULL, 1);
		cmp = ft_split(" ", 32);
		com = ft_strjoin(cmd[f], "=");
		args = remove_split(args, com, 1);
		free (com);
		com = NULL;
	}
	if (execve(g_glob.kurva, cmp, args) == -1)
	{
		perror("execve");
		freedom("ssa", cmp, args, com);
	}
}
