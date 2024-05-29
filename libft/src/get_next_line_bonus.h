/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:59:26 by ebriere           #+#    #+#             */
/*   Updated: 2024/01/04 22:26:17 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1
# endif
# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2, size_t *n, size_t len);
size_t	ft_strlen_n(const char *str, int endcalc);
char	*ft_strdup_n(const char *s, size_t *n);
void	*ft_memmove_gnl(void *dest, const void *src, size_t n);

#endif
