/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:58:10 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/26 17:01:48 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_quote(char c)
{
	return (c == "\"" || c == "\'");
}


void	create_cmd(struct, char *line, int i, char set)
{
	if(!set && is_quote(line[i]))
		set = 1;
	else if (set && is_quote(line[i]))
		set = 0;
	else if (!set && is_separator(line[i]))
	{
		
	}
	
}