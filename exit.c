/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/05/14 17:34:26 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *data, char *input) // test what exit does in pipes ...
{
	data->len = 0;
	if (!data->cmd[1])
	{
		freedom("saa", data->cmd, input, data);
		quit(NULL);
	}
	while (data->cmd[1][data->len])
	{
		if (ft_isdigit(data->cmd[1][data->len]) == 0)
		{
			write(1, "exit\n", 5);
			ft_putendl_fd("exit: numeric argument required", 2); 
			freedom("saa", data->cmd, input, data);
    		exit (0);
		}
		data->len++;
	}
	if (data->cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return ; // find right error code and add to exit status
	}
	if (data->cmd[1])
		g_glob.exit_status = ft_atoi(data->cmd[1]);
	else
		g_glob.exit_status = EXIT_SUCCESS;
	freedom("saa", data->cmd, input, data);
	write(1, "exit\n", 5);
	rl_clear_history();
    exit (g_glob.exit_status%255);
}

// int	exit_error(char *str, int check) // not used
// {
// 	static int	exit;

// 	if (check)
// 		return (exit);
// 	if (ft_strncmp("cd", str, 2) == 0)
// 		exit = 126;
// 	return (0);
// }
