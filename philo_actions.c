/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:54:25 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/09 23:55:26 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_table *table, t_philo *philo)
{
	print_philo(table, philo->id, SLEEP);
	custom_usleep(table->input.time_to_sleep);
}

void	philo_think(t_table *table, t_philo *philo)
{
	print_philo(table, philo->id, THINK);
}
