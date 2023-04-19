/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/19 10:29:48 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(char *input)
{
	int		i;
	t_shell	*data;
	
	data = (t_shell *)malloc(sizeof(t_shell));
	data->fd[0] = dup(STDIN_FILENO); // start with the normal and deppending on < > and shit will change and send to output func
	data->fd[1] = dup(STDOUT_FILENO);
	data->cmd = NULL;
	i = -1;
	while (input[++i])
	{
		while (input[i] == 32)
			i++;
		if (input[i] == '|')
			pipex(data);
		else if (input[i] == '<')
			i += file_in(data, input + i + 1); // need to check how there work with quotes and $ does it need the checker?
		else if (input[i] == '>')
			i += file_out(data, input + i + 1); 
		else if (input[i] == 34 || input[i] == 39)
			i += quotes(data, input + i);
		else if (input[i] != 32 && input[i])
			i += space(data, input + i, 1);
		// else if (input[i] == "$?") // what even is this
	}
	if (data->cmd)
	{
		do_cmd(data->cmd, data->fd);
		freesplit(data->cmd);
	}
	output(data->fd);
	free(data);
}

int	file_in(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '<')
		flag = 1;
	while(new[sp + flag] == 32)
		sp++;
	data->len = get_cmd(new + sp + flag, 1);
	data->res = ft_substr(new, flag + sp, data->len);
	if (flag == 1)
		here_doc(data);
	else
	{
		data->fd[0] = open(data->res, O_RDONLY);
		if (data->fd[0] < 0)
			perror("Error");	
	}
	free(data->res);
	return (data->len + flag + sp);
}

int	file_out(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '>')
		flag = 1;
	while(new[sp + flag] == 32)
		sp++;
	data->len = get_cmd(new + sp + flag, 1);
	data->res = ft_substr(new, flag + sp, data->len);
	if (flag == 1)
		data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->fd[1] < 0)
		perror("Error");
	free(data->res);
	return (data->len + flag + sp);
}

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] != '\n' && line[f] != 32 && line[f] != '.')
			return (1);
	}
	return (0);
}

void	here_doc(t_shell *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error("Error (pipe)", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork)", 0);
	if (pid == 0)
		here_doc_child(data, pipe_fd);
	else
	{
		close(data->fd[0]);
		close(pipe_fd[1]);
		data->fd[0] = pipe_fd[0];
		waitpid(pid, NULL, 0);
	}
} // signals dont work in here_doc!!!

void	here_doc_child(t_shell *data, int *pipe)
{
	char	*buffer;
	
	close(pipe[0]);
	while (1)
	{
		buffer = readline("here_doc> ");
		if (ft_strncmp(buffer, data->res, data->len) == 0)
			break ;
		write(pipe[1], buffer, ft_strlen(buffer));
		write(pipe[1], "\n", 1);
		free(buffer);
	}
	write(pipe[1], "\0", 1);
	free (buffer);
	exit(0);
}
	