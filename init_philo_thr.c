/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/10 10:33:17 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (philo->id % 2)
		custom_usleep(100);
	while (!table->sim_end)
	{
		philo_eat(table, philo);
		philo_sleep(table, philo);
		philo_think(table, philo);
	}
	return ((void *)0);
}

void	sim_finish_die(t_table *table, t_philo *philo)
{
	// int	i;
	while (!table->sim_end)
	{
		// printf("sim_end: %d\n", table->sim_end);
		if (table->input.meals_count != -1
			&& philo->meals_eaten == table->input.meals_count)
		{
			table->sim_end = true;
			break ;
		}
		// i = 0;
		// while (i < table->input.philo_count)
		// {
		// 	if (get_time() - philo[i].last_meal > table->input.time_to_die)
		// 	{
		// 		print_philo(table, philo[i].id, DEAD);
		// 		table->sim_end = true;
		// 		break ;
		// 	}
		// 	i++;
		// }
	}
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_count)
	{
		table->philo->last_meal = get_time();
		if (pthread_create(&table->philo[i].philo_thr, NULL, philo_life,
				&table->philo[i]))
			ft_error(5);
		i++;
	}
	sim_finish_die(table, table->philo);
	i = 0;
	while (i < table->input.philo_count)
	{
		if (pthread_join(table->philo[i].philo_thr, NULL))
			ft_error(5);
		// printf("Philo thread %d joined\n", i);
		i++;
	}
	// printf("meals eaten: %d\n", table->philo->meals_eaten);
	// free all threads
	return (0);
}
