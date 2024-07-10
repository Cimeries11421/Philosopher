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
	/*if (check_philo_all_alive(philo, start, start_routine, time) == false)
		return (-1);*/
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->right_fork->is_available == true)
	{
		philo->right_fork->is_available = false;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		if (print_time_and_state(philo, start, start_routine, "has taken a fork") == -1)
			return (-1);
		//printf("philosopher %ld take right fork\n", philo->name);
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->left_fork->is_available == true)
		{
			philo->left_fork->is_available = false;
			pthread_mutex_unlock(&philo->left_fork->mutex);
		//	printf("philosopher %ld take left fork\n", philo->name);
			/*if (check_philo_all_alive(philo, start, start_routine, time) == false)
				return (-1);*/ // necessaire ici ? 
			if (print_time_and_state(philo, start, start_routine, "has taken a fork") == -1)
				return (-1);
			if (wait_for_task(philo, start, start_routine, EATING) == -1)
				return (-1);
			philo->nbr_meal++;
			philo->meal_taken = true;
			philo->left_fork->is_available = true;
		}
	//	printf("philosopher %ld put back left fork\n", philo->name);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		philo->right_fork->is_available = true;
	}
	//printf("philosopher %ld put back right fork\n", philo->name);
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
