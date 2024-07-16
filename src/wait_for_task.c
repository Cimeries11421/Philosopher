/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_task.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:48:40 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/28 01:48:41 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	check_philo_dead_during_task(t_philo *philo, long *start, long start_routine, e_status state)
{
	long	timer;
	long	tmp;
	struct timeval time;

	tmp = get_time(time, *start);
	//check bool death ?
	//pas besoin d'unlock les fourchettes car deja unlock quand il mange
//	printf("start = %ld\n", *start);
//	timer = get_time(time, *start);
//	printf("timer = %ld\n", timer);
	if (state == EATING)
		timer = tmp + philo->tbl->time_to_eat;
	if (state == SLEEPING)
		timer = tmp + philo->tbl->time_to_sleep;
	if (timer >= philo->tbl->time_to_die)
	{
	//	while ()
	//	{}
	//	usleep(410 * 1000);
		if (print_time_and_state(philo, start, start_routine, RED"died"RESET) == -1)
			return (-1); //probleme unlock a nouveau les fourchettes, je dois les unlocks ?  

		pthread_mutex_lock(&philo->tbl->death_mutex);
		philo->tbl->death = true;
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (true);
	}
	return (false);
} 

int wait_for_task(t_philo *philo, long *start, long start_routine, e_status state)
{
	long		total_time;
	long		tmp;
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
			return (-1);	
	tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (state == EATING)
	{
		*start = tmp;
		if (print_time_and_state(philo, start, start_routine, ORANGE"is eating"RESET) == -1)
			return (-1);
		if (check_philo_dead_during_task(philo, start, start_routine, EATING) == true)
		{
			return (-1);
		}
	}
	else if (state == SLEEPING)
	{
		if (print_time_and_state(philo, start, start_routine, PINK"is sleeping"RESET) == -1)
			return (-1);
	
		if (check_philo_dead_during_task(philo, start, start_routine, EATING) == true)
		{
			return (-1);
		}
	}
	while (1)
	{
		usleep(200);
	//	if (state == EATING)
	//		printf(PINK"philo %ld start = %ld\n"RESET, philo->name, *start);
		total_time = get_time(time, tmp);
		if (state == EATING)
		{
			if (total_time >= philo->tbl->time_to_eat)
				break ;
		}
		if (state == SLEEPING)
		{
			if (total_time >= philo->tbl->time_to_sleep)
				break ;
		}
	}
	return (0);
}
