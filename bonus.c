/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:01:53 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/12 17:38:20 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bonus(t_shell *data, char *new)
{
	data->len = 0;
	while (new[data->len] == new[0])
		data->len++;
	if (data->len > 2)
	{
		error("Syntax error", 2);
		data->exit_flag = 1;
		return (data->len);
	}
	else
		execution(data, new);
	return (data->len);
}

int	priority_new(t_shell *data, char* new)
{
	char	*ptr;
	char	*input;
	char	*res;
	
	res = NULL;
	ptr = ft_strrchr(new, new[0]);
	if (ptr == new)
	{
		error("Syntax error", 2);
		data->exit_flag = 1;
		return (data->len);
	}
	input = ft_substr(new, 1, ptr - new);
	if (check_empty_line(input) == 0)
		// res = parse_input(input, 1);
	if (res == NULL)
		data->op_flag = -1;
	freedom("a", input);
	return (ft_strlen(input));
}

int	priority(t_shell *data, char *new)
{
	char	*ptr;
	
	data->len = 0;
	while (new[data->len] == new[0])
		data->len++;
	if (data->len > 1 || (new[0] == '(' && new[1] == '\0') \
	|| (new[0] == '(' && new[1] == ')') || (new[0] == ')' \
	&& data->op_flag == 0) || (data->cmd && new[0] == '('))
	{
		error("Syntax error", 2);
		data->exit_flag = 1;
		return (data->len);
	}
	if (new[0] == '(')
	{
		ptr = ft_strchr(new + 1, ')');
		if (ptr == NULL)
			return (0);
		data->op_flag = 1;
	}
	else if (new[0] == ')')
			data->op_flag = 0;
			// figure out if successfull or not. set op to whatever it is.
	return (1);
}

void	execution(t_shell *data, char *new)
{
	// if ((data->cmd && data->pipe_flag == 0) || data->cmd)
	data->pipe_flag = 1;
	if (data->op_char == 0 || g_glob.exit_status == 0)
	{
		do_cmd(data);
		output(data);
		data->op = 1;
	}
	else if (data->op_char == '&')
	{
		if (data->cmd)
			do_cmd(data);
		if (g_glob.exit_status == 0 && data->op == 1)
			output(data);
		else
			data->op = -1;
	}
	else if (data->op_char == '|')
	{
		if (data->op == -1)
		// 	data->op = 1;
		// else
		{
			printf("here\n");
			if (data->cmd)
				do_cmd(data);
			if (g_glob.exit_status == 0)
			{
				output(data);
				data->op = 1;
			}
		}
		else
			data->cmd = freedom("s", data->cmd);
		// else if (g_glob.exit_status != 0)
		// 	data->op = -1;
		// else if (data->op == -1)
		// {
		// 	output(data);
		// 	data->op = 1;
		// }
	}
	else 
		data->op = -1;
	data->op_char = new[0];
	clear_pipe(data);
}

void	clear_pipe(t_shell *data)
{
	data->cmd = freedom("s", data->cmd);
	close(data->fd[0]);
	close(data->fd[1]);
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	data->pipe_flag = 0;
	do_cmd(data);
	if (data->files) // do i need to? test
		data->files = freedom("l", data->files);
}

int	op_check(t_shell *data)
{
	if (data->op_data != NULL)
		output(data);
	else if (data->op == 0)
		return (0);
	else if (data->op_char == '&' && data->op == 1)
		return (0);
	else if (data->op_char == '|' && data->op == -1)
		return (0);
	return (1);
}

// TO MAKE 
void	data_to_pipe(t_shell *data)
{
	// put data->op_data into a pipe
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("Error (pipe): ", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork): ", 0);
	else if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(data->op_data, fd[1]);
		free(data);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(data->fd[0]);
		data->fd[0] = fd[0];
		waitpid(pid, NULL, 0);
		data->op_data = freedom("a", data->op_data);
	}
}


void	get_op_data(t_shell *data)
{
	char	*buf;

	buf = ft_calloc(2, sizeof(char));
	while (read(data->fd[0], buf, 1) > 0)
		data->op_data = ft_strjoin_mod(data->op_data, buf, 0);
	free(buf);
	// data->fd[0] = dup(STDIN_FILENO);
	// data->fd[1] = dup(STDOUT_FILENO);
	// data->out_flag = 0;
	// take data from the pipe and store in data->op_data
}