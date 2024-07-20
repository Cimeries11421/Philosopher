/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:37:52 by ebriere           #+#    #+#             */
/*   Updated: 2024/07/19 01:37:55 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_tbl *tbl)
{
	size_t	i;

	i = 0;
	while (i < tbl->nbr_philo)
	{
		pthread_mutex_destroy(&tbl->forks[i].mutex);
		i++;
	}
	return (0);
}
