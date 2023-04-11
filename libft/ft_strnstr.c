/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:16:14 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:23:15 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	i2;

	i = 0;
	if (str2[0] == '\0')
		return ((char *)str1);
	while (i < n && str1[i])
	{
		i2 = 0;
		while (str2[i2] && (str1[i + i2] == str2[i2])
			&& (i + i2) < n && str1[i + i2])
		{
			i2++;
			if (str2[i2] == '\0')
				return ((char *)&str1[i]);
		}
		i++;
	}
	return (NULL);
}

/* int main()
{
    char str[] = "";
    char str2[] = "coucou";
    
   //	printf("The function: %s\n", strnstr(str, str2, 10));
    printf("My function: %s", ft_strnstr(str, str2, -1));
} */