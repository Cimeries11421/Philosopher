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

int	is_eating(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	if (wait_for_task(philo, start, start_routine, EATING) == -1)
		return (-1);
	philo->nbr_meal++;
	philo->meal_taken = true;
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_available = true; // mettre des locks unlocks a chaque booleens	
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->right_fork->is_available = true;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (0);
}

int	is_sleeping(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	if (wait_for_task(philo, start, start_routine, SLEEPING) == -1)
		return (-1);
	/*if (philo->name % 2 == 0)
		usleep(20);*/
	philo->meal_taken = false;
	return (0);
}
