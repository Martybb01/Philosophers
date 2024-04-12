/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/12 13:02:51 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (!table->sim_end)
	{
		philo_eat(table, philo);
		if (table->input.meals_count != -1)
		{
			pthread_mutex_lock(&philo->philo_lock);
			philo->meals_eaten += 1;
			if (philo->meals_eaten == table->input.meals_count)
			{
				pthread_mutex_unlock(&philo->philo_lock);
				print_philo(table, philo->id, MEALS);
				break ;
			}
			pthread_mutex_unlock(&philo->philo_lock);
		}
		philo_sleep(table, philo);
		philo_think(table, philo);
	}
	return ((void *)0);
}

// void	sim_finish_die(t_table *table, t_philo *philo)
// {
// 	int	i;

// 	// pthread_mutex_lock(&table->lock);
// 	while (!table->sim_end)
// 	{
// 		pthread_mutex_lock(&table->lock);
// 		// printf("sim_end: %d\n", table->sim_end);
// 		if (table->input.meals_count != -1
// 			&& philo->meals_eaten == table->input.meals_count)
// 		{
// 			table->sim_end = true;
// 			break ;
// 		}
// 		pthread_mutex_unlock(&table->lock);
// 		i = 0;
// 		while (i < table->input.philo_count)
// 		{
// 			pthread_mutex_lock(&philo[i].lock);
// 			if (get_time() - philo[i].last_meal >= table->input.time_to_die)
// 			{
// 				print_philo(table, philo[i].id, DEAD);
// 				pthread_mutex_lock(&table->lock);
// 				table->sim_end = true;
// 				pthread_mutex_unlock(&table->lock);
// 				break ;
// 			}
// 			pthread_mutex_unlock(&philo[i].lock);
// 			i++;
// 		}
// 	}
// 	// pthread_mutex_unlock(&table->lock);
// }

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_count)
	{
		pthread_mutex_destroy(&table->philo[i].philo_lock);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->print_lock);
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_count)
	{
		table->philo[i].last_meal = get_time();
		if (pthread_create(&table->philo[i].philo_thr, NULL, philo_life,
				&table->philo[i]))
			ft_error(5);
		i++;
	}
	// sim_finish_die(table, table->philo);
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
