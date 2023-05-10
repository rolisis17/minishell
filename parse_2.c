/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/10 15:38:03 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(t_shell *data, char *new, int arg)
{
	int	i;

	i = 0;
	data->res = NULL;
	while (new[i] && new[i] != '|' && new[i] != '<' && \
		new[i] != '>' && new[i] != 32)
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

int	pipex(t_shell *data, char *new)
{
	data->pipe_flag = 1;
	data->len = 0;
	if (!data->cmd || new[1] == '|')
	{
		while (new[data->len] == '|')
			data->len++;
		error("Syntax Error", 2);
		data->exit_flag = 1;
		return (data->len - 1);
	}
	if (ft_strncmp("cd", data->cmd[0], 3) == 0)
	{
		data->cmd = freedom("s", data->cmd);
		close(data->fd[0]);
		data->fd[0] = dup(STDIN_FILENO);
	}
	else
		do_cmd(data);
	if (data->out_flag == 1)
		get_content(data);
	data->out_flag = 0;
	data->cmd = freedom("s", data->cmd);
	data->cd_flag++;
	return (0);
}
