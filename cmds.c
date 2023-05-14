/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:09 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/14 17:30:42 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd)
{
	char	*the_path;
    char    *cmd_temp;
    char    **paths;
    int     i;

    i = -1;
	if (getenv("PATH"))
	{
		cmd_temp = ft_strjoin("/", cmd);
		paths = ft_split(getenv("PATH"), ':');
		while (paths[++i])
		{
			the_path = ft_strjoin(paths[i], cmd_temp);
			if (access(the_path, F_OK) == 0)
			{
				freedom("sa", paths, cmd_temp);
				return (the_path);
			}
			free (the_path);
		}
		freedom("sa", paths, cmd_temp);
	}
	return (NULL);
}

void	bad_cmd(char *path, char **cmd)
{
	ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(cmd[0], 2);
	cmd = freedom("sa", cmd, path);
	exit(127);
}

void	execute(char **cmd)
{
	char		*path;
	char		**new_env;

	new_env = NULL;
	if (cmd == NULL)
		exit(0);
	check_builtin(cmd);
	path = exable(cmd);
	if (!path)
		bad_cmd(path, cmd);
	new_env = modify_split(g_glob.environ, env_shlvl(), 1, '=');
	if (file_checker(path) == 1)
	{
		cmd = freedom("ssa", cmd, new_env, path);
		exit(g_glob.exit_status);
	}
	if (execve(path, cmd, new_env) == -1)
	{
		cmd = freedom("ssa", cmd, new_env, path);
		perror("Error");
		exit(126);
	}
}

int	file_checker(char *path)
{
    struct stat	isreal;

	if (stat(path, &isreal) == 0)
	{
        if (S_ISDIR(isreal.st_mode))
		{
			ft_putstr_fd(path, 2);
			error(": Is a directory", 126);
			return (1);
		}
	}
	else
	{
		ft_putendl_fd("Error: No such file or directory", 2);
		g_glob.exit_status = 127;
		return (1);
	}
	return (0);
}

char	*exable(char **cmd)
{
	char	*path;
	
	path = NULL;
	if (ft_strncmp("/", cmd[0], 1) == 0)
		path = ft_strdup(cmd[0]);
	else if (ft_strncmp("./", cmd[0], 2) == 0) // should ../ work?
		path = ft_strjoin(this_folder_is(1), cmd[0] + 1);
	else if (ft_strncmp("../", cmd[0], 3) == 0)
		path = relative_cd2(cmd[0]);
	else if (ft_strncmp(".", cmd[0], 2) == 0)
	{
		error(".: filename argument required", 2);
		exit(2);
	}
	else
		path = find_path(cmd[0]);
	return (path);
}

// to change SHLVL INSIDE THE PROGRAM;

char	*env_shlvl(void)
{
	char	*shlvl;

	shlvl = NULL;
	if (getenv("SHLVL"))
		shlvl = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(getenv("SHLVL")) + 1));
	return (shlvl);
}

void	do_cmd(t_shell *data)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	g_glob.exit_status = 0;
	if (pipe(pipe_fd) == -1)
		error("Error (pipe)", 0); // should this error just exit...
	pid = fork();
	if (pid == -1)
		error("Error (fork)", 0); // end this?
	if (pid == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		if (data->pipe_flag == 0 && data->out_flag == 0)
			close (pipe_fd[1]);
		else
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);	
		execute(data->cmd);
	}
	else
	{
    	signal(SIGINT, interupt);
		close(data->fd[0]);
		close(pipe_fd[1]);
		data->fd[0] = pipe_fd[0];
		waitpid(pid, &status, 0);
		if (g_glob.exit_status != 130)
		g_glob.exit_status = status;
		data->cmd = freedom("s", data->cmd);
	}
}

void	check_builtin(char **cmd)
{
	 // need to fix all these function to take char ** because need to free, and check options which will be other strings
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		this_folder_is(0);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		env_cmd(cmd);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo_cmd(cmd);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		exit(0);
}
