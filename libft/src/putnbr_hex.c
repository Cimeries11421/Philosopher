/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:43:59 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 17:44:23 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	putnbr_hex(unsigned int nb, char *base, int *count)
{
	if (nb >= 16)
	{
		if (putnbr_hex(nb / 16, base, count) == -1)
			return (-1);
	}
	if (ft_putchar(base[nb % 16], count) == -1)
		return (-1);
	return (0);
}
