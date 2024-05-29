/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:49:45 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 22:07:00 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s);
	while (ft_strchr(set, s[i]))
		i++;
	while (j > i && (ft_strchr(set, s[j - 1])))
		j--;
	return (ft_substr(s, i, j - i));
}
