/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:59:42 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/06 12:26:28 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(t_philo *philo)
{
	printf("philo %d is thinking\n", philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("philo %d has taken a fork\n", philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("philo %d is eating\n", philo->id);
	usleep(philo->time_to_die * 1000);
	philo->meals_eaten++;
	printf("melas eaten: %d\n", philo->meals_eaten);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf("philo %d is sleeping\n", philo->id);
	usleep(philo->time_to_die * 1000);
	return (NULL);
}

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
	if (pthread_mutex_init(&table->forks[i], NULL))
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
		table->philo[i].id = i + 1;
		printf("philo %d id: %d\n", i, table->philo[i].id);
		table->philo[i].meals_eaten = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1)
			% table->input.philo_count];
		table->philo[i].time_to_die = table->input.time_to_die;
		table->philo[i].last_meal = get_time();
		printf("philo %d last meal: %d\n", table->philo[i].id,
			table->philo[i].last_meal);
		pthread_mutex_init(&table->philo[i].lock, NULL);
		i++;
	}
	printf("philo initialized\n");
	i = 0;
	printf("table->input.philo_count: %d\n", table->input.philo_count);
	while (i < table->input.philo_count)
	{
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
