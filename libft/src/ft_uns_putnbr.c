/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:13:53 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 17:43:17 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_uns_putnbr(unsigned int nb, int *count)
{
	if (nb >= 10)
	{
		if (ft_uns_putnbr(nb / 10, count) == -1)
			return (-1);
	}
	if (ft_putchar(nb % 10 + '0', count) == -1)
		return (-1);
	return (0);
}
