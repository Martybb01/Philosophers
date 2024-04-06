/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/06 19:04:13 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = data;
	table = philo->table;
	printf("philo %d is alive\n", philo->id);
	print_philo(table, philo->id, THINK);
	philo->meals_eaten++;
	return (NULL);
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_count)
	{
		// printf("ciso\n");
		table->philo->last_meal = get_time();
		if (pthread_create(&table->philo[i].philo_thr, NULL, philo_life,
				&table->philo[i]))
			ft_error(5);
		i++;
	}
	// check dead or finish of thr simulation
	i = 0;
	while (i < table->input.philo_count)
	{
		if (pthread_join(table->philo[i].philo_thr, NULL))
			ft_error(5);
		printf("Philo thread %d joined\n", i);
		i++;
	}
	printf("meals eaten: %d\n", table->philo->meals_eaten);
	// free all threads
	return (0);
}
