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
//		philo->left_fork->is_available = true;
//		philo->right_fork->is_available = true;
//		pthread_mutex_unlock(&philo->left_fork->mutex); //pas mettre ici;
//		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (NULL);
	}
	return (NULL);
}

static int	take_fork(t_philo *philo, t_forks *fork, int *taken, )
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->is_available == true)
	{
		fork->is_available = false;
		pthread_mutex_unlock(&fork->mutex);
		if (print_time_and_state(philo, start, start_routine, "has taken a fork") == -1)
			return (-1);
		*taken = 1;
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

static int	begin_routine(t_philo *philo, int *start, int start_routine, struct timeval time)
{
	bool right_fork;
	bool left_fork;
	int	total_time;
	int	tmp;

	tmp = 0;
	if (philo->name % 2 == 0)
	{
		while (1)
		{
			if (tmp > philo->tbl->time_to_die / 2)
				break ;
			tmp = get_time(time, start_routine);
		}
	}
	total_time = 0;
	right_fork = false;
	left_fork = false;
	while (1)
	{
		if (take_fork(philo, philo->right_fork, &right_fork_taken) == -1)
			return (-1);
		if (right_fork_taken == 1)
		{
			if (take_fork(philo, philo->left_fork, &left_fork_taken) == -1)
				return (-1);
		}
		if (right_fork == true && left_fork == true)
		{
			if (is_eating(philo, start, start_routine, time) == -1)
				return (-1);
			right_fork = false;
			left_fork = false;
		}
		if (philo->nbr_meal == philo->tbl->nbr_of_times_need_to_eat)
			philo->tbl->nbr_philo_full++;
		if (philo->tbl->nbr_philo_full >= philo->tbl->nbr_philo)
			return (0);
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

/*if (check_philo_all_alive(philo, start, start_routine, time) == false)
			return (-1);
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
			if (print_time_and_state(philo, start, start_routine, "is thinking") == -1)
				return (-1);
		}
		//	usleep(30);
*/
