/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:35:49 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/02 12:07:27 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	digit_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parse_input(char **av)
{
	if (digit_check(av[1]) || ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > MAX_PHILO)
		ft_error(2);
	if (digit_check(av[2]) || ft_atoi(av[2]) <= 0)
		ft_error(3);
	if (digit_check(av[3]) || ft_atoi(av[3]) <= 0)
		ft_error(3);
	if (digit_check(av[4]) || ft_atoi(av[4]) <= 0)
		ft_error(3);
	if (av[5] && (digit_check(av[5]) || ft_atoi(av[5]) <= 0))
		ft_error(4);
	return (0);
}
