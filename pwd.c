/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/17 17:24:07 by dcella-d         ###   ########.fr       */
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
		return (NULL);
	}
	else
		res = ft_strdup(buf);
	return (res);
}

char	*set_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = this_folder_is(1);
	if (getenv("OLDPWD"))
	{
		ft_strlcpy(getenv("OLDPWD"), oldpwd, ft_strlen(oldpwd) + 1);
		free (oldpwd);
		oldpwd = NULL;
	}
	return (oldpwd);
}

char	*set_pwd(void)
{
	char	*newpwd;

	newpwd = this_folder_is(1);
	if (getenv("PWD"))
	{
		ft_strlcpy(getenv("PWD"), newpwd, ft_strlen(newpwd) + 1);
		free (newpwd);
		newpwd = NULL;
	}
	return (newpwd);
}

void	set_pwd_noenv(char *newpwd, char *oldpwd)
{
	char	*export;
	char	**cmd;

	export = ft_strdup("export");
	if (oldpwd)
	{
		oldpwd = ft_strjoin(" OLDPWD=", oldpwd);
		export = ft_strjoin_mod(export, oldpwd, 0);
	}
	if (newpwd)
	{
		newpwd = ft_strjoin(" PWD=", newpwd);
		export = ft_strjoin_mod(export, newpwd, 0);
	}
	cmd = ft_split(export, 32);
	freedom("aaa", oldpwd, newpwd, export);
	if (oldpwd || newpwd)
		export_cmd(cmd);
	else
		cmd = freedom("s", cmd);
}
