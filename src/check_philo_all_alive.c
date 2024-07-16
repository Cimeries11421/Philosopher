/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo_all_alive.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:44:23 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/28 01:44:27 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_all_alive(t_philo *philo, long *start, long start_routine, struct timeval time)
{
	long	total_time;
	long	print_time;

	pthread_mutex_lock(&philo->tbl->death_mutex);
	total_time = get_time(time, *start); //necessaire ? 
	print_time = get_time(time, start_routine);
	if (philo->tbl->death == true)
	{	
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->is_available = true;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->is_available = true;
		pthread_mutex_unlock(&philo->left_fork->mutex); //comment faire si deja unlock
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		return (false);
	}
	if (total_time >= philo->tbl->time_to_die)
	{
		philo->tbl->death = true;
		pthread_mutex_unlock(&philo->tbl->death_mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->is_available = true;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		philo->left_fork->is_available = true;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		if (print_time_and_state(philo, start, start_routine, RED"died"RESET) == -1)
			return (-1);

		//if (printf(RED"%ld %ld %ld died\n"RESET,total_time, print_time, philo->name) == -1)
	//	if (printf("%ld %ld died\n", print_time, philo->name) == -1)
	//		return (false); //secu ?
		return (false);
	}
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	return (true);
}
