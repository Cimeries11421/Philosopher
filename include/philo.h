#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "libft.h"
#include <stdbool.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define ORANGE "\x1b[38;2;255;165;0m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define LIGHT_CYAN "\x1b[96m"
#define LIGHT_BLUE "\x1b[94m"
#define PINK "\001\x1b[38;2;255;105;180m\002"
#define RESET "\001\x1b[0m\002"

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
	size_t			nbr_philo_full;
	pthread_mutex_t	meal_mutex;
	long			start_routine;
	bool			death;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	t_forks			*forks;
}				t_tbl;

typedef struct	s_philo
{
	pthread_t	t;
	size_t		name;
	bool		start;
	bool		fork_taken;
	int			nbr_meal;
	t_forks		*right_fork;
	t_forks		*left_fork;
	t_tbl		*tbl;
	e_status	status;
}				t_philo;

int	parse_input_and_store_in_struct(int ac, char **av, t_tbl *tbl);
int	create_philosophers_and_launch_their_routine(t_tbl *tbl);
void	*routine(void *arg);
long	get_time(struct timeval time, long start);
int	is_eating(t_philo *philo, long *start, long start_routine, struct timeval time);
int	is_sleeping(t_philo *philo, long *start, long start_routine, struct timeval time);
int wait_for_task(t_philo *philo, long *start, long start_routine, e_status state);
bool	check_philo_all_alive(t_philo *philo, long *start, long start_routine, struct timeval time);
int	prt_time(t_philo *philo, long *start, long start_routine, char *str);
int	print_death(t_philo *philo, long start_routine, char *str);
int	destroy_mutex(t_tbl *tbl);

#endif
