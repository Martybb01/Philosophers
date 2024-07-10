/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:54:25 by marboccu          #+#    #+#             */
/*   Updated: 2024/07/10 19:51:00 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_table *table, t_philo *philo)
{
	print_philo(table, philo->id, SLEEP);
	custom_usleep(table->input.time_to_sleep);
}

void	philo_think(t_table *table, t_philo *philo)
{
	print_philo(table, philo->id, THINK);
}

void	philo_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_philo(table, philo->id, FORK);
	if (table->input.philo_count == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_philo(table, philo->id, FORK);
	print_philo(table, philo->id, EAT);
	custom_usleep(table->input.time_to_eat);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
}
