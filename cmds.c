/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:09 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/18 15:04:46 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cmd(t_shell *data)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	g_glob.exit_status = 0;
	if (pipe(pipe_fd) == -1)
		error("Error (pipe)", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork)", 0);
	if (pid == 0)
		cmd_child(data, pipe_fd);
	else
	{
		sig_handler(1);
		close(data->fd[0]);
		close(pipe_fd[1]);
		data->fd[0] = pipe_fd[0];
		waitpid(pid, &status, 0);
		if (g_glob.exit_status != 130 && g_glob.exit_status != 131)
		g_glob.exit_status = status;
		data->cmd = freedom("s", data->cmd);
	}
}

void	cmd_child(t_shell *data, int *pipe_fd)
{
	signal(SIGQUIT, child_quit);
	dup2(data->fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	if (data->pipe_flag == 0 && data->out_flag == 0)
		close (pipe_fd[1]);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	execute(data, data->cmd);
}

void	execute(t_shell *data, char **cmd)
{
	char		*path;
	char		**new_env;

	new_env = NULL;
	if (cmd == NULL)
	{
		data = freedom("dah", data, data);
		exit(0);
	}
	check_builtin(data, cmd);
	path = exable(cmd);
	if (!path)
		bad_cmd(data, path);
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

char	*exable(char **cmd)
{
	char	*path;

	path = NULL;
	if (ft_strncmp("/", cmd[0], 1) == 0)
		path = ft_strdup(cmd[0]);
	else if (ft_strncmp("./", cmd[0], 2) == 0)
		path = ft_strjoin(this_folder_is(1), cmd[0] + 1);
	else if (ft_strncmp("../", cmd[0], 3) == 0)
		path = relative_cd2(cmd[0]);
	else if (ft_strncmp(".", cmd[0], 2) == 0)
	{
		error(".: filename argument required", 2);
		cmd = freedom("s", cmd);
		exit(2);
	}
	else
		path = find_path(cmd[0]);
	return (path);
}

void	check_builtin(t_shell *data, char **cmd)
{
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		this_folder_is(0);
		keep_history(NULL, 2);
		data = freedom("da", data, data);
		exit (0);
	}
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		env_cmd(data);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo_cmd(data, cmd);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		keep_history(NULL, 2);
		data = freedom("da", data, data);
		exit(0);
	}
}
