#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

typedef enum	s_status
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}				e_status;

typedef struct	s_philo
{
	pthread_t	t;
	size_t		name_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;	
	int			meals_taken;
	int			fork_in_hands;
	e_status	status;
}				t_philo;

typedef struct	s_global
{
	size_t	nbr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_of_times_need_to_eat;
	t_philo	*philo;
}				t_global;

int	parse_input_and_store_in_struct(int ac, char **av, t_global *global);
int	create_philosophers_and_launch_their_routine(t_global *global);

#endif
