/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:47:54 by ilyanar           #+#    #+#             */
/*   Updated: 2023/11/22 17:52:50 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *nb)
{
	*nb += write(1, &c, 1);
}

void	printf_base_addr(unsigned long long int nb, char *base, int *n)
{
	unsigned long long int	len;

	len = ft_strlen(base);
	if (nb >= len)
	{
		printf_base_addr(nb / len, base, n);
		printf_base_addr(nb % len, base, n);
	}
	else
		ft_putchar(base[nb], n);
}

void	stlen(char *tab, int *nb, char c, const char *str)
{
	if (*str == 'c' || *str == '%')
	{
		if (write(1, &c, 1) > 0)
			*nb += 1;
		return ;
	}
	if (!tab)
	{
		*nb += write(1, "(null)", 6);
		return ;
	}
	while (*tab)
	{
		write(1, &(*tab), 1);
		tab++;
		*nb += 1;
	}
}

int	who_is_char(const char *str, va_list *args, int *nb)
{
	if (*str == 'c')
		stlen(0, nb, va_arg(*args, int), str);
	else if ((*str == 'i') || (*str == 'd'))
		ft_putnbr(va_arg(*args, int), nb);
	else if ((*str == 's'))
		stlen(va_arg(*args, char *), nb, 0, str);
	else if ((*str == 'u'))
		printf_base_addr(va_arg(*args, unsigned int), "0123456789", nb);
	else if ((*str == 'x'))
		printf_base_addr(va_arg(*args, unsigned int), "0123456789abcdef", nb);
	else if ((*str == 'X'))
		printf_base_addr(va_arg(*args, unsigned int), "0123456789ABCDEF", nb);
	else if ((*str == 'p'))
	{
		write(1, "0x", 2);
		*nb += 2;
		printf_base_addr(va_arg(*args, long long int), "0123456789abcdef", nb);
	}
	else if (*str == '%')
		stlen(0, nb, '%', str);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int		nb;
	va_list	args;

	nb = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			if ((who_is_char((str + 1), &args, &nb)) == 0)
				return (-1);
			str += 2;
		}
		else
		{
			write(1, &(*str), 1);
			nb++;
			str++;
		}
	}
	va_end(args);
	return (nb);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("byte_read ->_%d\n\n\n", printf("V-STRING ->_%%\n\n"));	
	printf("byte_read ->_%d\n\n", ft_printf("F-STRING ->_%%\n\n"));
}
*/
