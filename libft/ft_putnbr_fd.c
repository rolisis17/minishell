/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:37:44 by mstiedl           #+#    #+#             */
/*   Updated: 2023/03/30 10:35:11 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nb, int fd)
{
	int		len;
	long	i;

	len = 0;
	i = nb;
	if (i < 0)
	{
		len += write(fd, "-", 1);
		i *= -1;
	}
	if (i > 9)
		len += ft_putnbr_fd((i / 10), fd);
	len += ft_putchar_fd((i % 10 + 48), fd);
	return (len);
}

/* int main()
{
    ft_putnbr_fd(-2147483648LL, 2);
} */