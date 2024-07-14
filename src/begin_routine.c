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

static int	begin_routine(t_philo *philo, long *start, long start_routine, struct timeval time);

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time;
	long			start;
	long 			start_routine;
	
	philo = (t_philo*)arg;
	start_routine = philo->tbl->start_routine;
	start = start_routine;
//	printf("time.tv_sec = %d  usec = %d\n", time.tv_sec, time.tv_usec);
//	printf("start = %ld\n", start);
	//printf("\nphilo %ld got right_fork number : %ld and left_fork_number : %ld\n\n", philo->name,
//			philo->rf_index, philo->lf_index);
	pthread_mutex_lock(&philo->tbl->death_mutex);
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	if (begin_routine(philo, &start, start_routine, time) == -1)
	{
		philo->left_fork->is_available = true; //a enlever je crois 
		philo->right_fork->is_available = true;
		return (NULL);
	}
	return (NULL);
}

static int	begin_routine(t_philo *philo, long *start, long start_routine, struct timeval time)
{
	int	total_time;
	int	time_to_wait;
	int	tmp;

	tmp = 0;
	if (philo->tbl->time_to_die > philo->tbl->time_to_eat)
		time_to_wait = philo->tbl->time_to_eat;
	else
		time_to_wait = philo->tbl->time_to_die;
	if (philo->name % 2 == 0)
	{
		while (1)
		{
			if (tmp > time_to_wait / 2)
				break ;
			tmp = get_time(time, start_routine);
		}
	}
	total_time = 0;
	while (1)
	{
		if (check_philo_all_alive(philo, start, start_routine, time) == false)
		{
			//printf("mort boucle principale\n");
			return (-1);
		}
		if (philo->tbl->nbr_philo >= 2)
		{
			if (is_eating(philo, start, start_routine, time) == -1)
				return (-1);
		}
		if (philo->nbr_meal == philo->tbl->nbr_of_times_need_to_eat)
			philo->tbl->nbr_philo_full++;
		if (philo->tbl->nbr_philo_full >= philo->tbl->nbr_philo)
			return (0);
		if (philo->meal_taken == true)
		{
			if (is_sleeping(philo, start, start_routine, time) == -1)
				return (-1);
			if (print_time_and_state(philo, start, start_routine, MAGENTA"is thinking"RESET) == -1)
				return (-1);
		}
		usleep(100);
	}
	return (0);
}
