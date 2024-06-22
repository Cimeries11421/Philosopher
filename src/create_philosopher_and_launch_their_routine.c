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

static t_philo	*create_table_of_philosophers_and_add_forks(t_tbl *tbl);
static int		launch_routine_of_all_philosophers(t_philo *tab_philo, t_tbl *tbl);

int	create_philosophers_and_launch_their_routine(t_tbl *tbl)
{
	size_t	i;
	t_philo	*tab_philo;

	tab_philo = create_table_of_philosophers_and_add_forks(tbl);
	if (tab_philo == NULL)
		return (-1);
	if (launch_routine_of_all_philosophers(tab_philo, tbl) == -1)
		return (-1);
	i = 0;
	while (i < tbl->nbr_philo)
	{
		if (pthread_join(tab_philo[i].t, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static t_philo	*create_table_of_philosophers_and_add_forks(t_tbl *tbl)
{
	size_t	i;
	t_philo	*tab_philo;

	tbl->forks = malloc(tbl->nbr_philo * sizeof(t_forks));
	if (tbl->forks == NULL)
		return (NULL);
	i = 0;
	while (i < tbl->nbr_philo)
	{	
		pthread_mutex_init(&tbl->forks[i].mutex, NULL);
		tbl->forks[i].is_available = true;
		i++;
	}
	printf("tbl->time_to_eat = %d\n" ,tbl->time_to_eat);
	printf("tbl->time_to_die = %d\n" ,tbl->time_to_die);
	tab_philo = malloc(tbl->nbr_philo * sizeof(t_philo));
	if (tab_philo == NULL)
	{
		//free_forks;
		return (NULL);
	}
	return (tab_philo);
}

static int	launch_routine_of_all_philosophers(t_philo *tab_philo, t_tbl *tbl)
{
	size_t	i;

	i = 0;
	while (i < tbl->nbr_philo)
	{
		tab_philo[i] = (t_philo){0}; //status sur thinking de base;
		tab_philo[i].tbl = tbl;
		tab_philo[i].name = i;
		if (i == tbl->nbr_philo - 1)
		{
			tab_philo[i].right_fork = &tbl->forks[i];
			tab_philo[i].left_fork = &tbl->forks[0];
			tab_philo[i].rf_index = i;
			tab_philo[i].lf_index = 0;
		}
		else
		{
			tab_philo[i].right_fork = &tbl->forks[i];
			tab_philo[i].left_fork = &tbl->forks[i + 1];
			tab_philo[i].rf_index = i; // a enlever 
			tab_philo[i].lf_index = i + 1;
		}
		if (pthread_create(&tab_philo[i].t, NULL, &routine, &tab_philo[i]) != 0)
			return (-1);
		i++;
	}
}
