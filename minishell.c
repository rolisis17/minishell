/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/12 21:03:56 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *line;

	ft_printf("\033[2J\033[1;1H");
	line = NULL;
    while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break;
		}
		handle_input(line);
		free(line);
    }
    return 0;
}

void make_history(char *line)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	add_history(line);
}

void handle_input(char *line)
{
	char	**cmd;
	char	*path;
	char	*quotes;
    // printf("You entered: %s\n", line);
	// here we need to parse.
	if (!(check_empty_line(line)))
		return;
	quotes = to_trim_quotes(line, 39);
	if (quotes)
	{
		printf("%s\n", quotes);
		free (quotes);
	}
	// here we finish parse.
	cmd = ft_split(line, 32);
	if (ft_strncmp(line, "pwd", 3) == 0)
		this_folder_is(0);
	if (ft_strncmp(line, "cd", 2) == 0)
		cd_command(line);
	path = find_path(cmd[0]); // finds the path to the cmd
	if (!path)
		bad_cmd(path, cmd);
	else
		execute(path, cmd); // forks to execute and frees everyhting 
	make_history(line);
	// so far this is on;y good for single commands.
}

void	freesplit(char **splited)
{
	int	counter;

	counter = 0;
	while (splited[counter])
	{
		free(splited[counter]);
		counter++;
	}
	free (splited);
}
