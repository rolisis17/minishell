/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:09 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/09 16:40:41 by dcella-d         ###   ########.fr       */
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
	exit(127);
	// freesplit(cmd); 
	free(path); // fix this... how can free after exit
}

void	execute(char **cmd)
{
	char	*path;
	char	**new_env;

	check_builtin(cmd);
	  // need to do a exit function with free in everything for us to call everytime, Joao just fail minishell evaluation. Leaks when exit.
	 // or exit? or exit inside the command func to get out of the fork but here we need to free everything
	// can make the execution within each builtin, this was can disregard options and exit the child process
	if (ft_strncmp("/", cmd[0], 1) == 0)
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd[0]);
	if (!path)
		bad_cmd(path, cmd);
	new_env = modify_split(g_glob.environ, env_shlvl(), 1, '=');
	if (execve(path, cmd, new_env) == -1)
	{
		perror("execve");
		freedom("ssa", cmd, new_env, path);
	}
}

// to change SHLVL INSIDE THE PROGRAM;

char	*env_shlvl(void)
{
	char	*shlvl;

	shlvl = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(getenv("SHLVL")) + 1));
	return (shlvl);
}

void	do_cmd(t_shell *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	data_to_pipe(data);
	if (pipe(pipe_fd) == -1)
		error("Error (pipe)", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork)", 0);
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
		waitpid(pid, &g_glob.exit_status, 0);
	}
}

void	data_to_pipe(t_shell *data)
{
	int		fd[2];
	pid_t	pid;

	if (!data->here_doc)
		return ;
	if (pipe(fd) == -1)
		error("Error (pipe): ", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork): ", 0);
	else if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(data->here_doc, fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(data->fd[0]);
		data->fd[0] = fd[0];
		waitpid(pid, NULL, 0);
	}
	data->here_doc = freedom("a", data->here_doc);
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
}
