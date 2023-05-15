/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:43:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/15 16:26:54 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var(t_shell *data, char *new)
{
	char	*var;
	char	*res;
	int		var_len;

	var = get_var(data, new);
	if (var == NULL)
		return(2);
	var_len = ft_strlen(var);
	if (ft_strncmp(var, "$", 2) == 0)
	{
		data->res = ft_strjoin_mod(data->res, var, 0);
		return (1);
	}
	res = getenv(var);
	if (res == NULL)
	{
		free(var);
		return (var_len + 1);
	}
	data->res = ft_strjoin_mod(data->res, res, 0);
	free(var);
	return (var_len + 1);
}

void	check_substr(t_shell *data, char *new, char c)
{
	int		len;

	len = 0;
	if (c == 39)
	{
		data->res = ft_strjoin_mod(data->res, new, 0);
		free(new);
		return ;
	}
	if (ft_strchr(new, 36) != NULL)
	{
		while (new[len])
		{
			if (new[len] == '$')
				len += env_var(data, new + len);
			else
			{
				data->res = char_join(data->res, new[len]);
				len++;
			}
		}
	}
	if (len == 0)
		data->res = ft_strjoin_mod(data->res, new, 0);
	free(new);
}

char	*remove_quotes(char *str, int qte, int arg, t_shell *data)
{
	char	*res;
	char	*ptr;
	char	*start;
	char	*end;

	ptr = str;
	res = NULL;
	start = ft_strchr(ptr, qte);
	while (start != NULL)
	{
		data->here_limiter = 1;
		end = ft_strchr(start + 1, qte);
		if (end)
			ptr = split_n_join(ft_substr(ptr, 0, end - ptr), NULL, qte);
		res = ft_strjoin_mod(res, ptr, 0);
		if (end)
			free(ptr);
		ptr = end + 1;
		start = ft_strchr(end, qte);
	}
	if (!res)
		res = ft_strdup(str);
	if (arg == 1)
		free(str);
	return (res);
}

char	*get_var(t_shell *data, char *str)
{
	int		f;
	char	*var;

	f = 0;
	if (str[1] == '?')
	{
		data->res = ft_strjoin_mod(data->res, \
		ft_itoa(g_glob.exit_status % 255), 0);
		return (NULL);
	}
	while (str[++f])
	{
		if (ft_isalnum(str[f]) == 0 && str[f] != 95)
			break;
	}
	if (f == 1)
		var = ft_substr(str, 0, f);
	else
		var = ft_substr(str, 1, f - 1);
	return (var);
}