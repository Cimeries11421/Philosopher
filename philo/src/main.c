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
	t_tbl	tbl;

	tbl = (t_tbl){0};
	if (parse_input_and_store_in_struct(ac, av, &tbl) == -1)
		return (-1);
	if (av[5] == NULL)
		tbl.nbr_of_times_need_to_eat = -1;
	if (create_philosophers_and_launch_their_routine(&tbl) == -1)
		return (-1);
	return (0);
}
