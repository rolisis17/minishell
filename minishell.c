/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/12 13:17:21 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *line;

	ft_printf("\033[2J\033[1;1H");
    // Loop to read user input
	line = NULL;
    while (ft_strncmp(line, "exit", 4) != 0)
	{
		if (line)
        	free(line);
		line = readline("> ");
        rl_on_new_line();
        rl_replace_line("prev command", 0);
        rl_redisplay();
        handle_input(line);
    }
    return 0;
}

void handle_input(char *line)
{
    printf("You entered: %s\n", line);
    add_history(line);
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
