/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:54:25 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/12 13:57:15 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_table *table, t_philo *philo)
{
	// pthread_mutex_lock(&philo->lock);
	print_philo(table, philo->id, SLEEP);
	// pthread_mutex_unlock(&philo->lock);
	custom_usleep(table->input.time_to_sleep);
}

void	philo_think(t_table *table, t_philo *philo)
{
	// pthread_mutex_lock(&philo->philo_lock);
	print_philo(table, philo->id, THINK);
	// pthread_mutex_unlock(&philo->philo_lock);
}

void	philo_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_philo(table, philo->id, FORK);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_philo(table, philo->id, FORK);
	print_philo(table, philo->id, EAT);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
	custom_usleep(table->input.time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	print_philo(table, philo->id, FORK_DOWN);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	print_philo(table, philo->id, FORK_DOWN);
}
