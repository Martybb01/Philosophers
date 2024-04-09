/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:36:38 by marboccu          #+#    #+#             */
/*   Updated: 2024/04/09 23:55:16 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> // mutex: init, destroy, lock, unlock
						// thread: create,join, detach
# include <stdbool.h> // bool
# include <stdint.h>
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> //getttimeofday
# include <unistd.h>   // write, usleep

# define MAX_PHILO 200
# define INT_MAX 2147483647

# define RESET "\033[0m"
# define RED "\033[1;31m"     // errors input
# define GREEN "\033[1;32m"   // philo eating
# define YELLOW "\033[1;33m"  // philo thinking
# define MAGENTA "\033[1;35m" // philo died
# define CYAN "\033[1;36m"    // philo sleeping

# define EAT "is eating 🍝\n"
# define SLEEP "is sleeping 💤\n"
# define THINK "is thinking 💭\n"
# define FORK "has taken a fork 🍴\n"
# define DEAD "died 💀"

# define WRONG_ARG_NUM "Error: wrong number of arguments ❌\n"
# define INVALID_PHILO "Error: Invalid philo input 🧐\n"
# define INVALID_DEAD "Error: Invalid time_to_die ⏰\n"
# define INVALID_EAT "Error: Invalid time_to_eat ⏰\n"
# define INVALID_SLEEP "Error: Invalid time_to_sleep ⏰\n"
# define INVALID_MEALS "Error: Invalid meals_count 🍝\n"

typedef struct s_input
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_count;
}					t_input;

typedef struct s_philo
{
	struct s_table	*table;
	int				id;
	pthread_t		philo_thr;
	int				meals_eaten;
	int				last_meal;
	int				time_to_die;
	pthread_mutex_t	lock;
	int				left_fork;
	int				right_fork;

}					t_philo;

typedef struct s_table
{
	int				philos;
	long			sim_start;
	int				sim_end;
	t_input			input;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_t		monitor_thr;
	// int				meals;
	// pthread_mutex_t	print_lock;

}					t_table;

// ---------------UTILS----------------
void				ft_error(int code);
long				get_time(void);
void				custom_usleep(unsigned int usec);
void				print_philo(t_table *table, int id, char *msg);

// ---------------INIT---------------
int					init_input(int ac, char **av, t_table *table);
int					init_philo(t_table *table);
int					init_philo_threads(t_table *table);

// ---------------LIBFT----------------
int					ft_atoi(char *str);
int					ft_strlen(char *str);
void				ft_putstr_fd(char *str, int fd);

// ---------------PHILOLIFE-----------------
void				philo_sleep(t_table *table, t_philo *philo);
void				philo_eat(t_table *table, t_philo *philo);
void				philo_think(t_table *table, t_philo *philo);

#endif
