/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/13 20:48:08 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_line(char *line)
{
	int	f;

	f = -1;
	while (line[++f])
	{
		if (line[f] != '\n' && line[f] != 32 && line[f] != '.')
			return (1);
	}
	return (0);
}

char	*to_trim_quotes(char *str, int quote)
{
	char	*trimmed;
	int		end;
	int		start;
	int		u;
	// 34 == "
	// 36 == $
	// 39 == '

	trimmed = NULL;
	start = searchforquotes(str, quote, 1);
	end = searchforquotes(str, quote, 2);
	u = -1;
	if (searchforquotes(str, quote, 0) > 1)
	{
		trimmed = ft_calloc(end - start + 1, sizeof(char));
		while (start < end)
		{
			trimmed[++u] = str[start];
			start++;
		}
	}
	return (trimmed);
}

int	searchforquotes(char *str, int quote, int start)
{
	int	f;
	int	counter;

	f = 0;
	counter = 0;
	while (str[f])
	{
		if (str[f] == quote)
			counter++;
		if ((start == 2 && counter == 2))
			return (f);
		f++;
		if (start == 1 && counter == 1)
			return (f);
	}
	// if (start == 2)
	// 	return (0);
	return (counter);
}

void	error_func2(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(-1);
}

char **parse_tree(char *input)
{
	t_tree	*tree;
	
	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->data = input; // does this shit work??
	check_all(tree);
}

void	check_all(t_tree *trunk)
{
	char	*finder;

	finder = ft_strchr(trunk->data, 39);
	if (finder != NULL)
	{
		finder = ft_strchr(finder, 39);
		if (finder != NULL)
		{
			trunk->right = make_right(trunk->data, finder); // with new tree
			trunk->left = make_left(finder);// make branch, check if its not the end of the string
			return ;
		}
		
	}
}

t_tree	*make_right(char *str, char *spliter)
{
	t_tree	*res;
	int		len;

	res = (t_tree *)malloc(sizeof(t_tree));
	len = spliter - str;
	// res->data = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(res->data, str, len);
}

t_tree	*make_left(char *str)
{
	t_tree	*res;
	
	if (str[1] == NULL)
		return (NULL);
	else
	{
		res = (t_tree *)malloc(sizeof(t_tree));
		res->data = str;
	}
	return (res);
}
