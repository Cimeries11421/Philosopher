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

int wait_for_task(t_philo *philo, int *start, int start_routine, e_status state)
{
	int		total_time;
	int		tmp;
	struct timeval time;

	//printf(YELLOW"start = %d for philo %ld\n"RESET, *start, philo->name);
	if (gettimeofday(&time, NULL) == -1)
			return (-1);	
	tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (1)
	{
		if (state == EATING)
			*start = tmp;
		usleep(100);
		if (check_philo_all_alive(philo, start, time) == false)
		{
			if (print_time_and_state(philo, start_routine, "died") == -1)
				return (-1);
			return (-1);
		}
		total_time = get_time(time, tmp);
		if (state == EATING)
		{
			if (total_time >= philo->tbl->time_to_eat)
			{
				if (print_time_and_state(philo, start_routine, "is eating") == -1)
					return (-1);
				break ;
			}
		}
		if (state == SLEEPING)
		{
			if (total_time >= philo->tbl->time_to_sleep)
			{
				if (print_time_and_state(philo, start_routine, "is sleeping") == -1)
					return (-1);
				break ;
			}
		}
	}
	return (0);
}
