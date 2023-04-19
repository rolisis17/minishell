/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/19 08:42:27 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(char *input)
{
	int		i;
	t_shell	*data;
	
	data = (t_shell *)malloc(sizeof(t_shell));
	data->fd[0] = dup(STDIN_FILENO); // start with the normal and deppending on < > and shit will change and send to output func
	data->fd[1] = dup(STDOUT_FILENO);
	data->cmd = NULL;
	i = -1;
	while (input[++i])
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
	}
	if (data->cmd)
	{
		do_cmd(data->cmd, data->fd);
		freesplit(data->cmd);
	}
	output(data->fd);
	free(data);
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

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] != '\n' && line[f] != 32 && line[f] != '.')
			return (1);
	}
	return (0);
}
