/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/10 20:44:24 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_cd(char *str)
{
	if (!str || ft_strncmp("~", str, 2) == 0)
	{
		if (getenv("HOME"))
			return (ft_strdup(getenv("HOME")));
		else
			ft_putendl_fd("cd: HOME not set", 2);
		return (this_folder_is(1));
	}	
	else if (ft_strncmp("-", str, 2) == 0 && getenv("OLDPWD"))
		return (ft_strdup(getenv("OLDPWD")));
	else if (ft_strncmp(".", str, 2) == 0)
		return (this_folder_is(1));
	else if (ft_strncmp("./", str, 3) == 0)
		return (ft_strjoin_mod(this_folder_is(1), str + 1, 0));
	else if (ft_strncmp("..", str, 3) == 0)
		return (prev_folder(this_folder_is(1), 1));
	else if (ft_strncmp("../", str, 3) == 0)
		return (relative_cd2(str));
	return (ft_strdup(str));
}

char	*relative_cd2(char *str)
{
	char	*to_join;
	char	*res;
	int		f;

	to_join = this_folder_is(1);
	f = ft_strlen(to_join);
	while (str && ft_strncmp("../", str, 3) == 0)
	{
		str = str + 3;
		while ((to_join[--f - 1] != '/') && (ft_strncmp("/", to_join, 1) == 0))
			;
	}
	res = ft_substr(to_join, 0, f);
	free (to_join);
	res = ft_strjoin_mod(res, str, 0);
	return (res);
}

void	cd_command(char **splited)
{
	char	*prev;
	char	*oldpwd;

	oldpwd = set_oldpwd();
	prev = NULL;
	if (splited[1] && splited[2])
		error("cd: too many arguments", 0); // find error code to send as second param!
	prev = relative_cd(splited[1]);
	if (chdir(prev) == -1)
	{
		perror("cd");
		freedom("a", prev);
		g_glob.exit_status = 1;
		return ;
	}
	freedom("a", prev);
	set_pwd_noenv(set_pwd(), oldpwd);
	return ;
}

char	*prev_folder(char *path, int safe)
{
	int		f;
	char	*new;

	f = ft_strlen(path);
	while ((path[--f - 1] != '/') && (ft_strncmp("/", path, 1) == 0))
		;
	new = ft_calloc(f + 1, sizeof(char));
	ft_strlcpy(new, path, f + 1);
	if (safe)
		free (path);
	return (new);
}
