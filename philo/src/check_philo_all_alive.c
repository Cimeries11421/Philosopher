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

static bool	check_meal_eaten(t_philo *philo)
{
	if (philo->nbr_meal == philo->tbl->nbr_of_times_need_to_eat
		&& philo->full == false)
	{
		pthread_mutex_lock(&philo->tbl->meal_mutex);
		philo->full = true;
		philo->tbl->nbr_philo_full++;
		pthread_mutex_unlock(&philo->tbl->meal_mutex);
	}
	pthread_mutex_lock(&philo->tbl->meal_mutex);
	if (philo->tbl->nbr_philo_full >= philo->tbl->nbr_philo)
	{
		pthread_mutex_unlock(&philo->tbl->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->tbl->meal_mutex);
	return (false);
}

bool	check_philo_alive_or_full(t_philo *philo, long *start,
			long start_routine)
{
	long	total_time;

	if (philo->tbl->nbr_of_times_need_to_eat != -1)
		if (check_meal_eaten(philo) == true)
			return (false);
	pthread_mutex_lock(&philo->tbl->death_mutex);
	total_time = get_time(*start);
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
