/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:58:44 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:12:21 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)str;
	while (i < n)
	{
		if ((unsigned char)temp[i] == (unsigned char)c)
		{
			return ((void *)&temp[i]);
		}
		i++;
	}
	return (NULL);
}

/*int main()
{
    //const char str[] = "bonjourno";
    //char *ret = ft_memchr(str, 'n', 2);
    //char *ret2 = memchr(str, 'n', 2);
    int tab[7] = {-49, 49, 1, -1, 0, -2, 2};

	printf("My func %s\n", (char *)ft_memchr(tab, -1, 7));
	printf("The func %s\n", (char *)memchr(tab, -1, 7));
	
 //   printf("My func: %s\n", ret);
//    printf("The func: %s", ret2);
}*/