/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:13:44 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:17:15 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;

	ptr = malloc(ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	ptr = ft_memcpy(ptr, str, ft_strlen(str) + 1);
	return (ptr);
}

/* int main()
{
    char str[] = "lorem ipsum dolor sit amet";
    
    printf("%s", ft_strdup(str));
} */
