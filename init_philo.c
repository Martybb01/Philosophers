/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:59:42 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/06 19:36:43 by marboccu         ###   ########.fr       */
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

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->lock, NULL))
		ft_error(5);
	while (i < table->input.philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

int	init_philo(t_table *table)
{
	int	i;

	init_malloc(table);
	printf("table->input.philo_count: %d\n", table->input.philo_count);
	init_forks(table);
	printf("forks initialized\n");
	i = 0;
	while (i < table->input.philo_count)
	{
		table->sim_start = get_time();
		// printf("sim_start: %ld\n", table->sim_start);
		table->philo[i].id = i + 1;
		printf("philo %d id: %d\n", i, table->philo[i].id);
		table->philo[i].meals_eaten = 0;
		table->philo[i].left_fork = i;
		printf("philo %d left fork: %d\n", table->philo[i].id,
			table->philo[i].left_fork);
		table->philo[i].right_fork = (i + 1) % table->input.philo_count;
		printf("philo %d right fork: %d\n", table->philo[i].id,
			table->philo[i].right_fork);
		table->philo[i].time_to_die = table->input.time_to_die;
		// printf("philo %d time to die: %d\n", table->philo[i].id,
		// 	table->philo[i].time_to_die);
		table->philo[i].last_meal = get_time();
		printf("philo %d last meal: %ld\n", table->philo[i].id,
			table->philo[i].last_meal);
		pthread_mutex_init(&table->philo[i].lock, NULL);
		i++;
	}
	printf("philo initialized\n");
	return (0);
}
