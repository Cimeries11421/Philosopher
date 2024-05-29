/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:49:04 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 22:44:56 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*s2;

	len_s = ft_strlen(s);
	s2 = malloc((len_s + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	i = 0;
	while (*s)
	{
		s2[i] = f(i, *s);
		i++;
		s++;
	}
	s2[i] = '\0';
	return (s2);
}
