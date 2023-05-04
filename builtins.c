/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/04 13:59:08 by mstiedl          ###   ########.fr       */
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
	{
    	printf("%s\n", buf);
		exit(0);
	}
	else
		res = ft_strdup(buf);
	return (res);
}

char	*prev_folder(char *path, int safe)
{
	int	f;
	char *new;

	f = ft_strlen(path);
	while ((path[--f - 1] != '/') && (ft_strncmp("/", path, 1) == 0));
	new = ft_calloc(f + 1, sizeof(char));
	ft_strlcpy(new, path, f + 1);
	if (safe)
		free (path);
	return (new);
}

void	cd_command(char **splited)
{
	char	*prev;
    
	prev = NULL;
	if (splited[1] && splited[2])
		error("cd: too many arguments", 0);
	prev = relative_cd(splited[1]);
	set_oldpwd();
	ft_strlcpy(getenv("PWD"), prev, ft_strlen(prev));
    if (chdir(prev) == -1)
	{
        perror("chdir");
        freedom(NULL, prev, NULL, NULL);
        return;
    }
	freedom(NULL, prev, NULL, NULL);
	set_pwd();
	return;
}

void	set_oldpwd(void)
{
	char	*oldpwd;
	
	oldpwd = this_folder_is(1);
	ft_strlcpy(getenv("OLDPWD"), oldpwd, ft_strlen(oldpwd) + 1);
	free (oldpwd);
}

void	set_pwd(void)
{
	char	*newpwd;
	
	newpwd = this_folder_is(1);
	ft_strlcpy(getenv("PWD"), newpwd, ft_strlen(newpwd) + 1);
	free (newpwd);
}

char	*relative_cd(char *str)
{
	if (!str)
	{
		if (getenv("HOME"))
			return (ft_strdup(getenv("HOME")));
		else
			return (this_folder_is(1));
	}
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
		while ((to_join[--f - 1] != '/') && (ft_strncmp("/", to_join, 1) == 0));
	}
	res = ft_substr(to_join, 0, f);
	free (to_join);
	res = ft_strjoin_mod(res, str, 0);
	return (res);
}

void    env_cmd(char **cmd)
{
    int         i;

    i = -1;
    while (environ[++i])
	{
        printf("%s\n", environ[i]);
	}
	cmd = freedom(cmd, NULL, NULL, NULL);
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
	cmd = freedom(cmd, NULL, NULL, NULL);
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

void	export_cmd(char **cmd)
{
	char	**args;
	char	**cmp;
	
	// char	**env_new;
	// args = ft_split("env -i", 32);
	// env_new = add_split(environ, cmd[1], 1);
	// environ = env_new;
	// free (data->minienv);
	// data->minienv = env_new;
	// printf("%s\n", getenv("cara"));
	// while (environ[++f])
	// args = add_split(args, "./minishell", 0);
    // execve(find_path("env"), args, NULL); // check if need to free data.
	if(getenv("CURVA"))
	{
		cmp = ft_split(" ", 02);
		keep_history(NULL, 1);
		args = copy_split(environ, 1);
		args = add_split(args, cmd[1], 0);
    	if (execve(getenv("CURVA"), cmp, args) == -1)
		{
			perror("execve");
			freedom(cmp, NULL, NULL);
			freedom(args, NULL, NULL);
		}
	}
}

void	set_path_env(void)
{
	char	**args;
	char	**cmp;
	char	*path;
	char	*comm;

	if (!(getenv("CURVA")))
	{
		keep_history(NULL, 1);
		path = this_folder_is(1);
		path = ft_strjoin(this_folder_is(1), "/minishell");
		comm = ft_strjoin("CURVA=", path);
		cmp = ft_split(" ", 02);
		args = add_split(environ, comm, 1);
		if (execve(path, cmp, args) == -1)
		{
			perror("execve");
			freedom(cmp, path, comm);
			freedom(args, NULL, NULL);
		}
	}
}

void	unset_cmd(char **cmd)
{
	char	**args;
	char	**cmp;
	int		f;
	
	// char	**env_new;
	f = -1;
	// args = ft_split("env -i", 32);
	// env_new = add_split(environ, cmd[1], 1);
	// environ = env_new;
	// free (data->minienv);
	// data->minienv = env_new;
	// printf("%s\n", getenv("cara"));
	// args = add_split(args, "./minishell", 0);
    // execve(find_path("env"), args, NULL); // check if need to free data.
	if(getenv("CURVA"))
	{
		keep_history(NULL, 1);
		cmp = ft_split(" ", 32);
		args = remove_split(environ, cmd[1], 1);
    	if (execve(getenv("CURVA"), cmp, args) == -1)
		{
			perror("execve");
			freedom(cmp, NULL, NULL);
			freedom(args, NULL, NULL);
		}
	}
}

char	**new_env(char **envp)
{
	char	**new;
	int		counter;
	int		f;

	f = -1;
	counter = -1;
	while (envp[++counter]);
	new = ft_calloc(counter + 1, sizeof(char **));
	while (envp[++f] && new[f])
		new[f] = ft_strdup(envp[1]);
	return (NULL);
}

// char	*dollar_sign(char *str)
// {
	
// }

// |, >, <, <<, >> (TOP)
// ""
// >>>>, >>|, <<|> (Bater na mae)
// echo "ola, mundo" >t.txt >>l.txt >>>|> h.txt | wc | ls -la
// new + ft_strlen(2 x Recebida);
// echo2"ola, mundo"23>2t.txt2>>2l.txt23>>23>23|23>2h.txt232wc232ls2-la
// echo "ola, mundo"
// > t.txt
// >> l.txt
// >> 
// > 
// |
// > h.txt
// wc
// ls, la
// echo "ola, Mundo"