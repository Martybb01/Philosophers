/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:56 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/25 11:43:34 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get the current time in milliseconds.
 * @return The current time in milliseconds as a long.
 * @note track how long a philo has been thinking, eating, or sleeping.
 */
unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief Sleep for a given amount of time in microseconds.
 * @param usec The amount of time to sleep in microseconds.
 */
void	custom_usleep(unsigned long milli)
{
	unsigned long	start_time;
	unsigned long	target_time;

	start_time = get_time();
	target_time = start_time + (milli);
	while (get_time() < target_time)
		usleep(100);
}

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
