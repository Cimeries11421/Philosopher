/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:37:50 by ebriere           #+#    #+#             */
/*   Updated: 2023/12/27 17:37:52 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putchar(char c, int *count)
{
	*count += 1;
	return (write(1, &c, 1));
}
/*void    main(void)
{	
	int	a = 0;
    printf("\ncount = %ld\n",ft_putchar('a', &a));
}*/