/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/18 18:57:40 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//failed test =  ls      -la | uniq| wc     -l

void	parse_input(char *input)
{
	int		i;
	t_shell	*data;
	
	data = (t_shell *)malloc(sizeof(t_shell));
	data->fd[0] = dup(STDIN_FILENO); // start with the normal and deppending on < > and shit will change and send to output func
	data->fd[1] = dup(STDOUT_FILENO);
	i = 0;
	data->cmd = NULL;
	if (!(check_empty_line(input)))
		return;
	while (input[i])
	{
		while (input[i] == 32)
			i++;
		if (input[i] == '|')
			pipex(data);
		else if (input[i] == '<')
			i += file_in(data, input + i + 1); // need to check how there work with quotes and $ does it need the checker?
		else if (input[i] == '>')
			i += file_out(data, input + i + 1); 
		else if (input[i] == 34 || input[i] == 39)
			i += quotes(data, input + i);
		else if (input[i] != 32 && input[i])
			i += space(data, input + i, 1);
		// else if (input[i] == "$?") // what even is this
		if (!input[i++]) // why??
			break ;
	}
	if (data->cmd)
	{
		do_cmd(data->cmd, data->fd);
		freesplit(data->cmd);
	}
	output(data->fd);
	free(data);
}

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
	return(data->len - 1);  // does this fuck anything up?
}

int	quotes(t_shell *data, char *new)
{
	char	*ptr;
	
	ptr = ft_strchr(new + 1, new[0]);
	if (ptr == NULL)
		return(space(data, new, 0));
	data->res = ft_substr(new, 1, ptr - new - 1);
	data->len = ft_strlen(data->res);
	check_substr(data, new[0]);
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res);
	else
		data->cmd = ft_split(data->res, 34);
	free(data->res);
	return(data->len + 2);
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
		res = ft_strjoin(beg, end, -2);
		freedom(NULL, data, var);
		free(end);
		return(res);
	}	
	beg = ft_strjoin(beg, res, -2);
	beg = ft_strjoin(beg, end, -2);
	freedom(NULL, data, var);
	free(end);
	return (beg);
} // if env variable doesnt exist it needs to be ignored. make work!

void	pipex(t_shell *data)
{
	// need to take care of sitution like || maybe sytax error message?
	if (data->cmd)
		do_cmd(data->cmd, data->fd);
	else
	{
		data->cmd = ft_split("|", 32);
		do_cmd(data->cmd, data->fd);
	}
	data->cmd = freedom(data->cmd, NULL, NULL);
}

int	file_in(t_shell *data, char *new)
{
	int		sp;

	data->len = 0;
	sp = 0;
	while(new[sp] == 32)
		sp++;
	data->len = get_cmd(new + sp, 1);
	data->len = search_another(data, new, sp, '<');
	data->fd[0] = open(data->res, O_RDONLY);
	if (data->fd[0] < 0)
		perror("Error");
	else if (data->cmd)
	{
		do_cmd(data->cmd, data->fd);
		data->cmd = freedom(data->cmd, NULL, NULL);	
	}
	free(data->res);
	return (data->len);
}

int search_another(t_shell *data, char *str, int sp, int c)
{
	int		space;
	
	space = 0;
	while(str[space] == 32)
		space++;
	if (str[sp + data->len + space] == c)
	{
		sp += ++data->len;
		sp += space;
		space = 0;
		while(str[sp] == 32)
			space++;
		data->len = get_cmd(str + sp + space, 1);
		data->res = ft_substr(str, sp + space, data->len);
		return (sp + space + data->len);
	}
	else 
		data->res = ft_substr(str, sp, data->len);
	return (data->len + sp);
}

int	file_out(t_shell *data, char *new)
{
	int		sp;

	data->len = 0;
	sp = 0;
	while(new[sp] == 32)
		sp++;
	data->len = get_cmd(new + sp, 1);
	data->len = search_another(data, new, sp, '>');
	data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->fd[1] < 0)
		perror("Error");
	else if (data->cmd)
	{
		do_cmd(data->cmd, data->fd);
		data->cmd = freedom(data->cmd, NULL, NULL);	
	}
	free(data->res);
	return (data->len);
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
