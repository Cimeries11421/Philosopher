/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:58:33 by ebriere           #+#    #+#             */
/*   Updated: 2024/05/28 01:58:35 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_global global;

	global = (t_global){0};
	if (parse_input_and_store_in_struct(ac, av, &global) == -1)
		return (-1);
	printf("nbr_philo = %ld\n", global.nbr_philo);
	if (create_philosophers_and_launch_their_routine(&global) == -1)
		return (-1);
	return (0);
}
