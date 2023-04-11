/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:03:10 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 16:43:21 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_start(char const *str, char const *set)
{
	int	i;
	int	i2;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		i2 = 0;
		while (set[i2])
		{
			if (str[i] == set[i2])
			{
				res += 1;
				break ;
			}
		i2++;
		}
		if (res <= i)
			break ;
		i++;
	}
	return (res);
}

static int	check_end(char const *str, char const *set)
{
	int		i;
	int		i2;
	size_t	res;

	i = 0;
	i = ft_strlen(str) - 1;
	res = 0;
	while (i > 0)
	{
		i2 = 0;
		while (set[i2])
		{
			if (str[i] == set[i2])
			{
				res += 1;
				break ;
			}
			i2++;
		}
		if (res <= (ft_strlen(str) - 1 - i))
			break ;
		i--;
	}
	return (res);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		i;
	char	*res;
	int		len;
	size_t	start;

	i = 0;
	start = check_start(str, set);
	len = (ft_strlen(str) - start - check_end(str, set));
	if (start == ft_strlen(str))
	{
		res = (char *)malloc(sizeof(char));
		if (!res)
			return (0);
		res[0] = '\0';
		return (res);
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i != len)
		res[i++] = str[start++];
	res[i] = '\0';
	return (res);
}

/* int main()
{
    char str[] = "";
    char set[] = "";

    printf("Start: %i\n", check_start(str, set));
    printf("End: %i\n", check_end(str, set));
    printf("String: $%s$\n", ft_strtrim(str, set));
} */
