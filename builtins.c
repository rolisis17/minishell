/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/21 10:02:43 by mstiedl          ###   ########.fr       */
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
	char **new;

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
	if (splited[2])
		error("cd: too many arguments", 0);
	prev = change_dot(splited[1]);
	if (chdir(prev) == -1)
        perror("chdir");
	freesplit(splited);
	if (prev)
		free(prev);
    // printf("Current working directory changed.\n");
}

char	*change_dot(char *str)
{
	if (str[0] == '.' && !(str[1]))
		return (this_folder_is(1));
	else if (str[0] == '.' && str[1] == '/')
		return (ft_strjoin(this_folder_is(1), str + 1));
	else if (ft_strncmp("..\0", str, 3) == 0)
		return (prev_folder(this_folder_is(1)));
	else if (ft_strncmp("/\0", str, 2) == 0)
		return (getenv("PWD"));
	else
		return (str);
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
}