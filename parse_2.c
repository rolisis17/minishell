/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/14 17:12:22 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(char *input)
{
	int		i;
	int		fd[2];
	char	*current;
	char	*start;
	
	fd[0] = dup(STDIN_FILENO); // start with the normal and deppending on < > and shit will change and send to output func
	fd[1] = dup(STDOUT_FILENO);
	i = 0;
	current = NULL;
	start = input;
	if (!(check_empty_line(input)))
		return;
	while (input[i])
	{
		if (input[i] == 32)
		{
			while (input[i] == 32)
				i++;
			current = space(start, current, fd);
			start = input + i; // this might be fucked
		}
		// this might be fucked
		// if (input[i] == 39) // single quote
		// 	start = single_q(start, &current, &fd);
		// else if (input[i] == 34) // double quote
		if (input[i] == '<')
			file_in();
		else if (input[i] == '>')
			file_out();
		else if (input[i] == '|')
		{
			current = pipex(current, fd);
			start = input + i + 1;
			printf(" NEW current: %s\n", current);
			printf(" HERE start:%s\n", start + 1);
		}
		else if (input[i] == 36) // $
			envar();
		// else if (input[i] == "$?") // what even is this
		i++;
		if (!input[i] && !current)
		{
			do_cmd(start, NULL, fd);
			printf("WHY!!!!!\n"); // solve leak... should enter here but no
			
		}
		else if (!input[i] && current)
		{
			do_cmd(current, start, fd);
			printf("HERE!!!!!\n");
		}
		
	}
	if (current)
		free (current);
	output(fd);
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


char	*space(char *start, char *current, int *fd)
{
	char	*res;
	char	*end;
	int		len;
	int		i;
	
	i = 0;
	res = NULL;
	if (!current)
	{
		end = ft_strchr(start, 32);
		len = end - start; // maybe also - i!! need to test
		current = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(current, start, len + 1);
		return (current);
	}
	else
	{
		end = ft_strchr(start, 32);
		len = (end + i) - start;
		res = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(res, end + i, len);
		do_cmd(current, res, fd);
		free (current);
		free (res);
	}	
	return (NULL);	// check this null valid after changes
}

void	do_cmd(char *cmd, char *option, int *fd)
{
	char	*full[3];
	pid_t	pid;
	int		pipe_fd[2];
	
	full[0] = cmd;
	full[1] = option;
	full[2] = NULL;
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
		execute(full);
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

char	*pipex(char *current, int *fd)
{
	if (current)
	{
		do_cmd(current, NULL, fd);
		free (current);
	}
	return (NULL);
}

void	envar(void)
{
	printf("MAKE ENVIRONMENT VARIABLE WORK\n");
}

void	file_in(void)
{
	printf("MAKE PIPES WORK\n");
}

void	file_out(void)
{
	printf("MAKE PIPES WORK\n");
}