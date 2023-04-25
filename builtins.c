/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/25 20:02:15 by dcella-d         ###   ########.fr       */
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
	// char *new;

	f = ft_strlen(path);
	while ((path[--f] != '/') && (ft_strncmp("/", path, 1) == 0));
	path[f + 1] = 0;
	// new = ft_strjoin("/", path, 0); //need to free path
	// free (path);
	return (path);
}

void	cd_command(char **splited)
{
	char	*prev;
    // char cwd[1024];

	if (splited[1] && splited[2])
		error("cd: too many arguments", 0);
	prev = relative_cd(&splited[1]);
    if (chdir(prev) == -1)
	{
        perror("chdir");
        fprintf(stderr, "Could not change directory to '%s'\n", prev);
        free(prev);
        return;
    }
	return;
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     printf("Current working directory: %s\n", cwd);
    // } else {
    //     perror("getcwd() error");
    // }
    free(prev);
}

char	*relative_cd(char **str)
{
	if (!(*str))
		return (getenv("HOME"));
	else if (ft_strncmp(".", (*str), 2) == 0)
		return (this_folder_is(1));
	else if (ft_strncmp("./", (*str), 3) == 0)
		return (ft_strjoin(this_folder_is(1), (*str) + 1, -2));
	else if (ft_strncmp("..", (*str), 3) == 0)
		return (prev_folder(this_folder_is(1)));
	else if (ft_strncmp("../", (*str), 3) == 0)
		return (relative_cd2(*str));
	return (*str);
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
		while ((to_join[--f - 1] != '/') && (ft_strncmp("/", to_join, 1) == 0));
		printf("%zu\n", ft_strlen(str));
	}
	res = ft_calloc(f + 2, sizeof(char));
	ft_strlcpy(res, to_join, f + 1);
	free (to_join);
	res = ft_strjoin(res, str, -2);
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

void	echo_cmd(char **cmd)
{
	int	f;
	int	checker;

	f = 0;
	checker = 0;
	if (ft_strncmp(cmd[1], "-n", 3) == 0)
	{
		f++;
		checker++;
	}
	while (cmd[++f])
		printf("%s", cmd[f]);
	if (checker)
		printf("\n");
}

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