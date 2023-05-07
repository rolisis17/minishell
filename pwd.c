/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/07 19:31:42 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*this_folder_is(int check)
{
	char	buf[1024];
	char	*res;

	res = NULL;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		if (getenv("PWD"))
			ft_strlcpy(buf, getenv("PWD"), 1024);
		else
		{
			perror("getcwd");
			exit(EXIT_FAILURE);
		}
	}
	if (check == 0)
	{
		printf("%s\n", buf);
		exit(0);
	}
	else
		res = ft_strdup(buf);
	return (res);
}

void	set_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = this_folder_is(1);
	if (getenv("OLDPWD"))
		ft_strlcpy(getenv("OLDPWD"), oldpwd, ft_strlen(oldpwd) + 1);
	free (oldpwd);
}

void	set_pwd(void)
{
	char	*newpwd;

	newpwd = this_folder_is(1);
	if (getenv("PWD"))
		ft_strlcpy(getenv("PWD"), newpwd, ft_strlen(newpwd) + 1);
	free (newpwd);
}
