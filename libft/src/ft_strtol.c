/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:44:43 by ebriere           #+#    #+#             */
/*   Updated: 2024/02/11 16:44:51 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long	ft_strtol(const char *p)
{
	long	nbr;
	int		i;
	int		signe;

	nbr = 0;
	i = 0;
	signe = 1;
	while ((p[i] >= 9 && p[i] <= 13) || p[i] == 32)
		i++;
	if (p[i] == '-' || p[i] == '+')
		if (p[i++] == '-')
			signe = -1;
	while (ft_isdigit(p[i]))
	{
		if (nbr != ((nbr * 10) + (p[i] - '0')) / 10)
		{
			if (signe == -1)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		nbr = (nbr * 10) + (p[i] - '0');
		i++;
	}
	return (nbr * signe);
}
