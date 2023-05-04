/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/04 20:57:51 by dcella-d         ###   ########.fr       */
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
	if (getenv("PWD"))
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
	while (cmd[++f])
	{
		if (ft_strncmp(cmd[f], "-n", 3) == 0)
			checker = 1;
		else
			break;
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

	if (cmd[1] && getenv("CURVA") && !(export_varmod(cmd[1])) && strintchr(cmd[1], '='))
	{
		cmp = ft_split(" ", 02);
		keep_history(NULL, 1);
		args = copy_split(environ, 1);
		args = add_split(args, cmd[1], 0);
    	if (execve(getenv("CURVA"), cmp, args) == -1)
		{
			perror("execve");
			freedom(cmp, NULL, NULL, NULL);
			freedom(args, NULL, NULL, NULL);
		}
	}
	else if (!cmd[1])
	{
		char c = 97;
		while (getenv(c))
			printf("%s\n", getenv(c));
	}
}

void	print_export(void)
{
	char	**env_sorted;
	char	*low;
	char	*seclow;
	char	*next;
	int	f;

	f = -1;
	while (environ[++f])
	{
		if (ft_strncmp(environ[f], environ[f + 1], ft_strlen(environ[f] + 1))) // if < 0 -> str1 is bigger else str2
		{
			if () // need to do this to get the 3 lowest str and print the last one and keep comparing with the rest;
		}
	}
}

int	export_varmod(char *cmd)
{
	char	*env_var;
	int		len;

	len = strintchr(cmd, '=');
	env_var = ft_substr(cmd, 0, len - 1);
	if (getenv(env_var) && len > 0)
		ft_strlcpy(getenv(env_var), cmd + len, ft_strlen(cmd + len) + 1);
	else
		len = 0;
	free (env_var);
	return (len);
}

int	strintchr(char	*str, int c)
{
	int	f;

	f = -1;
	while (str[++f] != c);
	return (f + 1);
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
			freedom(cmp, path, comm, NULL);
			freedom(args, NULL, NULL, NULL);
		}
	}
}

void	unset_cmd(char **cmd)
{
	char	**args;
	char	**cmp;

	if(getenv("CURVA"))
	{
		keep_history(NULL, 1);
		cmp = ft_split(" ", 32);
		args = remove_split(environ, cmd[1], 1);
    	if (execve(getenv("CURVA"), cmp, args) == -1)
		{
			perror("execve");
			freedom(cmp, NULL, NULL, NULL);
			freedom(args, NULL, NULL, NULL);
		}
	}
}

// char	**new_env(char **envp)
// {
// 	char	**new;
// 	int		counter;
// 	int		f;

// 	f = -1;
// 	counter = -1;
// 	while (envp[++counter]);
// 	new = ft_calloc(counter + 1, sizeof(char **));
// 	while (envp[++f] && new[f])
// 		new[f] = ft_strdup(envp[1]);
// 	return (NULL);
// }

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