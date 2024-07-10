/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:56 by marboccu          #+#    #+#             */
/*   Updated: 2024/07/10 20:58:14 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_table *table, int id, char *msg)
{
	unsigned long	now;

	now = get_time();
	pthread_mutex_lock(&table->print_lock);
	if (!is_ended(table))
	{
		printf("%s", CYAN);
		printf("%ld ", now - table->sim_start);
		printf("%s", RESET);
		printf("%s", MAGENTA);
		printf("%d ", id);
		printf("%s", RESET);
		printf("%s", msg);
	}
	pthread_mutex_unlock(&table->print_lock);
}

int	is_ended(t_table *table)
{
	int	res;

	res = mutex_getint(&table->end_lock, &table->sim_end);
	return (res);
}

void	ft_error(int code)
{
	if (code == 4)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("Error: Malloc failed\n", 2);
	}
	if (code == 5)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("Error: Invalid thread\n", 2);
	}
	exit(1);
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
