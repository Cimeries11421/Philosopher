/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:34 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/19 16:35:36 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	begin_routine(t_philo *philo, long *start, long start_routine);

void	*routine(void *arg)
{
	t_philo			*philo;
	long			start;
	long			start_routine;
	int				i;

	i = 0;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->tbl->death_mutex);
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	start_routine = philo->tbl->start_routine;
	start = start_routine;
	if (begin_routine(philo, &start, start_routine) == -1)
	{
		pthread_mutex_lock(&philo->tbl->death_mutex);
		philo->tbl->death = true;
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (NULL);
	}
	return (NULL);
}

static bool	check_meal_eaten(t_philo *philo)
{
	if (philo->nbr_meal == philo->tbl->nbr_of_times_need_to_eat)
	{
		pthread_mutex_lock(&philo->tbl->meal_mutex);
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

static int	begin_routine(t_philo *philo, long *start, long start_routine)
{
	int	total_time;
	int	time_to_wait;
	int	tmp;

	tmp = 0;
	if (philo->tbl->time_to_die > philo->tbl->time_to_eat)
		time_to_wait = philo->tbl->time_to_eat;
	else
		time_to_wait = philo->tbl->time_to_die;
	if (philo->name % 2 != 0)
		usleep(time_to_wait / 2 * 1000);
	total_time = 0;
	while (1)
	{
		if (is_eating(philo, start, start_routine) == -1)
			return (-1);
		if (is_sleeping(philo, start, start_routine) == -1)
			return (-1);
		if (prt_time(philo, start, start_routine, "is thinking") == -1)
			return (-1);
		if (check_meal_eaten(philo) == true)
			return (0);
		usleep(10);
	}
	return (0);
}
