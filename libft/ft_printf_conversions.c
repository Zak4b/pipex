/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:46:49 by asene             #+#    #+#             */
/*   Updated: 2024/11/15 11:12:39 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_puthex(unsigned long n, char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_printf_puthex(n / 16, base);
	count += ft_printf_putchar(base[n % 16]);
	return (count);
}

int	ft_printf_putnbr(int nb)
{
	int		count;
	long	nbr;

	count = 0;
	nbr = nb;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
		count += ft_printf_putnbr(nbr / 10);
	count += ft_printf_putchar(nbr % 10 + '0');
	return (count);
}

int	ft_printf_putnbru(unsigned int nb)
{
	int				count;

	count = 0;
	if (nb >= 10)
		count += ft_printf_putnbru(nb / 10);
	count += ft_printf_putchar(nb % 10 + '0');
	return (count);
}
