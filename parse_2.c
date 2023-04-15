/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/15 10:09:26 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//failed test =  ls      -la | uniq| wc     -l

void	parse_input(char *input)
{
	int		i;
	t_shell	*data;
	
	data = (t_shell *)malloc(sizeof(t_shell));
	data->fd[0] = dup(STDIN_FILENO); // start with the normal and deppending on < > and shit will change and send to output func
	data->fd[1] = dup(STDOUT_FILENO);
	i = 0;
	data->cmd = NULL;
	data->start = input;
	if (!(check_empty_line(input)))
		return;
	while (input[i])
	{
		if (input[i] == 32)
		{
			while (input[i] == 32)
				i++;
			space(data, input + i);
		}
		if (input[i] == '|')
			pipex(data, input + i + 1);
			// data->start = input + i + 1;
		// this might be fucked
		// if (input[i] == 39) // single quote
		// 	data->start = single_q(data->start, &data->cmd, &data->fd);
		// else if (input[i] == 34) // double quote
		// if (input[i] == '<')
		// 	data->start = file_in(data->start, data->fd);
		// else if (input[i] == '>')
		// 	file_out();
		else if (input[i] == 36) // $
			envar();
		// else if (input[i] == "$?") // what even is this
		i++;
		if (!input[i] && !data->cmd) // will need to fix this, function to check end to execute or is a file or someshit
		{
			data->cmd = ft_split(data->start, 32);
			do_cmd(data->cmd, data->fd);
		}
		else if (!input[i] && data->cmd)
		{
			data->cmd = add_split(data->cmd, data->start);
			do_cmd(data->cmd, data->fd);
		}
	}
	if (data->cmd)
		freesplit(data->cmd);
	output(data->fd);
	free(data);
}

// char	*single_q(char *input, char *current, int fd)
// {
// 	char	*res;
// 	char	*end;
// 	int		len;
	
// 	if (current == NULL)
// 	{
// 		if (input[0] != 39)
// 		{
// 			end = ft_strchr(input, 32);
// 			len = end - input;
// 			res = ft_strlcpy(res, input, len);
// 			if (find_path(res) == NULL)
// 			{
// 				error(res, 1);
// 				return (NULL);
// 			}
// 			return (res);
// 		}
// 		end = ft_strchr(input[1], 39);	
// 	}
// 	else
// 		return ()
// }// okay this shit is fucked!!! echo still print shit like fuck"some"yes... 
//the whole thing so theres only a need ot parse that shit if theres a $ in the middle..


void	space(t_shell *data, char *new_start)
{
	char	*res;
	char	*end;
	int		len;

	res = NULL;
	if (!data->cmd)
	{
		end = ft_strchr(data->start, 32);
		len = end - data->start;
		res = ft_substr(data->start, 0, len);
		data->cmd = ft_split(res, 32); // some leak here ... 
		free (res);
	}
	else
	{
		end = ft_strchr(data->start, 32);
		len = end - data->start;
		res = ft_substr(data->start, 0, len);
		data->cmd = add_split(data->cmd, res);
		free(res);
	}
	data->start = new_start;
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

void	output(int *fd)
{
	char *buf;
	
	buf = malloc(sizeof(char));
	while (read(fd[0], buf, 1) > 0)
		write(fd[1], buf, 1);
	free(buf);
	close(fd[0]);
	close(fd[1]);
}
void	pipex(t_shell *data, char *new_start)
{
	char	*res;
	char	*end;
	int		len;
	// need to take care of sitution like || maybe sytax error message?
	if (data->cmd)
	{
		do_cmd(data->cmd, data->fd);
		freesplit(data->cmd);
	}
	else
	{
		end = ft_strchr(data->start, '|');
		len = end - data->start;
		res = ft_substr(data->start, 0, len);
		data->cmd = ft_split(res, 32);
		do_cmd(data->cmd, data->fd);
		freesplit(data->cmd);
		free(res);
	}
	data->cmd = NULL;
	data->start = new_start;
}

void	envar(void)
{
	printf("MAKE ENVIRONMENT VARIABLE WORK\n");
}

// char	*file_in(char *start, int *fd)
// {
// 	if (start[0] != '<')
// 	{
		
// 	}
// 	printf("MAKE < this shit WORK\n");
// }

// char	*file_out(char *start, int *fd)
// {
// 	printf("MAKE > this shit WORK\n");
// }