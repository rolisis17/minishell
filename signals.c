/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:02 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/10 11:48:40 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		if (g_glob.here_flag == 1)
			g_glob.exit_status = 130;
		else
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
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_glob.exit_status = 130;
	}
}

void	here_child_exit(int signum)
{
	if (signum == SIGINT)
	{
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
	exit (g_glob.exit_status);
}
