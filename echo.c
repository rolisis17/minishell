/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/09 17:32:21 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char **cmd)
{
	int	f;
	int	checker;

	f = 0;
	checker = 0;
	while (cmd[++f])
	{
		if (ft_strncmp(cmd[f], "-n", 3) == 0)
			checker = 1;
		else
			break ;
	}
	while (cmd[f])
	{
		printf("%s", cmd[f]);
		if (cmd[f + 1])
			printf(" ");
		f++;
	}
	if (!checker)
		printf("\n");
	exit (0);
}

int	strintchr(char	*str, int c)
{
	int	f;

	f = -1;
	while (str[++f] != c);
	return (f);
}
