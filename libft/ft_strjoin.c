/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:22:49 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/14 16:49:52 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int f)
{
	int		u;
	int		c;
	char	*s3;

	u = ft_strlen(s1) + ft_strlen(s2);
	if (f == -1)
		u -= ft_strlen(s1);
	s3 = (char *)ft_calloc(u + 1, sizeof(char));
	if (!s3)
		return (NULL);
	c = -1;
	if (s1 && f != -1)
		while (s1[++c] && (c < u))
			s3[c] = s1[c];
	else
		c = 0;
	u = -1;
	while (s2[++u])
		s3[c + u] = s2[u];
	if (f == -2)
		if (s1)
			free (s1);
	return (s3);
}

// char	*ft_strjoin(char const *str1, char const *str2)
// {
// 	int		len;
// 	char	*res;
// 	int		i;
// 	int		i2;

// 	i = 0;
// 	len = (ft_strlen(str1) + ft_strlen(str2));
// 	res = ft_calloc(sizeof(char), (len + 1));
// 	if (!res)
// 		return (NULL);
// 	while (str1[i])
// 	{
// 		res[i] = str1[i];
// 		i++;
// 	}
// 	i2 = 0;
// 	while (str2[i2])
// 	{
// 		res[i + i2] = str2[i2];
// 		i2++;
// 	}
// 	return (res);
// }

/* int main()
{
    const char str[] = "Marcell";
    const char str2[] = "Stiedl";
    
    printf("%s", ft_strjoin(str, str2));
} */
