/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo_all_alive.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:44:23 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/28 01:44:27 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_all_alive(t_philo *philo, long *start, long start_routine)
{
	long	total_time;
	long	print_time;

	pthread_mutex_lock(&philo->tbl->death_mutex);
	total_time = get_time(*start);
	print_time = get_time(start_routine);
	if (philo->tbl->death == true)
	{
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (false);
	}
	if (total_time >= philo->tbl->time_to_die)
	{
		if (print_death(philo, start_routine, "died") == -1)
			return (false);
		philo->tbl->death = true;
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	return (true);
}