/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/06 14:48:45 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob;

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
		else if (input[i] && input[i] != 32)
			i += space_new(data, input + i, 0);
		if (data->exit_flag == 1 || g_glob.here_exit == 1)
		{
			freedom(data->cmd, data->here_doc, input, data);
			g_glob.here_exit = 0;
			return ;
		}
		// else if (input[i] == "$?") // what even is this
		i++;
	}
	// set_env(data);
	if (data->cmd)
	{
		if (ft_strncmp(data->cmd[0], "cd", 3) == 0)
		{
			if (data->cd_flag == 0)
				cd_command(data->cmd);
		}
		else if (ft_strncmp(data->cmd[0], "export", 7) == 0)
			export_cmd(data->cmd);
		else if (ft_strncmp(data->cmd[0], "unset", 6) == 0)
			unset_cmd(data->cmd);
		else
		{
			do_cmd(data);
			output(data->fd);
		}
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
	data->exit_flag = 0;
	data->pipe_flag = 0;
	data->out_flag = 0;
	g_glob.here_flag = 0;
	return (data);
}

int	file_in(t_shell *data, char *new)
{
	int		sp;
	int		flag;

	sp = 0;
	flag = 0;
	if (new[0] == '<') // weird with <<< fix 
		flag = 1;
	while(new[sp + flag] == 32)
		sp++;
	data->len = space_new(data, new + sp + flag, 1); // still need to figure out <<<
	if (data->res == NULL)
	{
		ft_putendl_fd("Syntax error", 2); // this needs to be added to errors! shouldnt execute anything if this error occures leave loop maybe with a flag
		data->exit_flag = 1;
	}
	else if (flag == 1)
		g_glob.here_flag = here_doc(data);
	else
	{
		data->fd[0] = open(data->res, O_RDONLY);
		if (data->fd[0] < 0)
		{
			perror("Error");	
			data->cmd = freedom(data->cmd, NULL, NULL, NULL);
		}
	}
	freedom(NULL, data->res, NULL, NULL);
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
	data->len = space_new(data, new + sp + flag, 1);
	if (data->res == NULL)
	{
		ft_putendl_fd("Syntax error", 2); // this needs to be added to errors! shouldnt execute anything if this error occures leave loop maybe with a flag
		data->exit_flag = 1;
	}
	else 
	{
		data->out_flag = 1;
		if (flag == 1)
			data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			data->fd[1] = open(data->res, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (data->fd[1] < 0)
			perror("Error");
		free(data->res);
	}
	return (data->len + flag + sp);
}

int	here_doc(t_shell *data)
{
	int		fd[2];
	pid_t	pid;

	g_glob.here_flag = 1;
	if (pipe(fd) == -1)
		error("Error (pipe): ", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork): ", 0);
	else if (pid == 0)
	{
		close(fd[0]);
		here_child(data, fd);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(data->fd[0]);
		data->fd[0] = fd[0]; // if heredoc already exist dont use current pipe as input
		waitpid(pid, NULL, 0);
	}
	return (0);
}

void	here_child(t_shell *data, int *fd)
{
	char	*buffer;
	char	*limiter;
	int		len;
	
	limiter = remove_quotes(data->res, 34, 0);
	limiter = remove_quotes(limiter, 39, 1);
	data->res = freedom(NULL, data->res, NULL, NULL);
	len = ft_strlen(limiter);
	signal(SIGINT, here_child_exit);
	while (1)
	{
		buffer = readline("here_doc> ");
		if (buffer == NULL)
		{
			ft_putendl_fd("WARNING: here-document delimited by end-of-file", 2);
			break ;
		}
		if (ft_strncmp(buffer, limiter, len + 1) == 0)
			break ;
		check_substr_new(data, buffer, 0);
		ft_putendl_fd(data->res, fd[1]);
		data->res = freedom(NULL, NULL, data->res, NULL);
	}
	data->res = freedom(NULL, buffer, limiter, data->res);	
}

