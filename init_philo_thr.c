/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/17 12:06:03 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_ended(t_table *table)
{
	int	res;

	pthread_mutex_lock(&table->end_lock);
	res = table->sim_end;
	pthread_mutex_unlock(&table->end_lock);
	return (res);
}

void	philo_routine(t_table *table, t_philo *philo)
{
	while (!is_ended(table))
	{
		philo_eat(table, philo);
		if (table->input.philo_count == 1)
			break ;
		if (table->input.meals_count != -1)
		{
			pthread_mutex_lock(&philo->philo_lock);
			philo->meals_eaten += 1;
			if (philo->meals_eaten == table->input.meals_count)
			{
				pthread_mutex_unlock(&philo->philo_lock);
				print_philo(table, philo->id, MEALS);
				break ;
			}
			pthread_mutex_unlock(&philo->philo_lock);
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
	if (philo->id % 2 == 0)
		custom_usleep(1);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
	philo_routine(table, philo);
	return ((void *)0);
}

// void	sim_finish_die(t_table *table, t_philo *philo, int i)
// {
// 	int	is_full;

// 	is_full = 0;
// 	while (++i < table->input.philo_count)
// 	{
// 		philo = &table->philo[i];
// 		pthread_mutex_lock(&philo->philo_lock);
// 		if (table->input.meals_count != -1
// 			&& philo->meals_eaten == table->input.meals_count)
// 		{
// 			is_full++;
// 			pthread_mutex_unlock(&philo->philo_lock);
// 			continue ;
// 		}
// 		if (philo->last_meal != 0 && (get_time()
// 				- philo->last_meal > (uint64_t)table->input.time_to_die))
// 		{
// 			print_philo(table, philo->id, DEAD);
// 			pthread_mutex_unlock(&philo->philo_lock);
// 			pthread_mutex_lock(&table->end_lock);
// 			table->sim_end = 1;
// 			pthread_mutex_unlock(&table->end_lock);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&philo->philo_lock);
// 	}
// }

void	check_philo_health(t_table *table)
{
	int		i;
	int		is_full;
	t_philo	*philo;

	is_full = 0;
	philo = NULL;
	while (is_full != table->input.philo_count && !is_ended(table))
	{
		i = -1;
		is_full = 0;
		// sim_finish_die(table, philo, i);
		while (++i < table->input.philo_count)
		{
			philo = &table->philo[i];
			pthread_mutex_lock(&philo->philo_lock);
			if (table->input.meals_count != -1
				&& philo->meals_eaten == table->input.meals_count)
			{
				is_full++;
				pthread_mutex_unlock(&philo->philo_lock);
				continue ;
			}
			// pthread_mutex_unlock(&philo->philo_lock);
			// pthread_mutex_lock(&philo->philo_lock);
			// custom_usleep(1);
			if (philo->last_meal != 0 && (get_time()
					- philo->last_meal >= (uint64_t)table->input.time_to_die))
			{
				print_philo(table, philo->id, DEAD);
				pthread_mutex_unlock(&philo->philo_lock);
				pthread_mutex_lock(&table->end_lock);
				table->sim_end = 1;
				pthread_mutex_unlock(&table->end_lock);
				break ;
			}
			pthread_mutex_unlock(&philo->philo_lock);
		}
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_count)
	{
		pthread_mutex_destroy(&table->philo[i].philo_lock);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->end_lock);
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philo);
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
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
