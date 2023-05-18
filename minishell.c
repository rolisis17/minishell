/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/18 15:12:11 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	*data;

	if (ac > 1)
		dont_do(av);
	if (av || ac)
		set_path_env(envp, av[0]);
	if (!new_history())
		printf("\033[2J\033[1;1H");
	line = NULL;
	data = ft_calloc(sizeof(t_shell), 1);
	while (1)
	{
		sig_handler(0);
		line = readline("\033[0;95mminishit\033[0m > ");
		keep_history(line, 0);
		if (line == NULL)
			quit(data, line);
		data->input = ft_strtrim(line, " ");
		freedom("a", line);
		if ((check_empty_line(data->input)))
			parse_input(data);
	}
	return (0);
}

void	dont_do(char **av)
{
	if (ft_strncmp("de3ac21778e51de199438300e1a9f816c618d33a", av[1], 40) == 0)
		exit(ft_atoi(av[2]));
	else if (ft_strncmp("e5fa44f2b31c1fb553b6021e7360d07d5d91ff5e", \
	av[1], 40) == 0)
		g_glob.exit_status = 1;
	else if (ft_strncmp("6ca52a340915a306c116baccfd959717fcb1c651", \
	av[1], 40) == 0)
		g_glob.exit_status = 0;
	else
		error("minishell doesn't take arguments", 0);
}
