/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:38 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/08 08:15:32 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freelist(t_store *list)
{
	t_store	*temp;
	
	while(list)
	{
		temp = list;
		list = list->next;
		if (temp->content)
			free(temp->content);
		if (temp->name)
			free(temp->name);
		free(temp);
	}
	list = NULL;
}

void	free_check(void *freeable)
{
	if (freeable)
	{
		free(freeable);
		freeable = NULL;
	}
}

void	freesplit(char **splited)
{
	int	counter;

	counter = 0;
	if (!splited)
		return ;
	while (splited[counter])
	{
		free(splited[counter]);
		counter++;
	}
	free (splited);
	splited = NULL;
}

void	*freedom(const char *str, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == 's')
			freesplit(va_arg(args, char **));
		else if (str[i] == 'l')
			freelist(va_arg(args, t_store *));
		else if (str[i] == 'a')
			free_check(va_arg(args, void *));
		i++;
	}
	va_end(args);
	return (NULL);
}