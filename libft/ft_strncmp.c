/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:11:06 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/04 15:12:02 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strncmp(const char *str1, const char *str2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (str1[i] && i < n - 1)
// 	{
// 		if (str1[i] != str2[i])
// 			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
// 		i++;
// 	}
// 	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
// }

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
}

/* int main()
{
	char str1[] = "test\200";
	char str2[] = "test\0";

	printf("My func = %i\n", ft_strncmp(str1, str2, 6));
	printf("The func = %i\n", strncmp(str1, str2, 6));
} */
