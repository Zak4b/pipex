/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:15:58 by asene             #+#    #+#             */
/*   Updated: 2024/11/15 11:12:38 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_printf_putstr(char *str)
{
	int	i;

	if (str == NULL)
		return (ft_printf_putstr("(null)"));
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
}

int	ft_printf_put_pointer(void *adress)
{
	if (adress == NULL)
		return (ft_printf_putstr("(nil)"));
	ft_printf_putstr("0x");
	return (2 + ft_printf_puthex((unsigned long)adress, HEX_BASE_LOWER));
}
