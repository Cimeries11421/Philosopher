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

static int	begin_routine(t_philo *philo, int *start, int start_routine, struct timeval time);

void	*routine(void *arg)
{
	t_philo			*philo;	
	struct timeval	time;
	int				start;
	int				start_routine;
	
	philo = (t_philo*)arg;
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	start_routine = start;
	//printf("\nphilo %ld got right_fork number : %ld and left_fork_number : %ld\n\n", philo->name,
//			philo->rf_index, philo->lf_index);
	if (begin_routine(philo, &start, start_routine, time) == -1)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (NULL);
	}
	return (NULL);
}

static int	begin_routine(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	int	total_time;
	int	print_time;


	if (philo->name % 2 == 0)
		usleep(philo->tbl->time_to_eat * 500);
	total_time = 0;
	while (1)
	{
		if (philo->tbl->death == true)
			return (-1);
		if (philo->tbl->nbr_philo >= 2)
		{
			if (is_eating(philo, start, start_routine, time) == -1)
				return (-1);
		}
		if (philo->meal_taken == true)
		{
			if (is_sleeping(philo, start, start_routine, time) == -1)
				return (-1);
			if (print_time_and_state(philo, start, start_routine, "is thinking") == -1)
				return (-1);
		}
	}
	return (0);
}
