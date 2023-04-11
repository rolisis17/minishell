/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:39:24 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:20:02 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	len = ft_strlen(dest);
	destlen = len;
	srclen = ft_strlen(src);
	if ((destlen >= size) || (size == 0))
	{
		return (srclen + size);
	}
	while (src[i])
	{
		if (i < size - destlen - 1)
		{
			dest[len] = src[i];
			len++;
		}
		i++;
	}
	dest[len] = '\0';
	return (destlen + i);
}

/* int main()
{
	char dest[] = "abxcthftn";
	char src[] = "lorem i";
    size_t num = 3;

	printf("The func: %ld\n", ft_strlcat(dest, src, num));
	printf("Dest: %s\n", dest);
	printf("My func: %ld\n", strlcat(dest, src, num));
	printf("Dest: %s\n", dest);
} */
