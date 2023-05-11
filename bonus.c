/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:01:53 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/11 22:35:55 by mstiedl          ###   ########.fr       */
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

int	priority(t_shell *data, char *new)
{
	char	*ptr;
	
	data->len = 0;
	while (new[data->len] == new[0])
		data->len++;
	if (data->len > 1)
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
	{
		if (data->op_flag == 1)
		{
			data->op_flag = 0;
			// figure out if successfull or not. set op to whatever it is.
			data_to_pipe(data);
			return (1);
		}
	}
	return (0);
}

void	execution(t_shell *data, char *new)
{
	data->pipe_flag = 1;
	if (g_glob.exit_status == 0 && data->cmd)
		do_cmd(data);
	if (data->op_char == 0 && g_glob.exit_status == 0)
	{
		output(data);
		data->op = 1;
	}
	else if (data->op_char == '&')
	{
		if (g_glob.exit_status == 0 && data->op == 1)
			output(data);
		else
			data->op = -1;
	}
	else if (data->op_char == '|')
	{
		if (g_glob.exit_status != 0)
			data->op = -1;
		else if (data->op == -1)
		{
			output(data);
			data->op = 1;
		}
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
	if (data->op == 0)
		return (0);
	if (data->op_char == '&' && data->op == 1)
		return (0);
	if (data->op_char == '|' && data->op == -1)
		return (0);
	return (1);
}

// TO MAKE 
void	data_to_pipe(t_shell *data)
{
	// put data->op_data into a pipe
}

void	get_op_data(t_shell *data)
{
	// take data from the pipe and store in data->op_data
}