/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:32:32 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/25 17:59:03 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size < 1)
		return (len);
	while (src[i] && i != size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

/* int main()
{
	char dest[] = {"lorem ipsum"};
	char src[] = {"World"};

	//printf("%li\n", ft_strlcpy(dest, src, 0));
	printf("%li\n", strlcpy(dest, src, 0));
	printf("%s\n", dest);
	printf("%s\n", src);
} */
