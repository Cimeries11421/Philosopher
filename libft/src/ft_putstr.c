/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:40:32 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 21:03:49 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putstr(const char *s, int *count)
{
	size_t	i;

	if (!s)
	{
		if (ft_putstr("(null)", count) == -1)
			return (-1);
		return (0);
	}
	i = 0;
	while (s[i])
	{
		if (write(1, s + i, 1) == -1)
			return (-1);
		i++;
	}
	*count += (int)i;
	return (0);
}
