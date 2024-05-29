/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:01:04 by ebriere           #+#    #+#             */
/*   Updated: 2024/05/09 11:00:51 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup_n(const char *s, size_t *n)
{
	size_t		len_s;
	size_t		i;
	char		*s2;

	len_s = ft_strlen_n((char *)s, 1);
	s2 = malloc(len_s + 1 * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < len_s + 1)
	{
		s2[i] = s[i];
		i++;
		if (s2[i - 1] == '\n')
		{
			s2[i] = '\0';
			*n = ft_strlen_n((char *)s, 1);
			break ;
		}
	}
	return (s2);
}

void	*ft_memmove_gnl(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		i = n - 1;
		while (n--)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (n--)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	((char *)dest)[i] = '\0';
	return (dest);
}

size_t	ft_strlen_n(const char *s, int endcalc)
{
	size_t	i;
	char	c;

	if (endcalc == 1)
		c = '\n';
	else
		c = '\0';
	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (s[i] == '\n')
		return (i + 1);
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2, size_t *n, size_t len)
{
	char	*s3;
	size_t	i;

	if (!s1)
		return (ft_strdup_n(s2, n));
	i = 0;
	len = ft_strlen_n(s2, 1);
	s3 = malloc((ft_strlen_n(s1, 2) + ft_strlen_n(s2, 1) + 1) * sizeof(char));
	if (!s3)
		return (free(s1), NULL);
	while (s1[i++])
		s3[i - 1] = s1[i - 1];
	i--;
	while (*s2)
	{
		s3[i++] = *s2++;
		if (s3[i - 1] == '\n')
		{
			*n = len;
			break ;
		}
	}
	return (s3[i] = '\0', free(s1), s3);
}
