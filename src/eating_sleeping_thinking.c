/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_sleeping_thinking.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:53:36 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/28 01:53:38 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_right_fork(t_philo *philo, long *start, long start_routine);
static void	put_back_forks(t_philo *philo);

int	is_eating(t_philo *philo, long *start, long start_routine)
{
	while (1)
	{
		if (check_philo_all_alive(philo, start, start_routine) == false)
			return (-1);
		if (take_right_fork(philo, start, start_routine) == -1)
			return (-1);
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->fork_taken == true
			&& philo->left_fork->is_available == true)
		{
			philo->left_fork->is_available = false;
			pthread_mutex_unlock(&philo->left_fork->mutex);
			if (prt_time(philo, start, start_routine, "has taken a fork") == -1)
				return (-1);
			if (wait_for_task(philo, start, start_routine, EATING) == -1)
				return (-1);
			philo->nbr_meal++;
			put_back_forks(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		usleep(10);
	}
	return (0);
}

static int	take_right_fork(t_philo *philo, long *start, long start_routine)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->right_fork->is_available == true)
	{
		philo->right_fork->is_available = false;
		philo->fork_taken = true;
		if (prt_time(philo, start, start_routine, "has taken a fork") == -1)
		{
			pthread_mutex_unlock(&philo->right_fork->mutex);
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (0);
}

static void	put_back_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_available = true;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_available = true;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->fork_taken = false;
}

int	is_sleeping(t_philo *philo, long *start, long start_routine)
{
	if (wait_for_task(philo, start, start_routine, SLEEPING) == -1)
		return (-1);
	if (philo->name % 2 == 0)
		usleep(20);
	return (0);
}
