/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:22:49 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:18:40 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		len;
	char	*res;
	int		i;
	int		i2;

	i = 0;
	len = (ft_strlen(str1) + ft_strlen(str2));
	res = ft_calloc(sizeof(char), (len + 1));
	if (!res)
		return (NULL);
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	i2 = 0;
	while (str2[i2])
	{
		res[i + i2] = str2[i2];
		i2++;
	}
	return (res);
}

/* int main()
{
    const char str[] = "Marcell";
    const char str2[] = "Stiedl";
    
    printf("%s", ft_strjoin(str, str2));
} */
