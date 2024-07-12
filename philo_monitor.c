/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:05:18 by marboccu          #+#    #+#             */
/*   Updated: 2024/07/12 16:43:56 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_death(t_philo *philo, unsigned long now)
{
	unsigned long	prev_last_meal;

	if (mutex_getulong(&philo->philo_lock, &philo->last_meal) != 0)
	{
		prev_last_meal = now - mutex_getulong(&philo->philo_lock,
				&philo->last_meal);
		if (prev_last_meal > (unsigned long)philo->table->input.time_to_die)
		{
			print_philo(philo->table, philo->id, DEAD);
			mutex_setint(&philo->table->end_lock, &philo->table->sim_end, 1);
			return ;
		}
	}
}

int	is_satisfied(t_table *table)
{
	int	i;
	int	is_full;

	i = -1;
	is_full = 0;
	while (++i < table->input.philo_count)
	{
		if (mutex_getint(&table->philo[i].philo_lock,
				&table->philo[i].meals_eaten) >= table->input.meals_count)
		{
			is_full++;
			if (is_full == table->input.philo_count)
			{
				mutex_setint(&table->end_lock, &table->sim_end, 1);
				return (1);
			}
		}
	}
	return (0);
}

void	check_philo_health(t_table *table)
{
	int				i;
	unsigned long	now;

	while (!is_ended(table))
	{
		usleep(10);
		now = get_time();
		i = -1;
		if (table->input.meals_count != -1 && is_satisfied(table) == 1)
			break ;
		while (++i < table->input.philo_count)
		{
			update_death(&table->philo[i], now);
			if (is_ended(table))
				break ;
		}
	}
}
