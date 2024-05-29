/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:34:16 by ebriere           #+#    #+#             */
/*   Updated: 2024/01/03 16:34:16 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clear_used(char *buff, size_t n, ssize_t	read_size)
{
	if (n < BUFFER_SIZE && read_size > 0)
	{
		ft_memmove_gnl(buff, buff + n, ft_strlen_n(buff + n, 2));
	}
	else
	{
		buff[0] = '\0';
	}
	return (buff);
}

char	*recover_line(char *buff, size_t *n, char	*tmp)
{
	if (buff[0] != '\0')
	{
		tmp = ft_strdup_n(buff, n);
		if (tmp == NULL)
			return (buff[0] = 0, NULL);
	}
	return (tmp);
}

char	*fill_buff(int fd, char *buff, size_t *n, ssize_t *read_size)
{
	char	*tmp;

	tmp = NULL;
	tmp = recover_line(buff, n, tmp);
	if (*n)
		return (tmp);
	*read_size = read(fd, buff, BUFFER_SIZE);
	if (*read_size == -1)
		return (buff[0] = 0, free(tmp), NULL);
	if (*read_size <= 0 && !tmp)
		return (buff[0] = 0, NULL);
	while (*read_size > 0)
	{
		buff[*read_size] = '\0';
		tmp = ft_strjoin_gnl(tmp, buff, n, 0);
		if (tmp == NULL)
			return (buff[0] = 0, NULL);
		if (*n != 0)
			break ;
		*read_size = read(fd, buff, BUFFER_SIZE);
		if (*read_size == -1)
			return (buff[0] = 0, free(tmp), NULL);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	size_t		n;
	static char	buff[BUFFER_SIZE + 1] = "\0";
	char		*line;
	ssize_t		read_size;

	n = 0;
	read_size = BUFFER_SIZE;
	line = fill_buff(fd, buff, &n, &read_size);
	clear_used(buff, n, read_size);
	return (line);
}
