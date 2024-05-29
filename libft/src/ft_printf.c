/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:49:48 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 18:01:12 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	c_format(const char *format, ssize_t i, va_list args, int *count)
{
	if (format[i] == 'c')
		return (ft_putchar(va_arg(args, int), count));
	if (format[i] == 's')
		return (ft_putstr(va_arg(args, char *), count));
	if (format[i] == 'd' || format[i] == 'i')
		return (ft_putnbr(va_arg(args, int), count));
	if (format[i] == 'u')
		return (ft_uns_putnbr(va_arg(args, unsigned int), count));
	if (format[i] == 'x')
		return (putnbr_hex(va_arg(args, unsigned long), LOWER_BASE16, count));
	if (format[i] == 'X')
		return (putnbr_hex(va_arg(args, unsigned long), BASE16, count));
	if (format[i] == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long), LOWER_BASE16, count));
	if (format[i] == '%')
		return (ft_putchar('%', count));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] != '%')
			if (ft_putchar(format[i], &count) == -1)
				return (-1);
		if (format[i] == '%')
		{
			i++;
			if (c_format(format, i, args, &count) == -1)
				return (-1);
		}
		i++;
	}
	va_end(args);
	return (count);
}
