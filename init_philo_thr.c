/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/07/10 21:33:51 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *table, t_philo *philo)
{
	while (!is_ended(table))
	{
		philo_eat(table, philo);
		if (table->input.philo_count == 1)
		{
			custom_usleep(table->input.time_to_die);
            print_philo(table, philo->id, DEAD);
            mutex_setint(&table->end_lock, &table->sim_end, 1);
			break ;
		}
		if (table->input.meals_count != -1 && philo->meals_eaten >= table->input.meals_count)
			break ;
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
	if (philo->id % 2 == 0)
		custom_usleep(1);
	philo_routine(table, philo);
	return ((void *)0);
}

void	update_death( t_philo *philo, unsigned long now)
{
	unsigned long last_meal_time_since;

	if (mutex_getulong(&philo->philo_lock, &philo->last_meal) != 0)
	{
		last_meal_time_since = now - mutex_getulong(&philo->philo_lock, &philo->last_meal);
		if (last_meal_time_since > (unsigned long)philo->table->input.time_to_die)
		{
			print_philo(philo->table, philo->id, DEAD);
			mutex_setint(&philo->table->end_lock, &philo->table->sim_end, 1);
			return ;
		}
	}
}

int is_satisfied(t_table *table)
{
	int i;
	int is_full;

	i = -1;
	is_full = 0;
	while (++i < table->input.philo_count)
	{
		if (mutex_getint(&table->philo[i].philo_lock, &table->philo[i].meals_eaten) >= table->input.meals_count)
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

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	table->sim_start = get_time();
	while (i < table->input.philo_count)
	{
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
