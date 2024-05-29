/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:52:34 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/26 17:40:47 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(long n)
{
	size_t	len;

	len = 1;
	len += (n < 0);
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*fill_s(long n, char *s, size_t len)
{
	size_t	j;
	int		sign;

	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	j = len;
	while (j > 0)
	{
		j--;
		s[j] = (n % 10 + 48);
		n /= 10;
	}
	s[len] = '\0';
	if (sign)
		s[0] = '-';
	return (s);
}

char	*ft_itoa(int nb)
{
	size_t	len;
	char	*s;
	long	n;

	n = (long)nb;
	if (n == 0)
	{
		s = malloc(2 * sizeof(char));
		if (!s)
			return (NULL);
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	len = count_digit(n);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	return (fill_s(n, s, len));
}
