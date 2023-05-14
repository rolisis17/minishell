/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:02 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/14 17:40:29 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN); // should exit if line not empty
}

void	ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		g_glob.exit_status = 130;
		if (g_glob.here_flag != 1)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	interupt(int signum)
{
	if (signum == SIGINT)
	{
		g_glob.exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	here_child_exit(int signum)
{
	if (signum == SIGINT)
	{
		g_glob.exit_status = 130;
		printf("\n");
		exit(130);
	}
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
