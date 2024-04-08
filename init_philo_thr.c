/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_thr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:41:07 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/08 18:19:55 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (philo->id % 2)
		custom_usleep(1000);
	// while (!table->sim_end)
	// {
	// }
	// printf("philo %d is alive\n", philo->id);
	print_philo(table, philo->id, THINK);
	philo->meals_eaten++;
	philo->meals_eaten++;
	return (NULL);
}

int	sim_finish_die(t_table *table, t_philo *philo)
{
	// printf("sim_end: %d\n", table->sim_end);
	if (table->input.meals_count != -1
		&& philo->meals_eaten == table->input.meals_count)
	{
		// printf("MANGIATO %d\n", philo->meals_eaten);
		print_philo(table, philo->id, EAT);
		table->sim_end = true;
		return (0);
	}
	if (get_time() - philo->last_meal > table->input.time_to_die)
	{
		table->sim_end = true;
		print_philo(table, philo->id, DEAD);
		return (0);
	}
	return (1);
}

int	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->input.philo_count)
	{
		table->philo->last_meal = get_time();
		if (pthread_create(&table->philo[i].philo_thr, NULL, philo_life,
				&table->philo[i]))
			ft_error(5);
		i++;
	}
	if (!sim_finish_die(table, table->philo))
		printf("eat or die\n");
	i = 0;
	while (i < table->input.philo_count)
	{
		if (pthread_join(table->philo[i].philo_thr, NULL))
			ft_error(5);
		printf("Philo thread %d joined\n", i);
		i++;
	}
	printf("meals eaten: %d\n", table->philo->meals_eaten);
	// free all threads
	return (0);
}
