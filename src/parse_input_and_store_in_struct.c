/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_and_store_in_struct.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <ebriere@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:51:10 by ebriere           #+#    #+#             */
/*   Updated: 2024/05/28 01:51:12 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **av);
static int	not_only_digit(char *str);

int	parse_input_and_store_in_struct(int ac, char **av, t_tbl *tbl)
{
	if (ac != 6)
	{
		write(2,"need 5 arguments\n", 18);
		return (-1);
	}
	if (check_args(av) == -1)
	{
		write(2, "Wrong Input\n", 13);
		return (-1);
	}
	tbl->nbr_philo = ft_strtol(av[1]);
	tbl->time_to_die = ft_strtol(av[2]);
	tbl->time_to_eat = ft_strtol(av[3]);
	tbl->time_to_sleep = ft_strtol(av[4]);
	tbl->nbr_of_times_need_to_eat = ft_strtol(av[5]);
	return (0);
}

static int	check_args(char **av)
{
	size_t	i;
	long	nb;

	i = 1;
	while (av[i])
	{
		if (not_only_digit(av[i]) == -1)
			return (-1);
		nb = ft_strtol(av[i]);
		if (nb < 0 || nb >= 2147483647)
			return (-1);
		++i;
	}
	return (0);
}

static int	not_only_digit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (-1);
		++i;
	}
	return (0);
}
