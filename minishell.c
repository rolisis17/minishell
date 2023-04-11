/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/11 20:30:36 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main()
{
	int		f;
	char	*input;
	char	*hist[1000];

	f = 0;
	ft_printf("\033[2J\033[1;1H");
	while(1)
	{
		ft_printf("$ ");
		input = get_next_line(STDIN_FILENO);
		hist[f] = input;
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free (input);
			exit (0);
		}
		ft_printf("%d\n", searchforquots(input, 34));
	}
}


// Define a function to handle user input
void handle_input(char *line) {
    printf("You entered: %s\n", line);
    // Add the user's input to the history list
    add_history(line);
}

int main(void) {
    // Set up the readline library
    rl_bind_key('\t', rl_complete);
    stifle_history(100);

    // Loop to read user input
    char *line;
    while ((line = readline("> ")) != NULL) {
        // If the user entered a command, handle it
        handle_input(line);
        // Free the memory allocated by readline
        free(line);
    }

    return 0;
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
