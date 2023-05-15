/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:02 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/15 16:38:18 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int arg)
{
	if (arg == 0)
	{
		signal(SIGINT, ctrlc);
		signal(SIGQUIT, SIG_IGN);	
	}
	else if (arg == 1)
	{
		signal(SIGINT, interupt);
    	signal(SIGQUIT, interupt);
	}
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
	if (signum == SIGQUIT)
	{
		g_glob.exit_status = 131;
		printf("Quit\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	child_quit(int signum)
{
	if (signum == SIGINT)
	{
		g_glob.exit_status = 131;
		printf("\n");
		exit(131);
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
