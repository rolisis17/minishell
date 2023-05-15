/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:21:50 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/15 18:06:42 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_shell *data)
{
	int		fd[2];
	pid_t	pid;

	g_glob.here_flag = 1;
	if (pipe(fd) == -1)
		error("Error (pipe): ", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork): ", 0);
	else if (pid == 0)
		here_child(data, fd);
	else
	{
		close(fd[1]);
		close(data->fd[0]);
		data->fd[0] = fd[0];
		waitpid(pid, &g_glob.exit_status, 0);
		if (g_glob.exit_status % 255 == 130)
			data->exit_flag = 1;
	}
	return (0);
}

void	here_child(t_shell *data, int *fd)
{
	char	*buffer;
	char	*limiter;

	buffer = NULL;
	close(fd[0]);
	limiter = remove_quotes(data->res, 34, 0, data);
	limiter = remove_quotes(limiter, 39, 1, data);
	data->res = freedom("a", data->res);
	signal(SIGINT, here_child_exit);
	child_loop(data, fd, limiter, buffer);
	data->res = freedom("aaa", buffer, limiter, data->res);
	exit(0);
}

void	child_loop(t_shell *data, int *fd, char *limiter, char *buffer)
{
	int len;
	
	len = ft_strlen(limiter);
	while (1)
	{
		buffer = readline("here_doc> ");
		if (buffer == NULL)
		{
			ft_putendl_fd("WARNING: here_doc delimited by EOF", 2);
			break ;
		}
		if (ft_strncmp(buffer, limiter, len + 1) == 0)
			break ;
		if (ft_strlen(buffer) == 0)
			free(buffer);
		else if (data->here_limiter == 0)
			check_substr(data, buffer, 0);
		else
			check_substr(data, buffer, 39);
		ft_putendl_fd(data->res, fd[1]);
		data->res = freedom("a", data->res);
	}
}
