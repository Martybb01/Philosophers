/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:35:49 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/09 22:12:18 by marboccu         ###   ########.fr       */
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

int	init_input_struct(int ac, char **av, t_table *table)
{
	table->input.philo_count = ft_atoi(av[1]);
	table->input.time_to_die = ft_atoi(av[2]);
	table->input.time_to_eat = ft_atoi(av[3]);
	table->input.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->input.meals_count = ft_atoi(av[5]);
	else
		table->input.meals_count = -1;
	return (0);
}

int	init_input(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (printf(RED WRONG_ARG_NUM RESET), 1);
	if (digit_check(av[1]) || ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > MAX_PHILO)
		return (printf(RED INVALID_PHILO RESET), 1);
	if (digit_check(av[1]) || ft_atoi(av[2]) <= 0)
		return (printf(RED INVALID_DEAD RESET), 1);
	if (digit_check(av[3]) || ft_atoi(av[3]) <= 0)
		return (printf(RED INVALID_EAT RESET), 1);
	if (digit_check(av[4]) || ft_atoi(av[4]) <= 0)
		return (printf(RED INVALID_SLEEP RESET), 1);
	if (av[5] && (digit_check(av[5]) || ft_atoi(av[5]) <= 0))
		return (printf(RED INVALID_MEALS RESET), 1);
	if (init_input_struct(ac, av, table) == 1)
		return (1);
	// printf("philo_count: %d\n", table->input.philo_count);
	// printf("time_to_die: %d\n", table->input.time_to_die);
	// printf("time_to_eat: %d\n", table->input.time_to_eat);
	// printf("time_to_sleep: %d\n", table->input.time_to_sleep);
	// printf("meals: %d\n", table->input.meals_count);
	return (0);
}
