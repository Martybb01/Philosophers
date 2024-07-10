/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:59:42 by marboccu          #+#    #+#             */
/*   Updated: 2024/07/10 17:39:36 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_malloc(t_table *table)
{
	table->philo = (t_philo *)malloc(sizeof(t_philo)
			* table->input.philo_count);
	if (!table->philo)
	{
		free(table);
		ft_error(4);
	}
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->input.philo_count);
	if (!table->forks)
	{
		free(table->philo);
		free(table);
		ft_error(4);
	}
}

void	init_mutex(t_table *table, t_philo *philo)
{
	int	i;

	if (pthread_mutex_init(&table->end_lock, NULL))
		ft_error(5);
	if (pthread_mutex_init(&table->print_lock, NULL))
		ft_error(5);
	if (pthread_mutex_init(&table->full_lock, NULL))
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

void	assign_forks(t_table *table, int i)
{
	if (i == 0)
	{
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = table->input.philo_count - 1;
	}
	else
	{
		table->philo[i].left_fork = i - 1;
		table->philo[i].right_fork = i;
	}
}

int	init_philo(t_table *table)
{
	int	i;

	init_malloc(table);
	init_mutex(table, table->philo);
	i = 0;
	while (i < table->input.philo_count)
	{
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		assign_forks(table, i);
		table->philo[i].time_to_die = table->input.time_to_die;
		table->philo[i].last_meal = 0;
		i++;
	}
	return (0);
}
