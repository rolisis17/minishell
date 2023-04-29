/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/29 19:27:38 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space(t_shell *data, char *new, int arg)
{
	data->len = 0;
	if (arg == 0)
		data->len = get_cmd(new + 1, 0) + 1; // change this to also stop at quote when using in space
	else
		data->len = get_cmd(new, 0);
	data->res = ft_substr(new, 0, data->len);
	check_substr(data, 0);
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res);
	else
		data->cmd = ft_split(data->res, 32);
	if (data->res)
		free(data->res);
	return(data->len - 1);
}

int	quotes(t_shell *data, char *new)
{
	char	*ptr;
	
	ptr = ft_strchr(new + 1, new[0]);
	if (ptr == NULL || new[1] == '\0')
		return(space(data, new, 0));
	data->res = ft_substr(new, 1, ptr - new - 1);
	printf("HERE:%s\n", new);
	data->len = ft_strlen(data->res);
	check_substr(data, new[0]);
	if (data->len == 0)
	{
		if (new[2] == 32 || new[2] == '|' || new[2] == '<' || new[2] == '>') // fix this shit
		// free(data->res);
		// data->res = ft_strdup(" ");
		// return(data->len + 1); // needs to give error 
	}
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res);
	else
		data->cmd = ft_split(data->res, new[0]);
	free(data->res);
	return(data->len + 1); // this was 2 make sure it works with 1... nahhh its better with 1
}

void	check_substr(t_shell *data, char c)
{
	char	*beg;
	int		len;

	if (c == 39)
		return ;
	len = ft_strlen(data->res);
	while(ft_strchr(data->res, 36) != NULL)
	{
		beg = NULL;
		if (data->res[0] != 36)
		{
			beg = ft_strchr(data->res, 36);
			beg = ft_substr(data->res, 0, len - ft_strlen(beg));
		}
		data->res = env_var(data->res, len, beg);
	}
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
		// free(end);
		return(res);
	}	
	beg = ft_strjoin_mod(beg, res, 0);
	beg = ft_strjoin_mod(beg, end, 0);
	freedom(NULL, data, var, end);
	// free(end);
	return (beg);
} // if env variable doesnt exist it needs to be ignored. make work!

void	pipex(t_shell *data)
{
	// need to take care of sitution like || maybe sytax error message?
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
