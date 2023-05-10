/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/10 09:56:46 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob;

void	parse_input(char *input)
{
	int		i;
	t_shell	*data;

	data = data_init();
	i = -1;
	while (input[++i])
	{
		while (input[i] == 32)
			i++;
		if (input[i] == '|')
			i += pipex(data, input + i);
		else if (input[i] == '<')
			i += file_in(data, input + i + 1); // fix $_
		else if (input[i] == '>')
			i += file_out(data, input + i + 1);
		else if (input[i] && input[i] != 32)
			i += space(data, input + i, 0);
		if (data->exit_flag == 1)
		{
			freedom("lsaa", data->files, data->cmd, input, data);
			return ;
		}
	}
	parse_input_two(data, input);
	freedom("saa", data->cmd, input, data);
}

void	parse_input_two(t_shell *data, char *input)
{
	if (data->cmd)
	{
		if (ft_strncmp(data->cmd[0], "exit", 5) == 0)
			ft_exit(data, input);
		else if (ft_strncmp(data->cmd[0], "cd", 3) == 0)
		{
			if (data->cd_flag == 0)
				cd_command(data->cmd);
		}
		else if (ft_strncmp(data->cmd[0], "export", 7) == 0)
			export_cmd(data->cmd);
		else if (ft_strncmp(data->cmd[0], "unset", 6) == 0)
			unset_cmd(data->cmd);
		else
		{
			do_cmd(data);
			output(data);
		}	
	}
}

t_shell	*data_init(void)
{
	t_shell	*data;

	data = (t_shell *)malloc(sizeof(t_shell));
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	data->cmd = NULL;
	data->cd_flag = 0;
	data->exit_flag = 0;
	data->pipe_flag = 0;
	data->out_flag = 0;
	data->files = NULL;
	g_glob.here_flag = 0;
	return (data);
}

void	output(t_shell *data)
{
	char	*buf;

	if (data->out_flag == 1)
		get_content(data);
	else
	{
		buf = malloc(sizeof(char));
		while (read(data->fd[0], buf, 1) > 0)
			write(data->fd[1], buf, 1);
		free(buf);
	}
	if (data->files)
		make_files(data);
	close(data->fd[0]);
	close(data->fd[1]);
}
