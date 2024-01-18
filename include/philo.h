/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:37:40 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/18 11:10:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct timeval	t_time;

typedef struct s_info
{
	long			start_time;
	long			nr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	int				is_dead;
	pthread_mutex_t	*is_dead_mutex;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_info			*info;
	long			nr;
	long			last_meal_time;
	long			meals_counter;
	struct s_philo	*next;
}	t_philo;

/* -------------------------------------------------------------------------- */
/*                                  philo_msg                                 */
/* -------------------------------------------------------------------------- */

void	print_taken_fork(int philo_nr, long start_ms);
void	print_is_eating(int philo_nr, long start_ms);
void	print_is_sleeping(int philo_nr, long start_ms);
void	print_is_thinking(int philo_nr, long start_ms);
void	print_died(int philo_nr, long start_ms);

/* -------------------------------------------------------------------------- */
/*                                  error_msg                                 */
/* -------------------------------------------------------------------------- */

void	not_enough_arguments(void);
void	error_exiting(int error_code);
void	free_table_exit(t_philo *philo);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

void	*ft_calloc(int quantity, int size);
long	ft_atol(const char *s);
long	get_time(void);
void	generate_table(int nr_philo, t_info *info);
int		starvation_check(t_philo *philo);

void	*routine(t_philo *philo);

#endif /* PHILO_H */
