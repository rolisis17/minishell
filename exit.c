/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/16 21:10:49 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *data)
{
	data->len = 0;
	if (!data->cmd[1])
	{
		freedom("d", data);
		quit(data, NULL);
	}
	while (data->cmd[1][data->len])
	{
		if (ft_isdigit(data->cmd[1][data->len]) == 0)
		{
			write(1, "exit\n", 5);
			ft_putendl_fd("exit: numeric argument required", 2);
			keep_history(NULL, 2);
			data = freedom("da", data, data);
			exiting(2);
			// exit(0);
		}
		data->len++;
	}
	ft_exit_part2(data);
}

void	ft_exit_part2(t_shell *data)
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
	data = freedom("da", data, data);
	keep_history(NULL, 2);
	write(1, "exit\n", 5);
	// exit (g_glob.exit_status % 255);
	exiting(g_glob.exit_status % 255);
}

void	quit(t_shell *data, char *str)
{
	data = freedom("aa", data, str);
	write(1, "exit\n", 5);
		g_glob.exit_status = EXIT_SUCCESS;
	keep_history(NULL, 2);
	// exit (g_glob.exit_status);
	exiting(g_glob.exit_status % 255);
}

void	exiting(int arg)
{
	char *exit[4];
	
	exit[0] = "";
	exit[1] = "de3ac21778e51de199438300e1a9f816c618d33a";
	if (arg != 0)
		exit[2] = ft_itoa(arg);
	else 
		exit[2] = ft_itoa(0);
	exit[3] = NULL;

	execve(g_glob.kurva, exit, g_glob.environ);
}