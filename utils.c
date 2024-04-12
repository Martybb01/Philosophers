/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:56 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/12 12:57:43 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get the current time in milliseconds.
 * @return The current time in milliseconds as a long.
 * @note track how long a philo has been thinking, eating, or sleeping.
 */
long	get_time(void)
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
void	custom_usleep(unsigned int milli)
{
	long	start_time;
	long	target_time;

	start_time = get_time();
	target_time = start_time + (milli);
	while (get_time() < target_time)
		usleep(100);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

void	print_philo(t_table *table, int id, char *msg)
{
	long	now;

	(void)id;
	(void)msg;
	now = get_time();
	pthread_mutex_lock(&table->print_lock);
	if (!(table->sim_end))
	{
		printf("%s", CYAN);
		printf("%ld", now - table->sim_start);
		printf("%s", RESET);
		printf("%s", MAGENTA);
		printf(" %d ", id);
		printf("%s", RESET);
		printf("%s", msg);
	}
	pthread_mutex_unlock(&table->print_lock);
}

void	ft_error(int code)
{
	if (code == 1)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
	}
	if (code == 2)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("Error: Invalid philo input\n", 2);
	}
	if (code == 3)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("Error: Invalid time ⏰\n", 2);
	}
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
