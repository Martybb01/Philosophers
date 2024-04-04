/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:59:42 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/03 23:02:37 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(t_philo *philo)
{
	printf("philo id: %d\n", philo->id);
	pthread_mutex_lock(philo->left_fork);
	philo->meals_eaten++;
	printf("melas eaten: %d\n", philo->meals_eaten);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	init_philo(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->input.philo_count);
	if (!table->philo)
		ft_error(4);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->input.philo_count);
	if (!table->forks)
		ft_error(4);
	i = 0;
	printf("table->input.philo_count: %d\n", table->input.philo_count);
	while (i < table->input.philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	printf("forks initialized\n");
	i = 0;
	while (i < table->input.philo_count)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].left_fork = &table->forks[i];
		printf("left fork: %p\n", table->philo[i].left_fork);
		table->philo[i].right_fork = &table->forks[(i + 1)
			% table->input.philo_count];
		table->philo[i].time_to_die = table->input.time_to_die;
		i++;
	}
	printf("philo initialized\n");
	i = 0;
	printf("table->input.philo_count: %d\n", table->input.philo_count);
	while (i < table->input.philo_count)
	{
		printf("philo id: %d\n", table->philo[i].id);
		if (pthread_create(&table->philo[i].philo_thr, NULL, (void *)philo_life,
				&table->philo[i]))
			ft_error(5);
		i++;
	}
	i = 0;
	while (i < table->input.philo_count)
	{
		if (pthread_join(table->philo[i].philo_thr, NULL))
			ft_error(5);
		i++;
	}
	printf("meals eaten: %d\n", table->philo[0].meals_eaten);
	printf("philo joined\n");
	return (0);
}
