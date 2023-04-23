/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/23 20:15:36 by dcella-d         ###   ########.fr       */
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
	char *new;

	f = ft_strlen(path);
	while (path[--f] != '/');
	path[f + 1] = 0;
	new = ft_strjoin("/", path, 0); //need to free path
	free (path);
	return (new);
}

void	cd_command(char **splited)
{
	char	*prev;

	prev = NULL;
	if (splited[1] && splited[2])
		error("cd: too many arguments", 0);
	prev = change_dot(splited[1]);
	printf("%s\n", prev);
	printf("%s\n", getenv("PWD"));
	if (chdir(prev) == -1)
        perror("chdir");
	freesplit(splited);
	// if (prev)
	// 	free(prev);
	exit (0);
    // printf("Current working directory changed.\n");
}

char	*change_dot(char *str)
{
	char *res;

	res = NULL;
	if (ft_strncmp(".", str, 2) == 0)
		res = this_folder_is(1);
	else if (ft_strncmp("./", str, 3) == 0)
		res = ft_strjoin(this_folder_is(1), str + 1, -2);
	else if (ft_strncmp("..", str, 3) == 0)
		res = prev_folder(this_folder_is(1));
	else if (!str)
		res = ft_strdup(getenv("HOME"));
	return (res);
}

void    env_cmd(char **cmd)
{
    extern char **environ;
    int         i;

    i = -1;
    while (environ[++i])
	{
        printf("%s\n", environ[i]);
	}
	cmd = freedom(cmd, NULL, NULL);
	exit (0);
} // env command!

void	ft_exit(char **cmd)
{
	ft_putendl_fd("exit does not take options in this minishell", 2);
	cmd = freedom(cmd, NULL, NULL);
	exit(0);
}

int	exit_error(char *str, int check)
{
	static int	exit;

	if (check)
		return (exit);
	if (ft_strncmp("cd", str, 2) == 0)
		exit = 126;
	return (0);
}