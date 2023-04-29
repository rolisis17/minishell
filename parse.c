/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/29 17:57:36 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(char *line)
{
	int		i;
	char	*input;
	t_shell	*data;
	
	data = data_init();
	input = ft_strtrim(line, " ");
	i = 0;
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
		else if (input[i] && input[i] != 32)
			i += space(data, input + i, 1);
		// else if (input[i] == "$?") // what even is this
		i++;
	}
	if (data->cmd)
	{
		if (ft_strncmp(data->cmd[0], "cd", 3) == 0)
		{
			if (data->cd_flag == 0)
				cd_command(data->cmd);
		}
		else // here_doc need to fix "LIMITER" in quotes.
		{
			do_cmd(data);
			output(data->fd);
		}
		// freesplit(data->cmd);
	}
	freedom(data->cmd, data->here_doc, input, data);
}

t_shell	*data_init(void)
{
	t_shell	*data;
	
	data = (t_shell *)malloc(sizeof(t_shell));
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	data->cmd = NULL;
	data->here_doc = NULL;
	data->cd_flag = 0;
	return (data);
}

int	file_in(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '<')
		flag = 1;
	while(new[sp + flag] == 32)
		sp++;
	data->len = get_cmd(new + sp + flag, 1);
	data->res = ft_substr(new, flag + sp, data->len);
	if (flag == 1)
		here_new(data);
	else
	{
		data->fd[0] = open(data->res, O_RDONLY);
		if (data->fd[0] < 0)
		{
			perror("Error");	
			data->cmd = freedom(data->cmd, NULL, NULL, NULL); // test!
		}
	}
	free(data->res);
	return (data->len + flag + sp);
}

int	file_out(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '>')
		flag = 1;
	while(new[sp + flag] == 32)
		sp++;
	data->len = get_cmd(new + sp + flag, 1);
	data->res = ft_substr(new, flag + sp, data->len);
	if (flag == 1)
		data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->fd[1] < 0)
		perror("Error");
	free(data->res);
	return (data->len + flag + sp);
}

void	here_new(t_shell *data)
{
	char	*buffer;
	char	*limiter;
	int		len;

	limiter = remove_quotes(data->res, 34, 0);
	limiter = remove_quotes(limiter, 39, 1);
	len = ft_strlen(limiter);
	while (1)
	{
		buffer = readline("here_doc> ");
		if (ft_strncmp(buffer, limiter, len + 1) == 0)
			break ;
		data->here_doc = ft_strjoin_mod(data->here_doc, buffer, 0);
		data->here_doc = ft_strjoin_mod(data->here_doc, "\n", 0);
		free(buffer);
	}
	freedom(NULL, buffer, limiter, NULL);
}

char	*remove_quotes(char *str, int qte, int arg)
{
	char	*res;
	char	*ptr;
	char	*start;
	char	*end;
	
	ptr = str;
	res = NULL;
	start = ft_strchr(ptr, qte);
	while (start != NULL)
	{
		end = ft_strchr(start + 1, qte);
		if (end)
			ptr = split_n_join(ft_substr(ptr, 0, end - ptr), NULL, qte);
		res = ft_strjoin_mod(res, ptr, 0);
		if (end)
			free(ptr);
		ptr = end + 1;	
		start = ft_strchr(end, qte);
	}
	if (!res)
		res = ft_strdup(str);
	if (arg == 1)
		free(str);
	return (res);
}
