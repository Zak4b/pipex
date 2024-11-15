/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:46:23 by asene             #+#    #+#             */
/*   Updated: 2024/11/15 11:10:47 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"

int	ft_printf_putchar(char c);
int	ft_printf_putstr(char *str);
int	ft_printf_putnbr(int nb);
int	ft_printf_putnbru(unsigned int nb);
int	ft_printf_puthex(unsigned long n, char *base);
int	ft_printf_put_pointer(void *adress);

#endif