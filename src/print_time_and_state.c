/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time_and_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:51:43 by ebriere           #+#    #+#             */
/*   Updated: 2024/06/30 04:51:45 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_time_and_state(t_philo *philo, int *start, int start_routine, char *str)
{
	int		print_time;
	struct	timeval time;

	print_time = get_time(time, start_routine);
//	printf("HELLO\n");
	if (check_philo_all_alive(philo, start, start_routine, time) == false)
		return (-1);
	if (printf("%d %ld %s\n", print_time, philo->name, str) == -1)
		return (-1);
	return (0);
}
