/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:36:38 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/02 12:13:59 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> // mutex: init, destroy, lock, unlock
						// thread: create,join, detach
# include <stdint.h>
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> //getttimeofday
# include <unistd.h>   // write, usleep

# define MAX_PHILO 200
# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[1;31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

// typedef struct t_philo
// {
// } s_philo

// ---------------UTILS----------------
void	ft_error(int code);

// ---------------PARSING---------------
int		parse_input(char **av);

// ---------------LIBFT----------------
int		ft_atoi(char *str);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);

#endif
