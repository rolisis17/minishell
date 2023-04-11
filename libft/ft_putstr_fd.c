/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:04:59 by mstiedl           #+#    #+#             */
/*   Updated: 2022/12/29 12:24:24 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[i])
	{
		len += write(fd, &str[i], 1);
		i++;
	}
	return (len);
}

/* int main()
{
    ft_putstr_fd(NULL, 1);
} */