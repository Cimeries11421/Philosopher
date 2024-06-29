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

bool	check_philo_all_alive(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	int	total_time;

	pthread_mutex_lock(&philo->tbl->death_mutex);
	total_time = get_time(time, *start);
	if (philo->tbl->death == true)
	{
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (false);
	}
	if (total_time >= philo->tbl->time_to_die)
	{
		philo->tbl->death = true;
		if (print_time_and_state(philo, start_routine, "died") == -1)
			return (-1);
		//if (printf("%d %ld died\n", print_time, philo->name) == -1)
		//	return (false) //secu ?
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	return (true);
}
