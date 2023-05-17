/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:06:32 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/17 11:07:11 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	keep_history(char *line, int check)
{
	static char	**keep;

	if (!check)
	{
		if (!keep)
			keep = ft_split(line, 02);
		else
			keep = add_split(keep, line);
		add_history(line);
	}
	if (ft_strncmp(line, "exit", 4) == 0 || check == 2)
	{
		keep = freedom("s", keep);
		rl_clear_history();
		return ;
	}
	if (check && keep)
		hiddenfile_history(keep);
}

int	new_history(void)
{
	char	*hist;
	int		fd;

	hist = NULL;
	fd = 0;
	if (g_glob.kurva)
	{
		hist = ft_strdup(g_glob.kurva);
		hist = prev_folder(hist, 1);
		hist = ft_strjoin_mod(hist, ".minihist", 0);
		if (access(hist, F_OK) == 0)
		{
			new_history_2(hist);
			if (unlink(hist) == -1)
			{
				perror("unlink");
				freedom("a", hist);
				exit(EXIT_FAILURE);
			}
			fd = 600;
		}
	}
	freedom("a", hist);
	return (fd);
}

void	new_history_2(char *hist)
{
	char	*gnl;
	char	*res;
	int		fd;

	fd = open(hist, O_RDWR);
	if (fd < 0)
		error("Error", 1);
	gnl = get_next_line(fd);
	while (gnl)
	{
		res = ft_strtrim(gnl, "\n");
		keep_history(res, 0);
		freedom ("aa", res, gnl);
		gnl = get_next_line(fd);
	}
	freedom("a", gnl);
	close (fd);
}

void	hiddenfile_history(char **keep)
{
	int		fd;
	int		counter;
	char	*hist;

	counter = -1;
	if (g_glob.kurva)
	{
		hist = ft_strdup(g_glob.kurva);
		hist = prev_folder(hist, 1);
		hist = ft_strjoin_mod(hist, ".minihist", 0);
		fd = open(hist, O_RDWR | O_CREAT | O_TRUNC, 0777);
		while (keep[++counter])
			ft_putendl_fd(keep[counter], fd);
		close(fd);
		keep = freedom ("sa", keep, hist);
	}
}
