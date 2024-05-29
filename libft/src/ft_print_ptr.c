/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:34:05 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 17:36:50 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	print_hex(unsigned long nb, char *base, int *count)
{
	if (nb >= 16)
	{
		if (print_hex(nb / 16, base, count) == -1)
			return (-1);
	}
	if (ft_putchar(base[nb % 16], count) == -1)
		return (-1);
	return (0);
}

ssize_t	ft_print_ptr(unsigned long nb, char *base, int *count)
{
	if (!nb)
	{
		if (ft_putstr("(nil)", count) == -1)
			return (-1);
		return (0);
	}
	if (ft_putstr("0x", count))
		return (-1);
	return (print_hex(nb, base, count));
}
