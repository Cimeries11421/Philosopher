/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time_and_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:51:43 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/30 04:51:45 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_death(t_philo *philo, long start_routine, char *str)
{
	long			print_time;

	print_time = get_time(start_routine);
	if (philo->tbl->death == true)
	{
		pthread_mutex_unlock(&philo->tbl->print_mutex);
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (-1);
	}
	pthread_mutex_lock(&philo->tbl->test_mutex);
	if (printf("%ld %ld %s\n", print_time, philo->name, str) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->tbl->test_mutex);
	return (0);
}

int	prt_time(t_philo *philo, long *start, long start_routine, char *str)
{
	long			print_time;

	pthread_mutex_lock(&philo->tbl->print_mutex);
	print_time = get_time(start_routine);
	if (check_philo_all_alive(philo, start, start_routine) == false)
	{
		pthread_mutex_unlock(&philo->tbl->print_mutex);
		return (-1);
	}
	pthread_mutex_lock(&philo->tbl->test_mutex);
	if (printf("%ld %ld %s\n", print_time, philo->name, str) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->tbl->test_mutex);
	pthread_mutex_unlock(&philo->tbl->print_mutex);
	return (0);
}
