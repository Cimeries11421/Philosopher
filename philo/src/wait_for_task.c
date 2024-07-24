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

static int	print_task(t_philo *philo, long *start, long start_routine,
				t_status state);
static int	check_philo_dead_during_task(t_philo *philo, long *start,
				long start_routine, t_status state);
static int	loop_task(long tmp, long total_time, int time_to_wait);

int	wait_for_task(t_philo *philo, long *start, long start_routine,
		t_status state)
{
	long			total_time;
	long			tmp;
	struct timeval	time;

	total_time = 0;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (state == EATING)
	{
		*start = tmp;
		if (print_task(philo, start, start_routine, EATING) == -1)
			return (-1);
		loop_task(tmp, total_time, philo->tbl->time_to_eat);
	}
	else if (state == SLEEPING)
	{
		if (print_task(philo, start, start_routine, SLEEPING) == -1)
			return (-1);
		loop_task(tmp, total_time, philo->tbl->time_to_sleep);
	}
	return (0);
}

static int	print_task(t_philo *philo, long *start, long start_routine,
		t_status state)
{
	if (state == EATING)
	{
		if (prt_time(philo, start, start_routine, "is eating") == -1)
			return (-1);
		if (check_philo_dead_during_task(philo, start,
				start_routine, EATING) == -1)
			return (-1);
	}
	else if (state == SLEEPING)
	{
		if (prt_time(philo, start, start_routine, "is sleeping") == -1)
			return (-1);
		if (check_philo_dead_during_task(philo, start,
				start_routine, SLEEPING) == -1)
			return (-1);
	}
	return (0);
}

static int	out_of_timer(t_philo *philo, long *start, long start_routine,
		long tmp)
{
	while (1)
	{
		if (tmp >= philo->tbl->time_to_die)
			break ;
		tmp = get_time(*start);
	}
	pthread_mutex_lock(&philo->tbl->print_mutex);
	pthread_mutex_lock(&philo->tbl->death_mutex);
	if (print_death(philo, start_routine, "died") == -1)
		return (-1);
	pthread_mutex_unlock(&philo->tbl->print_mutex);
	philo->tbl->death = true;
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	return (0);
}

static int	check_philo_dead_during_task(t_philo *philo, long *start,
			long start_routine, t_status state)
{
	long			timer;
	long			tmp;

	timer = 0;
	tmp = get_time(*start);
	if (state == EATING)
		timer = tmp + philo->tbl->time_to_eat;
	else if (state == SLEEPING)
		timer = tmp + philo->tbl->time_to_sleep;
	if (timer >= philo->tbl->time_to_die)
	{
		if (out_of_timer(philo, start, start_routine, tmp) == -1)
			return (-1);
		return (-1);
	}
	return (0);
}

static int	loop_task(long tmp, long total_time, int time_to_wait)
{
	while (1)
	{
		usleep(100);
		total_time = get_time(tmp);
		if (total_time >= time_to_wait)
			break ;
	}
	return (0);
}
