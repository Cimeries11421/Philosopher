/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosopher_and_launch_their_routi          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:29:51 by ebriere           #+#    #+#             */
/*   Updated: 2024/05/29 17:29:55 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating(t_philo *philo, int start, struct timeval time)
{
	int	end;
	int	total_time;

	total_time = 0;
	int i = 5;
	while (1)
	{
		//printf("forks[0].is_available = %d\n", philo->tbl->forks[0].is_available);
		//printf("forks[1].is_available = %d\n", philo->tbl->forks[1].is_available);
		
		//printf("total_time = %d, tbl->time_to_die = %d\n" , total_time, philo->tbl->time_to_die);
		if (total_time > philo->tbl->time_to_die)
		{
			printf("philosopher %ld is dead\n", philo->name);
			return (0);
		}
		printf("name = %d\n  nbr_philo = %d\n", philo->name, philo->tbl->nbr_philo);
		if (philo->name < philo->tbl->nbr_philo)
		{
			if (philo->tbl->forks[philo->name].is_available == true
				&& philo->tbl->forks[philo->name + 1].is_available == true)
			{
				philo->tbl->forks[philo->name].is_available = false;
				philo->tbl->forks[philo->name + 1].is_available = false;
				printf("passe la\n");
				printf("philosopher %ld is eating\n", philo->name);
				usleep(philo->tbl->time_to_eat * 1000);
				philo->tbl->forks[philo->name].is_available = true;
				philo->tbl->forks[philo->name + 1].is_available = true;
				philo->meal_taken = true;
				if (gettimeofday(&time, NULL) == -1)
					return (-1);
				start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
//				pthread_mutex_lock(&philo->tbl->forks[0].mutex);
			}
		}
		else	
			printf("philosopher %ld is thinking\n", philo->name);
		if (philo->meal_taken == true)
		{
			printf("philosopher %ld is sleeping\n", philo->name);
			usleep(philo->tbl->time_to_sleep * 1000);
			philo->meal_taken = false;
		}
		if (gettimeofday(&time, NULL) == -1)
			return (-1);
		end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		total_time = end - start;
	}
//	printf("total_time = %d\n", total_time);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;	
	struct timeval	time;
	int				start;
		
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	philo = (t_philo*)arg;
	if (is_eating(philo, start, time) == -1)
		return (-1);
}

int	create_philosophers_and_launch_their_routine(t_tbl *tbl)
{
	size_t	i;
	t_philo	*tab_philo;

	tbl->forks = malloc(tbl->nbr_philo * sizeof(t_forks));
	if (tbl->forks == NULL)
		return (NULL);
	i = 0;
	while (i < tbl->nbr_philo)
	{
		tbl->forks[i].is_available = true;
		//printf("forks[%d].is_available = %d\n", i, tbl->forks[i].is_available);
		i++;
	}
	printf("tbl->time_to_eat = %d\n" ,tbl->time_to_eat);
	printf("tbl->time_to_die = %d\n" ,tbl->time_to_die);
	tab_philo = malloc(tbl->nbr_philo * sizeof(t_philo));
	if (tab_philo == NULL)
	{
		//free_forks;
		return (-1);
	}
	i = 0;
	while (i < tbl->nbr_philo)
	{
		tab_philo[i] = (t_philo){0, i, 0, 0, tbl, 0}; //status sur thinking de base;
		//tab_philo[i].tbl = tbl;
		//tab_philo[i].name = i;
		if (pthread_create(&tab_philo[i].t, NULL, &routine, &tab_philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < tbl->nbr_philo)
	{
		if (pthread_join(tab_philo[i].t, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}


