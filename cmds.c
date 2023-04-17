/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:09 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/17 15:52:59 by mstiedl          ###   ########.fr       */
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
	cmd_temp = ft_strjoin("/", cmd, 0);
    paths = ft_split(getenv("PATH"), ':');
    while (paths[++i])
    {
        the_path = ft_strjoin(paths[i], cmd_temp, 0);
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

	// check_builtin() // check for builtins here!!!
	// can make the execution within each builtin, this was can disregard options and exit the child process
	path = find_path(cmd[0]);
	if (!path)
		bad_cmd(path, cmd);
	execve(path, cmd, NULL);
}

void	do_cmd(char **cmd, int *fd)
{
	pid_t	pid;
	int		pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
		error("Error (pipe)", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork)", 0);
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		execute(cmd);
	}
	else
	{
		close(fd[0]);
		close(pipe_fd[1]);
		fd[0] = pipe_fd[0];
		waitpid(pid, NULL, 0);
	}
}
