/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/18 10:38:19 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(t_shell *data, char *new, int arg)
{
	int		i;
	char	**wild;

	i = 0;
	data->res = NULL;
	wild = NULL;
	data->here_limiter = 0;
	while (end_search(new[i]) == 0)
	{
		if (new[i] == 34 || new[i] == 39)
			i += quote(data, new + i);
		else if (new[i] == 36)
			i += env_var(data, new + i);
		else
			data->res = char_join(data->res, new[i++]);
	}
	if (ft_strchr(data->res, '*') != NULL && data->q_flag == 0)
		wild = read_folder(data->res);
	data->q_flag = 0;
	if (arg == 1)
		return (i);
	how_split(data, wild);
	data->res = freedom("a", data->res);
	return (i - 1);
}

void	how_split(t_shell *data, char **wild)
{
	if (data->cmd && wild)
		data->cmd = merge_split(data->cmd, wild);
	else if (data->cmd)
		data->cmd = add_split(data->cmd, data->res);
	else if (ft_strlen(data->res) == 0)
	{
		data->empty = 1;
		data->res = freedom("a", data->res);
		error("Command '' not found", 127);
	}
	else
	{
		if (wild)
			data->cmd = copy_split(wild, 0);
		else
			data->cmd = ft_split(data->res, 1);
	}
}

int	quote(t_shell *data, char *new)
{
	char	*ptr;
	char	*temp;

	ptr = ft_strchr(new + 1, new[0]);
	if (ptr == NULL || new[1] == '\0')
	{
		data->res = char_join(data->res, new[0]);
		return (1);
	}
	data->here_limiter = 1;
	temp = ft_substr(new, 1, ptr - new - 1);
	data->len = ft_strlen(temp);
	check_substr(data, temp, new[0]);
	data->q_flag = 1;
	return (data->len + 2);
}

int	pipex(t_shell *data, char *new)
{
	if (data->empty == 1)
	{
		data->cmd = freedom("s", data->cmd);
		data->empty = 0;
		return (0);
	}
	data->pipe_flag = 1;
	data->len = 0;
	if (data->file_err == 1)
		data->cmd = freedom("s", data->cmd);
	data->len = syntax_check(new);
	if (data->len > 1)
	{
		error("Syntax Error", 2);
		data->exit_flag = 1;
		return (data->len - 1);
	}
	pipex_2(data, 0);
	if (data->out_flag == 1)
		get_content(data);
	data->cmd = freedom("s", data->cmd);
	data->file_err = 0;
	return (0);
}

void	pipex_2(t_shell *data, int arg)
{
	if (ft_strncmp(data->cmd[0], "cd", 3) == 0 \
		|| ft_strncmp(data->cmd[0], "export", 7) == 0 \
		|| ft_strncmp(data->cmd[0], "unset", 6) == 0 \
		|| ft_strncmp(data->cmd[0], "exit", 5) == 0)
	{
		data->cmd = freedom("s", data->cmd);
		close(data->fd[0]);
		data->fd[0] = dup(STDIN_FILENO);
	}
	else
	{
		do_cmd(data);
		if (arg == 1)
			output(data);
	}
}
