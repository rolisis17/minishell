/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/09 12:55:49 by mstiedl          ###   ########.fr       */
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
		if (ft_strncmp("?", var, 2) == 0)
			beg = ft_strjoin_mod(beg, ft_itoa(g_glob.exit_status), 0);
		res = ft_strjoin_mod(beg, end, 0);
		freedom("aaa", data, var, end);
		return(res);
	}	
	beg = ft_strjoin_mod(beg, res, 0);
	beg = ft_strjoin_mod(beg, end, 0);
	freedom("aaa", data, var, end);
	return (beg);
} 

int	pipex(t_shell *data, char *new)
{
	// need to take care of sitution like || maybe sytax error message?
	data->pipe_flag = 1;
	data->len = 0;
	if (!data->cmd || new[1] == '|')
	{
		while(new[data->len] == '|')
			data->len++;
		ft_putendl_fd("Syntax Error", 2);
		g_glob.exit_status = 2; // maybe also need to stop the rest of cmds
		return (data->len - 1);
	}
	if (ft_strncmp("cd", data->cmd[0], 3) == 0)
	{
		data->cmd = freedom("s", data->cmd);
		close(data->fd[0]);
		data->fd[0]= dup(STDIN_FILENO);	
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

void	output(t_shell *data)
{
	char *buf;

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
