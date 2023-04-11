/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:22:51 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:15:53 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	if (!dest && !src)
		return (0);
	if (dest > src)
	{
		while (n != i)
		{
		((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
		n--;
		}
	}
	else
	{
		while (i != n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/* int main()
{
	char src[] = "ab";
	char dest[] = "ab";
	printf("%ld", (src - dest));
	printf("src = %s\n", src);
	printf("new dest = %s\n", dest);
	ft_memmove(dest, src, 5);
	printf("new dest = %s\n", dest);
	printf("src = %s\n", src);
} */