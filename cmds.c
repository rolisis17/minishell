/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:09 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/27 17:41:14 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*find_path(char *cmd)
{
	char	*the_path;
    char    *cmd_temp;
    char    **paths;
    int     i;

    i = -1;
	cmd_temp = ft_strjoin("/", cmd);
    paths = ft_split(getenv("PATH"), ':');
    while (paths[++i])
    {
        the_path = ft_strjoin(paths[i], cmd_temp);
        if (access(the_path, F_OK) == 0)
        {
            freesplit(paths);
            free(cmd_temp);
            return (the_path);
        }
        free (the_path);
	}
    freesplit(paths);
    free (cmd_temp);
	return (NULL);
}

void	bad_cmd(char *path, char **cmd)
{
	ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(cmd[0], 2);
	exit(1);
	// freesplit(cmd);
	free(path);
}

void	execute(char **cmd)
{
	char	*path;

	check_builtin(cmd);
	  // need to do a exit function with free in everything for us to call everytime, Joao just fail minishell evaluation. Leaks when exit.
	 // or exit? or exit inside the command func to get out of the fork but here we need to free everything
	// can make the execution within each builtin, this was can disregard options and exit the child process
	path = find_path(cmd[0]);
	if (!path)
		bad_cmd(path, cmd);
	execve(path, cmd, NULL);
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
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);	
		execute(data->cmd);
	}
	else
	{
		close(data->fd[0]);
		close(pipe_fd[1]);
		data->fd[0] = pipe_fd[0];
		waitpid(pid, NULL, 0);
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
	free(data->here_doc);
	data->here_doc = NULL;
}

void	check_builtin(char **cmd)
{
	 // need to fix all these function to take char ** because need to free, and check options which will be other strings
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		this_folder_is(0);
	// else if (ft_strncmp(cmd[0], "export", 6) == 0)
	// else if (ft_strncmp(cmd[0], "unset", 5) == 0)
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		env_cmd(cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		export_cmd(cmd);
	else if (ft_strncmp(cmd[1], "echo", 5) == 0)
		echo_cmd(cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit(cmd); // to say there are no options
	else if (ft_strncmp(cmd[0], "|", 1) == 0)
	{
		// this is not what bash does but we need a bad syntax error of | is first in string
		// ft_putendl_fd("Nothing to pipe", 2); 
		exit(0);
	}
}