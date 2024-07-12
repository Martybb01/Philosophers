/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/07/12 13:05:35 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *table, t_philo *philo)
{
	while (!is_ended(table))
	{
		philo_eat(table, philo);
		if (table->input.philo_count == 1)
		{
			custom_usleep(table->input.time_to_die);
			print_philo(table, philo->id, DEAD);
			mutex_setint(&table->end_lock, &table->sim_end, 1);
			break ;
		}
		if (table->input.meals_count != -1
			&& philo->meals_eaten >= table->input.meals_count)
			break ;
		philo_sleep(table, philo);
		philo_think(table, philo);
	}
}

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (philo->id % 2 == 0)
		custom_usleep(1);
	philo_routine(table, philo);
	return ((void *)0);
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	table->sim_start = get_time();
	while (i < table->input.philo_count)
	{
		if (pthread_create(&table->philo[i].philo_thr, NULL, philo_life,
				&table->philo[i]))
			ft_error(5);
		i++;
	}
	check_philo_health(table);
	i = 0;
	while (i < table->input.philo_count)
	{
		if (pthread_join(table->philo[i].philo_thr, NULL))
			ft_error(5);
		i++;
	}
	destroy_mutex(table);
	return (0);
}
