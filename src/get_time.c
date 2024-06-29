/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:42:39 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/28 01:42:44 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(struct timeval time, int start)
{
	int	print_time;
	int	tmp;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	print_time = tmp - start;
	return (print_time);
}