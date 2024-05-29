/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:28:24 by ebriere           #+#    #+#             */
/*   Updated: 2023/11/27 15:22:53 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char *s, char c)
{
	size_t	i;
	size_t	wd;

	i = 0;
	wd = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wd++;
			while (s[i] != c && s[i])
			{
				i++;
			}
			i--;
		}
		i++;
	}
	return (wd);
}

static void	*free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**fill_tab(char const *s, char c, char **tab, size_t len)
{
	size_t	j;
	size_t	i;
	size_t	l;

	j = 0;
	i = 0;
	l = 0;
	while (j < len)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			l++;
			i++;
		}
		tab[j] = ft_substr((char *)s, i - l, l);
		if (tab[j] == NULL)
			return (free_tab(tab));
		l = 0;
		j++;
	}
	return (tab[j] = NULL, tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**tab;

	if (!s)
		return (NULL);
	len = count_words((char *)s, c);
	tab = malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (fill_tab(s, c, tab, len));
}
