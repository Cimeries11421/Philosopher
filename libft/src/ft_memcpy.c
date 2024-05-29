/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:38:08 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 22:32:56 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*t1;
	const char	*t2;
	size_t		i;

	if (!dest && !src)
		return (0);
	t1 = (char *)dest;
	t2 = (char *)src;
	i = 0;
	while (i < n)
	{
		t1[i] = t2[i];
		i++;
	}
	return (dest);
}
