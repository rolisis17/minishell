/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/04 16:45:57 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_new(t_shell *data, char *new, int arg)
{
	int	i;
	
	i = 0;
	data->res = NULL;
	while(new[i] && new[i] != '|' && new[i] != '<' && new[i] != '>' && new[i] != 32)
	{
		if (new[i] == 34 || new[i] == 39)
			i += quote_new(data, new + i);
		else if (new[i] == 36)
			i += env_var_new(data, new + i);
		else
			data->res = char_join(data->res, new[i++]);
	}
	if (arg == 1)
		return (i);
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res, 0);
	else if (ft_strlen(data->res) == 0)
		error("Command '' not found", 1); // cannot send empty str to find path, can make seperate condition, thats it.
	else
		data->cmd = ft_split(data->res, 1);
	if (data->res)
		free(data->res);
	return (i - 1);
}

int	quote_new(t_shell *data, char *new)
{
	char	*ptr;
	char	*temp;
	
	ptr = ft_strchr(new + 1, new[0]);
	if (ptr == NULL || new[1] == '\0')
	{
		data->res = ft_strjoin_mod(data->res, new, 0);
		return(ft_strlen(new));
	}
	temp = ft_substr(new, 1, ptr - new - 1);
	data->len = ft_strlen(temp);
	check_substr_new(data, temp, new[0]);
	return(data->len + 2);
}

char	*env_var(char *data, int len, char *beg)
{
	char	*var;
	char	*end;
	char	*res;
	int		cmd_len;
	
	cmd_len = get_cmd(data + ft_strlen(beg), 0);
	var = ft_substr(data, ft_strlen(beg) + 1, cmd_len - 1);
	cmd_len = ft_strlen(beg) + ft_strlen(var) + 1;
	end = ft_substr(data, cmd_len, len - cmd_len);
	res = getenv(var);
	if (res == NULL)
	{
		res = ft_strjoin_mod(beg, end, 0);
		freedom(NULL, data, var, end);
		return(res);
	}	
	beg = ft_strjoin_mod(beg, res, 0);
	beg = ft_strjoin_mod(beg, end, 0);
	freedom(NULL, data, var, end);
	return (beg);
} 

void	pipex(t_shell *data)
{
	// need to take care of sitution like || maybe sytax error message?
	data->pipe_flag = 1;
	if (data->cmd)
	{
		if (ft_strncmp("cd", data->cmd[0], 3) == 0)
		{
			data->cmd = freedom(data->cmd, NULL, NULL, NULL);
			close(data->fd[0]);
			data->fd[0]= dup(STDIN_FILENO);	
		}
		else
			do_cmd(data);
	}
	else
	{
		data->cmd = ft_split("|", 32);
		do_cmd(data);
	}
	data->cmd = freedom(data->cmd, NULL, NULL, NULL);
	data->cd_flag++;
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
