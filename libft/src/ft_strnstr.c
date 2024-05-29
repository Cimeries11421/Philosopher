/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:42:22 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 22:03:49 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*l)
		return ((char *)b);
	j = 0;
	while (b[j] && j < len)
	{
		i = 0;
		if (b[j + i] == l[0])
		{
			while (l[i] && b[j + i] == l[i] && i + j < len)
			{
				i++;
			}
		}
		if (l[i] == '\0')
		{
			return ((char *)(b + j));
		}
		j++;
	}
	return (NULL);
}
