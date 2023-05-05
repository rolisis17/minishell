/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/05 18:45:23 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ac, char **av, char **envp
int main()
{
    char *line;

	set_path_env();
	new_history();
	// ft_printf("\033[2J\033[1;1H");
	line = NULL;
    while (1)
	{
		sig_handler();
		line = readline("> ");
		keep_history(line, 0);
		if (line == NULL)
			quit(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			quit(line);
		if ((check_empty_line(line)))
        	parse_input(line);
		freedom(NULL, line, NULL, NULL);
    }
    return 0;
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
	char	*hist;
	int		fd;

	hist = NULL;
	if (getenv("CURVA"))
	{
		hist = ft_strdup(getenv("CURVA"));
		hist = prev_folder(hist, 1);
		hist = ft_strjoin_mod(hist, ".minihist", 0);
		if (access(hist, F_OK) == 0)
		{
			fd = open(hist, O_RDWR);
			gnl = get_next_line(fd);
			while (gnl)
			{
				res = ft_strtrim(gnl, "\n");
				keep_history(res, 0);
				freedom (NULL, res, gnl, NULL);
				gnl = get_next_line(fd);
			}
			if (gnl)
				free (gnl);
			close (fd);
			if (unlink(hist) == -1)
			{
				perror("unlink");
				if (hist)
					free (hist);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (hist)
		free (hist);
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

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] != '\n' && line[f] != 32 && line[f] != '.') // if its just a . should return an error
			return (1);
	}
	return (0);
}