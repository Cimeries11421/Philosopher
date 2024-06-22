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

static int	begin_routine(t_philo *philo, int *start, struct timeval time);
static int	is_eating(t_philo *philo, int *start, struct timeval time);
static void	is_sleeping(t_philo *philo);

void	*routine(void *arg)
{
	t_philo			*philo;	
	struct timeval	time;
	int				start;
	
	philo = (t_philo*)arg;
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	printf("\nphilo %ld got right_fork number : %ld and left_fork_number : %ld\n\n", philo->name,
			philo->rf_index, philo->lf_index);
	if (begin_routine(philo, &start, time) == -1)
		return (-1);
}

static int	begin_routine(t_philo *philo, int *start, struct timeval time)
{
	int	end;
	int	total_time;

	total_time = 0;
	int i = 5;
	while (1)
	{
		if (total_time > philo->tbl->time_to_die)
		{
			printf("philosopher %ld is dead\n", philo->name);
			printf("total_time = %d, time_to_die = %d\n" , total_time, philo->tbl->time_to_die);
			return (0);
		}
		if (philo->tbl->nbr_philo >= 2)
		{
			if (is_eating(philo, start, time) == -1)
				return (printf("error \n"), -1);
		}
		else	
			printf("philosopher %ld is thinking\n", philo->name);
		if (philo->meal_taken == true)
		{
			is_sleeping(philo);
		}
		if (gettimeofday(&time, NULL) == -1)
			return (printf("get time of"), -1);
		end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		total_time = end - *start;
	}
//	printf("total_time = %d\n", total_time);
	return (0);
}

static int	is_eating(t_philo *philo, int *start, struct timeval time)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
//	pthread_mutex_lock(&philo->left_fork.mutex);
	if (philo->right_fork->is_available == true)
	{
		philo->right_fork->is_available = false;
		printf("philosopher %ld take right fork\n", philo->name);
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->left_fork->is_available == true)
		{
			philo->left_fork->is_available = false;
			printf("philosopher %ld take left fork\n", philo->name);
			printf("philosopher %ld is eating\n", philo->name);
			usleep(philo->tbl->time_to_eat * 1000);
			philo->meal_taken = true;
			if (gettimeofday(&time, NULL) == -1)
				return (printf("HOUHOU\n"), -1);
			*start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
			philo->left_fork->is_available = true;
		}
		printf("philosopher %ld put back left fork\n", philo->name);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		philo->right_fork->is_available = true;
	}
	printf("philosopher %ld put back right fork\n", philo->name);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (0);
}

static void	is_sleeping(t_philo *philo)
{
	printf("philosopher %ld is sleeping\n", philo->name);
	usleep(philo->tbl->time_to_sleep * 1000);
	philo->meal_taken = false;
}
