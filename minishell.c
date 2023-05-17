/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/17 18:02:52 by dcella-d         ###   ########.fr       */
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
		// ft_printf("\033[2J\033[1;1H");
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
	else
		error("minishell doesn't take arguments", 0);
}
