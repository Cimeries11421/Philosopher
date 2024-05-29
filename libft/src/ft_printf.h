/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:46:45 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 17:49:03 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BASE16 "0123456789ABCDEF"
# define LOWER_BASE16 "0123456789abcdef"
# include <stdarg.h>
# include <unistd.h>

ssize_t	ft_putstr(const char *s, int *count);
ssize_t	ft_putchar(char c, int *count);
ssize_t	ft_putnbr(int nb, int *count);
ssize_t	ft_uns_putnbr(unsigned int nb, int *count);
size_t	ft_strlen(const char *s);
ssize_t	putnbr_hex(unsigned int nb, char *base, int *count);
ssize_t	ft_print_ptr(unsigned long nb, char *base, int *count);
int		ft_printf(const char *format, ...);

#endif