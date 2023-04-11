/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:23:24 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:26:16 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (start >= ft_strlen(str))
	{
		subs = ft_calloc(sizeof(char), 1);
		return (subs);
	}
	if (len >= ft_strlen(str))
		len = ft_strlen(str) - start;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	while (start < ft_strlen(str) && i < len)
		subs[i++] = str[start++];
	subs[i] = '\0';
	return (subs);
}

/* int main()
{
    char str[] = "0123456789";
	char *ret;
	
	ret = ft_substr(str, 9, 10);
	if (!strcmp(ret, "9"))
		printf("wtv\n");
	printf("%s\n", ret);
	free(ret);
	return (0);
} */