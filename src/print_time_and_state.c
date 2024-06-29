#include "philo.h"

int	print_time_and_state(t_philo *philo, int start_routine, char *str)
{
	int		print_time;
	struct	timeval time;

	print_time = get_time(time, start_routine);
	if (printf("%d %ld %s\n", print_time, philo->name, str) == -1)
		return (-1);
	return (0);
}
