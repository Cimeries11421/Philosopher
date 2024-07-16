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

int	print_time_and_state(t_philo *philo, long *start, long start_routine, char *str)
{
	long	print_time;
	struct	timeval time;
	long	total_time;


	pthread_mutex_lock(&philo->tbl->death_mutex);
	print_time = get_time(time, start_routine);
	total_time = get_time(time, *start);

	pthread_mutex_lock(&philo->tbl->print_mutex);
//	printf("total_time = %ld\n", total_time);
//	printf("print_time = %ld\n", print_time);
//	printf("HELLO\n");
//
	if (philo->tbl->death == true)
	{
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->tbl->death_mutex);
/*	if (check_philo_all_alive(philo, start, start_routine, time) == false)
	{
		pthread_mutex_unlock(&philo->tbl->print_mutex);
		return (-1);
	}*/
	if (printf("%ld %ld %s\n", print_time, philo->name, str) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->tbl->print_mutex);
	return (0);
}
