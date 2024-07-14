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

int wait_for_task(t_philo *philo, long *start, long start_routine, e_status state)
{
	long		total_time;
	long		tmp;
	struct timeval time;

	//printf(YELLOW"start = %d for philo %ld\n"RESET, *start, philo->name);
	if (gettimeofday(&time, NULL) == -1)
			return (-1);	
	tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (state == EATING)
	{
		*start = tmp;
		if (print_time_and_state(philo, start, start_routine, ORANGE"is eating"RESET) == -1)
			return (-1);
	}
	else
	{
		if (print_time_and_state(philo, start, start_routine, PINK"is sleeping"RESET) == -1)
			return (-1);
	}
	while (1)
	{
		usleep(200);
		if (check_philo_all_alive(philo, start, start_routine, time) == false)
		{
			return (-1);
		}
		total_time = get_time(time, tmp);
		if (state == EATING)
		{
			if (total_time >= philo->tbl->time_to_eat)
			{
				break ;
			}
		}
		if (state == SLEEPING)
		{
			if (total_time >= philo->tbl->time_to_sleep)
			{
				break ;
			}
		}
	}
	return (0);
}
