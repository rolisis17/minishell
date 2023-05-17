/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/17 11:09:59 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob;

void	parse_input(t_shell *data)
{
	int		i;

	data = data_init(data);
	i = -1;
	while (data->input[++i])
	{
		while (data->input[i] == 32)
			i++;
		if (data->input[i] == '|')
			i += pipex(data, data->input + i);
		else if (data->input[i] == '<')
			i += file_in(data, data->input + i + 1);
		else if (data->input[i] == '>')
			i += file_out(data, data->input + i + 1);
		else if (data->input[i] && data->input[i] != 32 && data->exit_flag == 0)
			i += space(data, data->input + i, 0);
		if (data->exit_flag == 1)
		{
			freedom("d", data);
			return ;
		}
	}
	parse_input_two(data);
	freedom("d", data);
}

void	parse_input_two(t_shell *data)
{
	if (data->cmd && data->file_err == 0 && data->empty == 0)
	{
		if (data->pipe_flag == 1)
			pipex_2(data, 1);
		else if (ft_strncmp(data->cmd[0], "exit", 5) == 0)
			ft_exit(data);
		else if (ft_strncmp(data->cmd[0], "cd", 3) == 0)
			cd_command(data->cmd);
		else if (ft_strncmp(data->cmd[0], "export", 7) == 0)
			export_cmd(data->cmd);
		else if (ft_strncmp(data->cmd[0], "unset", 6) == 0)
			unset_cmd(data->cmd, 0);
		else
		{
			do_cmd(data);
			output(data);
		}
	}
	else if (!data->cmd && data->file_err == 0 && data->empty == 0)
	{
		do_cmd(data);
		output(data);
	}
}

t_shell	*data_init(t_shell	*data)
{
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	data->cmd = NULL;
	data->res = NULL;
	data->exit_flag = 0;
	data->pipe_flag = 0;
	data->out_flag = 0;
	data->q_flag = 0;
	data->empty = 0;
	data->file_err = 0;
	data->files = NULL;
	data->here_limiter = 0;
	data->limiter = NULL;
	g_glob.here_flag = 0;
	return (data);
}

void	output(t_shell *data)
{
	char	*buf;

	if (data->out_flag == 1 && data->file_err == 0)
		get_content(data);
	else if (data->file_err == 0)
	{
		buf = ft_calloc(sizeof(char), 2);
		while (read(data->fd[0], buf, 1) > 0)
			write(data->fd[1], buf, 1);
		free(buf);
	}
	if (data->files)
		make_files(data);
}
