/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 06:48:55 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/16 12:10:36 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_split(char **split, char *new)
{
	int		i;
	int		len;
	char	**new_split;

	if (split[0] == NULL)
		return (ft_split(new, 32));
	new_split = (char **) ft_calloc(sizeof(char *), (word_count(split) + 2));
	if (!new_split)
		return (0);
	i = -1;
	while (split[++i])
	{
		len = ft_strlen(split[i]);
		new_split[i] = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(new_split[i], split[i], len + 1);
	}
	len = ft_strlen(new);
	new_split[i] = ft_calloc(len + 1, sizeof(char));
	if (!new_split[i])
		return (0);
	if (len > 0)
		ft_strlcpy(new_split[i], new, len + 1);
	new_split[++i] = NULL;
	split = freedom("s", split);
	return (new_split);
}

char	**copy_split(char **split, int arg)
{
	int		i;
	int		len;
	char	**new_split;

	i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * (i + 1));
	if (!new_split)
		return (0);
	i = -1;
	while (split[++i])
	{
		len = ft_strlen(split[i]);
		new_split[i] = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(new_split[i], split[i], len + 1);
	}
	new_split[i] = NULL;
	if (!arg)
		freesplit(split);
	return (new_split);
}

char	**remove_split(char **split, char *rem, int arg)
{
	int		i;
	int		f;
	int		len;
	char	**new_split;

	i = word_count(split);
	new_split = (char **) malloc(sizeof(char *) * i);
	if (!new_split)
		return (0);
	i = -1;
	f = -1;
	while (split[++i])
	{
		if ((ft_strncmp(split[i], rem, ft_strlen(rem)) != 0))
		{
			len = ft_strlen(split[i]);
			new_split[++f] = ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(new_split[f], split[i], len + 1);
		}
	}
	new_split[++f] = NULL;
	if (!arg)
		freesplit(split);
	return (new_split);
}

char	**modify_split(char **split, char *mod, int arg, int flag)
{
	int		i;
	int		len;
	char	**new_split;

	if (!mod)
		return (split);
	i = word_count(split);
	new_split = (char **) ft_calloc(sizeof(char *), i + 1);
	if (!new_split)
		return (0);
	i = -1;
	while (split[++i])
	{
		if ((ft_strncmp(split[i], mod, strintchr(mod, flag) - 1) != 0))
		{
			len = ft_strlen(split[i]);
			new_split[i] = ft_calloc(len + 1, sizeof(char));
			ft_strlcpy(new_split[i], split[i], len + 1);
		}
		else
			new_split[i] = ft_strdup(mod);
	}
	if (!arg)
		freesplit(split);
	return (new_split);
}

char	**merge_split(char **og, char **new)
{
	int		len;
	int		word;
	int		i;
	char	**res;

	i = -1;
	len = word_count(og) + word_count(new);
	res = (char **) malloc(sizeof(char *) * (len + 1));
	while (og[++i])
	{
		word = ft_strlen(og[i]);
		res[i] = ft_calloc(word + 1, sizeof(char));
		ft_strlcpy(res[i], og[i], word + 1);
	}
	len = 0;
	while (new[len])
	{
		word = ft_strlen(new[len]);
		res[i] = ft_calloc(word + 1, sizeof(char));
		ft_strlcpy(res[i++], new[len++], word + 1);
	}
	res[i] = NULL;
	og = freedom("ss", og, new);
	return (res);
}

// char	**split_init(char *new)
// {
	
// }