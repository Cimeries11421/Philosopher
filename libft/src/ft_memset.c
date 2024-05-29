/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:12:45 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 18:08:33 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *start, int value, size_t n)
{
	char	*str;

	str = start;
	while (n)
	{
		*str = value;
		str++;
		n--;
	}
	return (start);
}
