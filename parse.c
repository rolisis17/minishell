/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:19:54 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/18 17:17:46 by mstiedl          ###   ########.fr       */
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

// char	**break_qtes(t_shell *data, char *new)
// {
//     char *start;
//     char *end;
//     char **split;
//     int i = 0;

// 	split = (char **) malloc(sizeof(char *) * (word_count(str, 39) + 1));
//     printf("%s\n", str);
//     while(1)
//     {    
//         start = ft_strchr(str, 39);
//         if (start != NULL)
//             end = ft_strchr(start + 1, 39);
//         if (start == NULL || end == NULL)
//         {
//             split[i++] = ft_substr(str, 0, ft_strlen(str));
//             break;
//         }
//         else if (str[0] != 39 && end != NULL)
//         {
//             split[i++] = ft_substr(str, 0, start - str); // maybe -1
//             str = start;
//         }
//         else
//         {
//             split[i++] = ft_substr(str, 0, end - start + 1);
//             str = end + 1;
//         }
//     }
//     split[i] = NULL;
// 	return (split);
// }