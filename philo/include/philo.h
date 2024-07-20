/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:06:35 by ebriere           #+#    #+#             */
/*   Updated: 2024/07/21 01:06:36 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef enum s_status
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}				t_status;

typedef struct s_forks
{
	bool			is_available;
	pthread_mutex_t	mutex;
}				t_forks;

typedef struct s_tbl
{
	size_t			nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_times_need_to_eat;
	size_t			nbr_philo_full;
	pthread_mutex_t	meal_mutex;
	long			start_routine;
	bool			death;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	t_forks			*forks;
}				t_tbl;

typedef struct s_philo
{
	pthread_t	t;
	size_t		name;
	bool		fork_taken;
	int			nbr_meal;
	t_forks		*right_fork;
	t_forks		*left_fork;
	t_tbl		*tbl;
	t_status	status;
}				t_philo;

long	ft_strtol(const char *p);
int		ft_isdigit(int c);
int		parse_input_and_store_in_struct(int ac, char **av, t_tbl *tbl);
int		create_philosophers_and_launch_their_routine(t_tbl *tbl);
void	*routine(void *arg);
long	get_time(long start);
int		is_eating(t_philo *philo, long *start, long start_routine);
int		is_sleeping(t_philo *philo, long *start, long start_routine);
int		wait_for_task(t_philo *philo, long *start, long start_routine,
			t_status state);
bool	check_philo_all_alive(t_philo *philo, long *start, long start_routine);
int		prt_time(t_philo *philo, long *start, long start_routine, char *str);
int		print_death(t_philo *philo, long start_routine, char *str);
int		destroy_mutex(t_tbl *tbl);

#endif
