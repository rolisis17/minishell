/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/13 14:12:17 by mstiedl          ###   ########.fr       */
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
		sig_handler();
		line = readline("> ");
		if (line == NULL)
			quit(line);
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
	
    // printf("You entered: %s\n", line);
	// here we need to parse.
	cmd = ft_split(line, 32);
	path = find_path(cmd[0]); // finds the path to the cmd
	if (!path)
		bad_cmd(path, cmd);
	else
		execute(path, cmd); // forks to execute and frees everything 
    add_history(line);
	// so far this is only good for single commands.
}

int	searchforquots(char *str, int quote)
{
	int	f;
	int	counter;

	f = 0;
	counter = 0;
	while (str[f])
	{
		if (str[f] == quote)
			counter++;
		f++;
	}
	return (counter % 2 != 0);
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
