/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:35:34 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/19 16:35:36 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	begin_routine(t_philo *philo, int *start, int start_routine, struct timeval time);
static int	is_eating(t_philo *philo, int *start, int start_routine, struct timeval time);
static int	is_sleeping(t_philo *philo, int *start, int start_routine, struct timeval time);
static bool wait_and_check_if_philo_still_alive(t_philo *philo, int *start,
		e_status status, struct timeval time);
static int	get_time(struct timeval time, int start_routine);

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
	printf("\nphilo %ld got right_fork number : %ld and left_fork_number : %ld\n\n", philo->name,
			philo->rf_index, philo->lf_index);
	if (begin_routine(philo, &start, start_routine, time) == -1)
		return (NULL);
}

static int	begin_routine(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	int	end;
	int	total_time;
	int	print_time;

	total_time = 0;
	int i = 5;
	while (1)
	{
		if (philo->tbl->death == true)
			return (-1);
		if (philo->tbl->nbr_philo >= 2)
		{
			if (is_eating(philo, start, start_routine, time) == -1)
			{
				philo->tbl->death = true;
				printf(RED"philosopher %ld is dead\n"RESET, philo->name);
				return (-1);
			}
		}
		if (philo->meal_taken == true)
		{
			if (is_sleeping(philo, start, start_routine, time) == -1)
				return (-1);
			print_time = get_time(time, start_routine);
			printf(GREEN"%d philosopher %ld is thinking\n"RESET, print_time, philo->name);
		}
		if (gettimeofday(&time, NULL) == -1)
			return (printf("get time of"), -1);
		end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		total_time = end - *start;
	}
	return (0);
}

static int	get_time(struct timeval time, int start_routine)
{
	int	print_time;
	int	tmp;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	print_time = tmp-start_routine;
	return (print_time);
}

static int	is_eating(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	int	print_time;

	if (philo->name % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->right_fork->mutex);
//	pthread_mutex_lock(&philo->left_fork.mutex);
	if (philo->right_fork->is_available == true)
	{
		philo->right_fork->is_available = false;
	//	printf("philosopher %ld take right fork\n", philo->name);
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->left_fork->is_available == true)
		{
			philo->left_fork->is_available = false;
		//	printf("philosopher %ld take left fork\n", philo->name);
			
			print_time = get_time(time, start_routine);
			printf(PINK"%d philosopher %ld is eating\n"RESET, print_time, philo->name);
	//		usleep(philo->tbl->time_to_eat * 1000);
			if (wait_and_check_if_philo_still_alive(philo, start, EATING, time) == false)
				return (-1);
			philo->meal_taken = true;
			if (gettimeofday(&time, NULL) == -1)
				return (printf("HOUHOU\n"), -1);
			*start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
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

static int	is_sleeping(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	int	print_time; 

	print_time = get_time(time, start_routine);
	printf(BLUE"%d philosopher %ld is sleeping\n"RESET, print_time, philo->name);
	if (wait_and_check_if_philo_still_alive(philo, start, SLEEPING, time) == false)
		return (-1);
//	usleep(philo->tbl->time_to_sleep * 1000);
	philo->meal_taken = false;
	return (0);
}
static bool wait_and_check_if_philo_still_alive(t_philo *philo, int *start,
		e_status status, struct timeval time)
{
	int		end;
	int		total_time;
	int		tmp;

//	printf(YELLOW"start = %d for philo %ld\n"RESET, *start, philo->name);
	if (gettimeofday(&time, NULL) == -1)
			return (-1);	
		tmp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (1)
	{
		usleep(40);
		if (gettimeofday(&time, NULL) == -1)
			return (-1);
		end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		total_time = end - *start;

	//	printf(RED"total_time before death = %d for philo %d\n"RESET, total_time, philo->name);
		if (total_time >= philo->tbl->time_to_die)
		{
			printf(RED"total_time before death = %d\n"RESET, total_time);
			return (false);
		}
		total_time = end - tmp;
		if (status == EATING && total_time >= philo->tbl->time_to_eat)
		{
//			printf(YELLOW"total_time before finish eating = %d for philo %ld\n"RESET, total_time, philo->name);
			break ;
		}
		if (status == SLEEPING && total_time >= philo->tbl->time_to_sleep)
		{
//			printf(YELLOW"total_time before finish sleeping = %d for philo %ld\n"RESET, total_time, philo->name);
			break ;
		}
	}
	return (true);
}
