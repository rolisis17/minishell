/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:13:51 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/17 17:19:42 by mstiedl          ###   ########.fr       */
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
			i += file_in(data, input + i + 1);
		else if (input[i] == '>')
			i += file_out(data, input + i + 1);
		else if (input[i] != 32 && input[i])
			i += space(data, input + i);
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

int	space(t_shell *data, char *new)
{
	data->len = 0;
	if (new[0] == 34)// 34 == "
		data->res = dub_qte(data, new);
	if (new[0] == 36)// 36 == $
	{
		if (!env_var(data, new))
			return(data->len - 1);	// not working with simple wrong input $SOMETHING...
	}
	// else if (new[0] == 39)// 39 == '
	// 	func();
	else
	{
		data->len = get_cmd(new);
		data->res = ft_substr(new, 0, data->len);
	}
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res);
	else
		data->cmd = ft_split(data->res, 32);
	if (data->res)
		free(data->res);
	return(data->len - 1);	
}

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
	data->len = get_cmd(new + sp);
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
		data->len = get_cmd(str + sp + space);
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
	data->len = get_cmd(new + sp);
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

char	*env_var(t_shell *data, char *new)
{
	char	*temp;
	char	*temp2;
	
	data->len = get_cmd(new);
	temp = ft_substr(new, 1, data->len);
	temp2 = getenv(temp);
	if (temp2 == NULL)
	{
		// perror(temp); this doesnt work
		// data->res = ft_substr(new, 0, data->len);// check out how bash is behaving its werid
		free(temp);
		return (NULL);
	}
	else
	{
		data->res = ft_calloc(ft_strlen(temp2) + 1, sizeof(char));
		ft_strlcpy(data->res, temp2, ft_strlen(temp2) + 1);
	}
	free(temp);
	return (data->res);
} // if env variable doesnt exist it needs to be ignored. make work!

char	*dub_qte(t_shell *data, char *new)
{
	char	*temp;
	char	*ptr;
	int		ptr_len;
	
	data->len = get_cmd(new);
	temp = ft_substr(new, 1, data->len - 1); // does this need a minus 1?
	ptr = ft_strchr(temp, 34);
	if (!ptr)
		return (ft_substr(new, 0, data->len));
	else if (ft_strlen(ptr) == data->len)
		return (ft_substr(new, 1, data->len - 2)); // if above is no then this is 1 not 2
	else
	ptr_len = ft_strlen(ptr);
	data->res = ft_substr(new, 1, data->len - ptr_len);
	data->res = check_env(data->res);
	data->res = ft_strjoin(data->res, ptr, -2);
}

char	*check_env(char *str)
{
	char	*ptr;
	char	*new;
	char	*var;

	ptr = ft_strchr(str, 36);
	if (ptr == NULL)
		return (str);
	new = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ptr));
	var = ft_strchr(ptr, 32);
	if (var == NULL)
	{
		ptr = getenv(ptr + 1);
		if (ptr == NULL)
			return(new);
		return(ft_strjoin(new, ptr, -2));
	}
	ptr = ft_substr(ptr, 1, ft_strlen(var) - 1); // this and everything after needs to be fixed
	ptr = getenv(var);
	if (ptr == NULL)
		return(new);
	new = 
}