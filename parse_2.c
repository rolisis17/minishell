/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/12 16:30:09 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(t_shell *data, char *new, int arg)
{
	int	i;

	i = 0;
	data->res = NULL;
	while (end_search(new[i]) == 0)
	{
		if (new[i] == 34 || new[i] == 39)
			i += quote(data, new + i);
		else if (new[i] == 36)
			i += env_var(data, new + i);
		else
			data->res = char_join(data->res, new[i++]);
	}
	if (arg == 1)
		return (i);
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res, 0);
	else if (ft_strlen(data->res) == 0)
		error("Command '' not found", 127);
	else
		data->cmd = ft_split(data->res, 1);
	if (data->res)
		free(data->res);
	return (i - 1);
}

int	quote(t_shell *data, char *new)
{
	char	*ptr;
	char	*temp;

	ptr = ft_strchr(new + 1, new[0]);
	if (ptr == NULL || new[1] == '\0')
	{
		data->res = ft_strjoin_mod(data->res, new, 0);
		return (ft_strlen(new));
	}
	temp = ft_substr(new, 1, ptr - new - 1);
	data->len = ft_strlen(temp);
	check_substr(data, temp, new[0]);
	return (data->len + 2);
}

int	pipex_new(t_shell *data, char *new)
{
	data->pipe_flag = 1;
	data->len = 0;

	if (g_glob.exit_status != 0) //??
		data->cmd = freedom("s", data->cmd);
	while (new[data->len] == '|') // check syntax error |  | eg
			data->len++;
	if (data->len > 2)
	{
		error("Syntax Error", 2); // might need to store the error message until the end
		data->exit_flag = 1;
		return (data->len - 1);
	}
	// if (data->op_data != NULL && data->op_flag == 0)
	// 	data_to_pipe(data);
	// else
	pipex_2(data, 0);
	if (data->out_flag == 1)
		get_content(data);
	data->cmd = freedom("s", data->cmd);
	return (0);
}


void	pipex_2(t_shell *data, int arg)
{
	if (!data->cmd)
		do_cmd(data);
	else if (ft_strncmp(data->cmd[0], "cd", 3) == 0 \
		|| ft_strncmp(data->cmd[0], "export", 7) == 0 \
		|| ft_strncmp(data->cmd[0], "unset", 6) == 0)
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
