/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:22:30 by marboccu          #+#    #+#             */
/*   Updated: 2024/05/04 15:23:09 by marboccu         ###   ########.fr       */
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
 * @brief Sleep for a given amount of time in milliseconds.
 * @param usec The amount of time to sleep in milliseconds.
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
