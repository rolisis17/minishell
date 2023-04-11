/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:38:45 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:23:32 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = ft_strlen(str);
	if (!str)
		return (0);
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			ptr = (char *)&str[i];
			return (ptr);
			break ;
		}
	i--;
	}
	return (NULL);
}

/* int main()
{
	char str[] = "";
	int c = '\0';

	printf("My func: %s\n", ft_strrchr(str, c));
	printf("The func: %s\n", strrchr(str, c));
}
 */