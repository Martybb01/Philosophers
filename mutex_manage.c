/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:13:23 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/25 11:21:00 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mutex_getint(pthread_mutex_t *mutex, int *value)
{
	int ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

uint64_t mutex_getuint64(pthread_mutex_t *mutex, unsigned long *value)
{
	uint64_t ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void mutex_setint(pthread_mutex_t *mutex, int *value, int new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

void mutex_setuint64(pthread_mutex_t *mutex, unsigned long *value, unsigned long new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

int mutex_intincr(pthread_mutex_t *mutex, int *value)
{
	int ret;

	pthread_mutex_lock(mutex);
	*value += 1;
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}