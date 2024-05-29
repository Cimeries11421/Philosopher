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

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	printf("philosopher %ld is eating\n", philo->name_philo);
	usleep(philo->t_eat * 1000);
}

int	create_philosophers_and_launch_their_routine(t_global *global)
{
	size_t	i;

	global->philo = malloc(global->nbr_philo * sizeof(t_philo));
	if (global->philo == NULL)
		return (-1);
	i = 0;
	while (i < global->nbr_philo)
	{
		global->philo[i].t_die = global->time_to_die;
		global->philo[i].t_eat = global->time_to_eat;
		global->philo[i].t_sleep = global->time_to_sleep;
		global->philo[i].name_philo = i;
		if (pthread_create(&global->philo[i].t, NULL, &routine, &global->philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < global->nbr_philo)
	{
		if (pthread_join(global->philo[i].t, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}


