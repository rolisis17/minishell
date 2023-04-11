/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:08:15 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:16:13 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
			((unsigned char *)str)[i] = c;
			i++;
	}
	return (str);
}

/*int main()
{
	char str[] = {"This is string.h library function"};

	ft_memset(str, '$', 7);
	printf("%s", str);
}*/
