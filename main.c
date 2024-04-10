/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:36:28 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/10 10:22:51 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// die 				./philo 1 800 200 200
// no die			./philo 5 800 200 200
// only eat 7 times 	./philo 5 800 200 200 7
// no die 			./philo 4 410 200 200
// one die 			./philo 4 310 200 100

int	main(int ac, char **av)
{
	t_table	table;

	table = (t_table){0};
	if (init_input(ac, av, &table))
		return (1);
	if (init_philo(&table))
		return (1);
	// printf("Philo initialized\n");
	if (init_philo_threads(&table))
		return (1);
	printf("Simulation finished\n");
	return (0);
}
