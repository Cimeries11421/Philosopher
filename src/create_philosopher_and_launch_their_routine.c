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
static int		launch_routine_of_all_philosophers(t_philo *tab_philo,
					t_tbl *tbl);
static int		init_mutex(t_tbl *tbl);
static void		init_philos_and_give_fork(t_philo *tab_philo,
					t_tbl *tbl, size_t *i);

int	create_philosophers_and_launch_their_routine(t_tbl *tbl)
{
	size_t	i;
	t_philo	*tab_philo;

	tbl->death = false;
	tab_philo = create_table_of_philosophers_and_add_forks(tbl);
	if (tab_philo == NULL)
		return (-1);
	if (launch_routine_of_all_philosophers(tab_philo, tbl) == -1)
	{
		destroy_mutex(tbl);
		return (-1);
	}
	i = 0;
	while (i < tbl->nbr_philo)
	{
		if (pthread_join(tab_philo[i].t, NULL) != 0)
		{
			destroy_mutex(tbl);
			return (-1);
		}
		i++;
	}
	return (0);
}

static t_philo	*create_table_of_philosophers_and_add_forks(t_tbl *tbl)
{
	t_philo	*tab_philo;

	tbl->forks = malloc(tbl->nbr_philo * sizeof(t_forks));
	if (tbl->forks == NULL)
		return (NULL);
	if (init_mutex(tbl) == -1)
		return (NULL);
	tab_philo = malloc(tbl->nbr_philo * sizeof(t_philo));
	if (tab_philo == NULL)
		return (free(tbl->forks), NULL);
	return (tab_philo);
}

static int	init_mutex(t_tbl *tbl)
{
	size_t	i;

	i = 0;
	while (i < tbl->nbr_philo)
	{
		if (pthread_mutex_init(&tbl->forks[i].mutex, NULL) == -1)
			return (-1);
		tbl->forks[i].is_available = true;
		i++;
	}
	if (pthread_mutex_init(&tbl->death_mutex, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&tbl->print_mutex, NULL) == -1)
	{
		pthread_mutex_destroy(&tbl->death_mutex);
		return (-1);
	}
	if (pthread_mutex_init(&tbl->meal_mutex, NULL) == -1)
	{
		pthread_mutex_destroy(&tbl->death_mutex);
		pthread_mutex_destroy(&tbl->print_mutex);
		return (-1);
	}
	return (0);
}

static int	launch_routine_of_all_philosophers(t_philo *tab_philo, t_tbl *tbl)
{
	size_t			i;
	struct timeval	time;

	i = 0;
	pthread_mutex_lock(&tbl->death_mutex);
	while (i < tbl->nbr_philo)
	{
		init_philos_and_give_fork(tab_philo, tbl, &i);
		if (pthread_create(&tab_philo[i].t, NULL, &routine, &tab_philo[i]) != 0)
			return (-1);
		i++;
	}
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	tbl->start_routine = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	pthread_mutex_unlock(&tbl->death_mutex);
	return (0);
}

static void	init_philos_and_give_fork(t_philo *tab_philo, t_tbl *tbl, size_t *i)
{
	tab_philo[*i] = (t_philo){0};
	tab_philo[*i].tbl = tbl;
	tab_philo[*i].name = *i;
	tab_philo[*i].fork_taken = false;
	tab_philo[*i].start = false;
	if (*i == tbl->nbr_philo - 1)
	{
		tab_philo[*i].right_fork = &tbl->forks[*i];
		tab_philo[*i].left_fork = &tbl->forks[0];
	}
	else
	{
		tab_philo[*i].right_fork = &tbl->forks[*i];
		tab_philo[*i].left_fork = &tbl->forks[(*i) + 1];
	}
}
