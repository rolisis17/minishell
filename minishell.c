/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/29 19:32:11 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ac, char **av, char **envp
int main()
{
    char *line;

	new_history();
	set_path_env();
	// ft_printf("\033[2J\033[1;1H");
	line = NULL;
    while (1)
	{
		sig_handler();
		// rl_on_new_line();
		line = readline("> ");
		keep_history(line, 0);
		if (line == NULL)
			quit(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			quit(line);
		if ((check_empty_line(line)))
        	parse_input(line);
		freedom(NULL, line, NULL);
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

void	keep_history(char *line, int check)
{
	static char **keep;

	if (!check)
	{
		if (!keep)
			keep = ft_split(line, 02);
		else
			keep = add_split(keep, line, 0);
		add_history(line);
	}
	if (check && keep)
		hiddenfile_history(keep);
}

void	new_history()
{
	char	*gnl;
	char	*res;
	int		fd;

	if (access(".minihist", F_OK) == 0)
	{
		fd = open(".minihist", O_RDWR);
		gnl = get_next_line(fd);
		while (gnl)
		{
			res = ft_strtrim(gnl, "\n");
			keep_history(res, 0);
			freedom (NULL, res, gnl);
			gnl = get_next_line(fd);
		}
		if (gnl)
			free (gnl);
		close (fd);
		if (unlink(".minihist") == -1)
		{
			perror("unlink");
			exit(EXIT_FAILURE);
		}
	}
}

void	hiddenfile_history(char **keep)
{
	int	fd;
	int	counter;

	counter = -1;
	fd = open(".minihist", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (keep[++counter])
		ft_putendl_fd(keep[counter], fd);
	close(fd);
}

// void handle_input(char *line)
// {
// 	char	**cmd;
// 	char	*path;
// 	char	*quotes;
//     // printf("You entered: %s\n", line);
// 	// here we need to parse.
// 	if (!(check_empty_line(line)))
// 		return;
// 	quotes = to_trim_quotes(line, 34);
// 	if (quotes)
// 	{
// 		printf("%s\n", quotes);
// 		free (quotes);
// 	}
// 	// here we finish parse.
// 	cmd = ft_split(line, 32);
// 	if (ft_strncmp(line, "pwd", 3) == 0)
// 		this_folder_is(0);
// 	if (ft_strncmp(line, "cd", 2) == 0)
// 		cd_command(line);
// 	path = find_path(cmd[0]); // finds the path to the cmd
// 	if (!path)
// 		bad_cmd(path, cmd);
// 	else
// 		execute(path, cmd); // forks to execute and frees everything 
// 	// so far this is only good for single commands.
// }

