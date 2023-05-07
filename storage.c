/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:54:42 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/07 17:15:20 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_back(t_store **lst, t_store *new);


void	store_it(t_shell *data, int flag)
{
	t_store	*node;

	node = ft_calloc(1, sizeof(t_store));
	if (!node)
		return ; // probs need malloc error
	node->flag = flag;
	node->name = ft_strdup(data->res);
	add_back(&data->files, node);
}

static void	add_back(t_store **lst, t_store *new)
{
	t_store	*temp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	make_files(t_shell *data)
{
	t_store	*temp;
	int		fd;
	
	while(data->files)
	{
		temp = data->files;
		// printf("HERE\n");
		if (data->files->flag == 1)
			fd = open(data->files->name, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			fd = open(data->files->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror("Error");
		if (data->files->content != NULL)
		{
			ft_putstr_fd(data->files->content, fd);
			close(fd);
		}
		data->files = data->files->next;
		freedom("aaa", temp->name, temp->content, temp);
	}
}

void	get_content(t_shell *data)
{
	char	*buf;
	t_store	*last;

	last = list_last(data->files);
	buf = ft_calloc(2, sizeof(char));
	while (read(data->fd[0], buf, 1) > 0)
		last->content = ft_strjoin_mod(last->content, buf, 0);
	free(buf);
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
}

t_store	*list_last(t_store *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}