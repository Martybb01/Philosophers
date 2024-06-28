/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/06/28 14:29:28 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *table, t_philo *philo)
{
	while (!is_ended(table))
	{
		philo_eat(table, philo);
		if (table->input.philo_count == 1)
			break ;
		if (table->input.meals_count != -1)
		{
			if (mutex_intincr(&philo->philo_lock,
					&philo->meals_eaten) == table->input.meals_count)
				break ;
		}
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
	if (philo->id % 2 != 0)
		custom_usleep(1);
	mutex_setulong(&philo->meal_lock, &philo->last_meal, get_time());
	philo_routine(table, philo);
	return ((void *)0);
}

void	update_philo_status(t_table *table, t_philo *philo, unsigned long now,
		int *is_full)
{
	unsigned long	last_meal_time_since;

	if (table->input.meals_count != -1 && mutex_getint(&philo->philo_lock,
			&philo->meals_eaten) == table->input.meals_count)
	{
		mutex_intincr(&table->full_lock, is_full);
		return ;
	}
	if (mutex_getulong(&philo->meal_lock, &philo->last_meal) != 0)
	{
		last_meal_time_since = now - mutex_getulong(&philo->meal_lock,
				&philo->last_meal);
		if (last_meal_time_since > (unsigned long)table->input.time_to_die + 3)
		{
			print_philo(table, philo->id, DEAD);
			mutex_setint(&table->end_lock, &table->sim_end, 1);
		}
	}
}

void	check_philo_health(t_table *table)
{
	int				i;
	int				is_full;
	unsigned long	now;

	is_full = 0;
	while (mutex_getint(&table->full_lock, &is_full) != table->input.philo_count
		&& !is_ended(table))
	{
		now = get_time();
		i = -1;
		mutex_setint(&table->full_lock, &is_full, 0);
		while (++i < table->input.philo_count)
		{
			update_philo_status(table, &table->philo[i], now, &is_full);
			if (is_ended(table))
				break ;
		}
	}
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	table->sim_start = get_time();
	while (i < table->input.philo_count)
	{
		table->philo[i].last_meal = 0;
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
