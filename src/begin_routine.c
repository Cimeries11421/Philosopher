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
	int				i;
	
	i = 0;
	philo = (t_philo*)arg;	
	pthread_mutex_lock(&philo->tbl->death_mutex);
	pthread_mutex_unlock(&philo->tbl->death_mutex);
	start_routine = philo->tbl->start_routine;
	start = start_routine;
	philo->start = 1;
	if (begin_routine(philo, &start, start_routine, time) == -1)
	{
	//	philo->left_fork->is_available = true; //a enlever je crois 
	//	philo->right_fork->is_available = true;
		return (NULL);
	}
	//printf("why here\n");
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
	if (philo->name % 2 != 0)
		usleep(time_to_wait / 2 * 1000);
	total_time = 0;
	while (1)
	{
		if (is_eating(philo, start, start_routine, time) == -1)
			return (-1);
		if (philo->nbr_meal == philo->tbl->nbr_of_times_need_to_eat)
			philo->tbl->nbr_philo_full++;
		if (philo->tbl->nbr_philo_full >= philo->tbl->nbr_philo)
			return (0);
		if (is_sleeping(philo, start, start_routine, time) == -1)
			return (-1);
		if (print_time_and_state(philo, start, start_routine, MAGENTA"is thinking"RESET) == -1)
			return (-1);
	/*	if (check_philo_all_alive(philo, start, start_routine, time) == false)
			return (-1);*/
		usleep(10);
	}
	return (0);
}
