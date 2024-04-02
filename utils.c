/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:56 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/02 12:13:20 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		ft_putstr_fd("Error: Invalid time\n", 2);
	}
	if (code == 4)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("Error: Invalid meals\n", 2);
	}
	exit(1);
}
