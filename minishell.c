/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:28:58 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/11 17:02:54 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *input;
	
	ft_printf("\033[2J\033[1;1H");
	while(1)
	{
		ft_printf("$ ");
		input = get_next_line(STDIN_FILENO);
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free (input);
			exit(0);
		}
		free (input);
	}
}