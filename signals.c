/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:02 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/04 15:44:25 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// these are fucked.. need to reset 
void    sig_handler(void)
{
    signal(SIGINT, ctrlc);
    signal(SIGQUIT, SIG_IGN);
}

void    ctrlc(int signum)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    signal(signum, ctrlc);
}

void    quit(char *str)
{
    free(str);
	write(1, "exit\n", 5);
    exit (EXIT_SUCCESS);
}
