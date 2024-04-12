/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:59:42 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/12 10:55:19 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_malloc(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->input.philo_count);
	if (!table->philo)
		ft_error(4);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->input.philo_count);
	if (!table->forks)
		ft_error(4);
	table->philo->philo_thr = (pthread_t)malloc(sizeof(pthread_t)
			* table->input.philo_count);
	if (!table->philo->philo_thr)
		ft_error(4);
}

void	init_mutex(t_table *table, t_philo *philo)
{
	int	i;

	if (pthread_mutex_init(&table->dead_lock, NULL))
		ft_error(5);
	if (pthread_mutex_init(&table->print_lock, NULL))
		ft_error(5);
	i = 0;
	while (i < table->input.philo_count)
	{
		if (pthread_mutex_init(&philo[i].philo_lock, NULL))
			ft_error(5);
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error(5);
		i++;
	}
}

int	init_philo(t_table *table)
{
	int	i;

	init_malloc(table);
	// printf("table->input.philo_count: %d\n", table->input.philo_count);
	init_mutex(table, table->philo);
	// printf("forks initialized\n");
	i = 0;
	while (i < table->input.philo_count)
	{
		table->sim_start = get_time();
		table->philo[i].table = table;
		// printf("sim_start: %ld\n", table->sim_start);
		table->philo[i].id = i + 1;
		// printf("philo %d id: %d\n", i, table->philo[i].id);
		table->philo[i].meals_eaten = 0;
		if (i == 0)
		{
			table->philo[i].left_fork = 0;
			table->philo[i].right_fork = table->input.philo_count - 1;
		}
		else if (i == table->input.philo_count - 1)
		{
			table->philo[i].left_fork = table->input.philo_count - 2;
			table->philo[i].right_fork = table->input.philo_count - 1;
		}
		else
		{
			table->philo[i].right_fork = table->philo[i].id - 2;
			table->philo[i].left_fork = table->philo[i].id - 1;
		}
		// printf("philo %d left fork: %d\n", table->philo[i].id,
		// 	table->philo[i].left_fork);
		// printf("philo %d right fork: %d\n", table->philo[i].id,
		// 	table->philo[i].right_fork);
		table->philo[i].time_to_die = table->input.time_to_die;
		// printf("philo %d time to die: %d\n", table->philo[i].id,
		// table->philo[i].time_to_die);
		table->philo[i].last_meal = get_time();
		// printf("philo %d last meal: %d\n", table->philo[i].id,
		// table->philo[i].last_meal);
		i++;
	}
	// printf("philo initialized\n");
	return (0);
}
