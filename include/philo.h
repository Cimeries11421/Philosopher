#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "libft.h"
#include <stdbool.h>

typedef enum	s_status
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}				e_status;

typedef struct	s_forks
{
	bool			is_available;
	pthread_mutex_t	mutex;
}				t_forks;

typedef struct	s_tbl
{
	size_t			nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_times_need_to_eat;
	t_forks			*forks;
}				t_tbl;

typedef struct	s_philo
{
	pthread_t	t;
	size_t		name;
	bool		meal_taken;
	int			fork_in_hands;
	t_tbl	*tbl;
	e_status	status;
	
}				t_philo;

int	parse_input_and_store_in_struct(int ac, char **av, t_tbl *tbl);
int	create_philosophers_and_launch_their_routine(t_tbl *tbl);

#endif
