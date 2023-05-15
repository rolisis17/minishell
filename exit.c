/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/15 17:54:40 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *data, char *input) // test what exit does in pipes ...
{
	data->len = 0;
	if (!data->cmd[1])
	{
		freedom("da", data, input);
		quit(NULL);
	}
	while (data->cmd[1][data->len])
	{
		if (ft_isdigit(data->cmd[1][data->len]) == 0)
		{
			write(1, "exit\n", 5);
			ft_putendl_fd("exit: numeric argument required", 2); 
			freedom("da", data, input);
			rl_clear_history();
    		exit (0);
		}
		data->len++;
	}
	ft_exit_part2(data, input);
}

void	ft_exit_part2(t_shell *data, char *input)
{
	if (data->cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_glob.exit_status = 1;
		return ;
	}
	if (data->cmd[1])
		g_glob.exit_status = ft_atoi(data->cmd[1]);
	else
		g_glob.exit_status = EXIT_SUCCESS;
	freedom("ad", input, data);
	write(1, "exit\n", 5);
	rl_clear_history();
    exit (g_glob.exit_status % 255);
}

void	quit(char *str)
{
	if (str)
		free(str);
	write(1, "exit\n", 5);
		g_glob.exit_status = EXIT_SUCCESS;
	rl_clear_history();
	exit (g_glob.exit_status);
}
