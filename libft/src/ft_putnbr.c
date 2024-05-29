/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:38:03 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 17:39:22 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putnbr(int nb, int *count)
{
	if (nb == -2147483648)
	{
		if ((write(1, "-2147483648", 11)) == -1)
			return (-1);
		*count += 11;
		return (0);
	}
	if (nb < 0)
	{
		nb = -nb;
		if (ft_putchar('-', count) == -1)
			return (-1);
	}
	if (nb >= 10)
	{
		if (ft_putnbr(nb / 10, count) == -1)
			return (-1);
	}
	if (ft_putchar(nb % 10 + '0', count) == -1)
		return (-1);
	return (0);
}
