/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/20 14:16:51 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*this_folder_is(int	check)
{
	char buf[1024];
	char *res;

	res = NULL;
    if (getcwd(buf, sizeof(buf)) == NULL)
	{
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
	if (check == 0)
    	printf("%s\n", buf);
	else
		res = ft_strdup(buf);
	return (res);
}

char	*prev_folder(char *path)
{
	int	f;

	f = ft_strlen(path);
	while (path[--f] != '/');
	path[f + 1] = 0;
	ft_strjoin("/", path, 0); //need to free path
	return (ft_strjoin("/", path, 0));
}

void	cd_command(char **splited)
{
	char	*prev;

	prev = NULL;
	if (splited[2])
		error("cd: too many arguments", 0);
	if (ft_strncmp(splited[1], "..", 2) == 0)
		prev = prev_folder(this_folder_is(1));
	else if (splited[1][0] == '/')
		prev = ft_strjoin("/", splited[1], 0);
	else if (!(prev) && splited[1][0] == '.')
		splited[1]++;
	if (chdir(prev) == -1)
        perror("chdir");
	freesplit(splited);
	if (prev)
		free(prev);
    // printf("Current working directory changed.\n");
}

void    env_cmd(void)
{
    extern char **environ;
    int         i;

    i = -1;
    while (environ[++i])
        printf("%s\n", environ[i]);
} // env command!
