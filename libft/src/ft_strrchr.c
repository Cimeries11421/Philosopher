/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:50:10 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 22:12:16 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	while (i > 0 && s[i] != (unsigned char)c)
		i--;
	if (i == 0 && s[i] != (unsigned char)c)
		return (NULL);
	return ((char *)s + i);
}
