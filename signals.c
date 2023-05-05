/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:02 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/05 15:57:43 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob;

void    sig_handler(void)
{
    signal(SIGINT, ctrlc);
    signal(SIGQUIT, SIG_IGN);
}

void    ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	interupt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	here_exit(int signum)
{
	if (signum == SIGINT)
	{
		g_glob.here_flag = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
	}
}

void    quit(char *str)
{
    free(str);
	write(1, "exit\n", 5);
    exit (EXIT_SUCCESS);
}
