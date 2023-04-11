/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:56:55 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 13:20:59 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_placeholder(char c, va_list args, int len);
int			ft_voidptr(unsigned long int arg, char *base);
int			ft_putunsigned(unsigned int nb);
int			ft_puthex(unsigned int nb, char *base);

int	ft_printf(const char *input, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%' && input[i])
		{
			len = ft_placeholder(input[i + 1], args, len);
			i++;
		}
		else
			len += write(1, &input[i], 1);
		i++;
	}	
	va_end(args);
	return (len);
}

static int	ft_placeholder(char c, va_list args, int len)
{
	if (c == 'c')
		len += ft_putchar_fd(va_arg(args, int), 1);
	if (c == 's')
		len += ft_putstr_fd(va_arg(args, char *), 1);
	if (c == 'd' || c == 'i')
		len += ft_putnbr_fd(va_arg(args, int), 1);
	if (c == 'p')
		len += ft_voidptr(va_arg(args, unsigned long int), "0123456789abcdef");
	if (c == 'u')
		len += ft_putunsigned(va_arg(args, unsigned int));
	if (c == 'x')
		len += ft_puthex(va_arg(args, unsigned int), "0123456789abcdef");
	if (c == 'X')
		len += ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		len += ft_putchar_fd('%', 1);
	return (len);
}

int	ft_puthex(unsigned int nb, char *base)
{
	int	len;

	len = 0;
	if (nb > 15)
		len += ft_puthex(nb / 16, base);
	len += write(1, &base[nb % 16], 1);
	return (len);
}

int	ft_putunsigned(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
		len += ft_putnbr_fd((nb / 10), 1);
	len += ft_putchar_fd((nb % 10 + 48), 1);
	return (len);
}

int	ft_voidptr(unsigned long int arg, char *base)
{
	int	len;

	len = 0;
	if (!arg)
		return (write(1, "(nil)", 5));
	if (arg > 15)
		len += ft_voidptr(arg / 16, base);
	if (len == 0)
		len += write(1, "0x", 2);
	len += write(1, &base[arg % 16], 1);
	return (len);
}
/* int main()
{
	char str[] = "";

	int a = ft_printf("%s\n", *str);
	int b = printf("%c\n", *str);
	printf("%d\n", a);
	printf("%d\n", b);
} */