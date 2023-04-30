/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:43:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/30 19:54:38 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_new(t_shell *data, char *new)
{
	int	i;
	
	i = 0;
	data->res = NULL;
	while(new[i] && new[i] != '|' && new[i] != '<' && new[i] != '>' && new[i] != 32)
	{
		if (new[i] == 34 || new[i] == 39)
			i += quote_new(data, new + i);
		else if (new[i] == 36)
			i += env_var_new(data, new + i);
		else
			data->res = char_join(data->res, new[i++]);
	}
	if (data->cmd)
		data->cmd = add_split(data->cmd, data->res);
	else if (ft_strlen(data->res) == 0)
		error("Command '' not found", 1); // need to figure out a way to send '' this to command because it will so the error for me
	else
		data->cmd = ft_split(data->res, 32);
	if (data->res)
		free(data->res);
	return (i - 1);
}

int	quote_new(t_shell *data, char *new)
{
	char	*ptr;
	char	*temp;
	
	ptr = ft_strchr(new + 1, new[0]);
	if (ptr == NULL || new[1] == '\0')
	{
		data->res = ft_strjoin_mod(data->res, new, 0);
		return(ft_strlen(new));
	}
	printf("LEN:%li\n", ptr - new);
	temp = ft_substr(new, 1, ptr - new - 1); // LEEAAAAAAK!!
	data->len = ft_strlen(temp);
	printf("THERE:%s:%i\n", temp, data->len);
	check_substr_new(data, temp, new[0]);
	return(data->len + 2); // check return is correct amount
}

int	env_var_new(t_shell *data, char *new)
{
	char	*var;
	char	*res;
	int		var_len;
	
	var_len = get_cmd(new, 0);
	var = ft_substr(new, 1, var_len - 1);
	res = getenv(var);
	if (res == NULL)
	{
		free(var);
		return(var_len);
	}
	// printf("HERE:%s\n", var);
	data->res =  ft_strjoin_mod(data->res, res, 0);
	free(var);
	return(var_len);
}

void	check_substr_new(t_shell *data, char *new, char c)
{
	char	*beg;
	int		len;

	if (c == 39)
	{
		data->res = ft_strjoin_mod(data->res, new, 0);
		return ;
	}
	len = ft_strlen(new);
	while(ft_strchr(new, 36) != NULL)
	{
		beg = NULL;
		if (new[0] != 36)
		{
			beg = ft_strchr(new, 36);
			beg = ft_substr(new, 0, len - ft_strlen(beg));
		}
		new = env_var(new, len, beg); // might need to add a strjoin here. test $something$something
	}
	if (len != 0)
		data->res = ft_strjoin_mod(data->res, new, 0);
	free(new);
}