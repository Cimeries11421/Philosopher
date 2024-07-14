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

int	is_eating(t_philo *philo, long *start, long start_routine, struct timeval time)
{
	/*if (check_philo_all_alive(philo, start, start_routine, time) == false)
		return (-1);*/
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->right_fork->is_available == true)
	{
		philo->right_fork->is_available = false;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		philo->fork_taken = true;
		if (print_time_and_state(philo, start, start_routine, BLUE"has taken a fork"RESET) == -1)
			return (-1);
		//printf(BLUE"philo %d take right fork\n"RESET, philo->name);
	}
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	if (philo->fork_taken == true && philo->left_fork->is_available == true) //date race ?  
	{
		philo->left_fork->is_available = false;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		/*if (check_philo_all_alive(philo, start, start_routine, time) == false)
		return (-1);*/ // necessaire ici ? 
		if (print_time_and_state(philo, start, start_routine, GREEN"has taken a fork"RESET) == -1)
			return (-1);
		if (wait_for_task(philo, start, start_routine, EATING) == -1)
			return (-1);
		philo->nbr_meal++;
		philo->meal_taken = true;
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->is_available = true; // mettre des locks unlocks a chaque booleens
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->is_available = true;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		philo->fork_taken = false;
		return (0);
	}
	//	printf("philosopher %ld put back left fork\n", philo->name);
//	else if (philo->left_fork->is_available == false)
	pthread_mutex_unlock(&philo->left_fork->mutex);
	//printf("philosopher %ld put back right fork\n", philo->name);
	return (0);
}

int	is_sleeping(t_philo *philo, long *start, long start_routine, struct timeval time)
{
	if (wait_for_task(philo, start, start_routine, SLEEPING) == -1)
		return (-1);
	if (philo->name % 2 == 0)
		usleep(200);
	philo->meal_taken = false;
	return (0);
}
