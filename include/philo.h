/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:37:40 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/20 13:15:31 by tlouro-c         ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DIED "died"

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

typedef struct s_info
{
	long	start;
	long	nr_philo;
	long	life_time;
	long	eat_time;
	long	sleep_time;
	long	nr_meals;
	int		death;
	t_mutex	*status_mutex;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_info			*info;
	long			nr;
	long			last_meal;
	long			meals_counter;
	int				full;
	struct s_philo	*next;
}	t_philo;

typedef struct s_garcon
{
	pthread_t	thread;
	t_philo		*table;
	t_info		*info;
	int			client_full;
	int			anyone_died;
}	t_garcon;

/* -------------------------------------------------------------------------- */
/*                                  messages                                  */
/* -------------------------------------------------------------------------- */

void		print_death(t_philo *philo);
void		print(t_philo *philo, char *msg);
void		not_enough_arguments(void);
void		error_exiting(t_philo *table, int error_code);
void		free_table(t_philo *table);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

void		*ft_calloc(int quantity, int size);
long		ft_atol(const char *s);
long		get_time(void);
t_philo		*generate_table(t_info *info);
t_garcon	*generate_garcon(t_info *info);
void		launch_threads(t_garcon *garcon);
int			alive(t_philo *philo);

void		*routine(t_philo *philo);
void		*garcon_routine(t_garcon *garcon);

void		update_last_meal(t_philo *philo);
int			update_meal_counter(t_philo *philo);
void		*wait_for_philosophers(t_garcon *garcon);
int			unlock_fork_ret(t_mutex *fork);
int			unlock_both_forks_ret(t_mutex *first_fork, t_mutex *second_fork);

#endif /* PHILO_H */
