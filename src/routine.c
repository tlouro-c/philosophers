/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:02:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/18 16:08:45 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	even_forks(t_philo *philo)
{
	if (philo->nr % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_taken_fork(philo->nr, philo->info->start_time);
		if (starvation_check(philo) == -1)
			return (-1);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		usleep(2 * 1000);
		pthread_mutex_lock(philo->right_fork);
		print_taken_fork(philo->nr, philo->info->start_time);
		if (starvation_check(philo) == -1)
			return (-1);
		pthread_mutex_lock(philo->left_fork);
	}
	print_taken_fork(philo->nr, philo->info->start_time);
	if (starvation_check(philo) == -1)
		return (-1);
	return (0);
}

static int	odd_forks(t_philo *philo)
{
	if (philo->nr % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_taken_fork(philo->nr, philo->info->start_time);
		if (starvation_check(philo) == -1)
			return (-1);
		usleep(2 * 1000);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		usleep(2 * 1000);
		if (philo->left_fork)
			pthread_mutex_lock(philo->left_fork);
		if (starvation_check(philo) == -1)
			return (-1);
		print_taken_fork(philo->nr, philo->info->start_time);
		pthread_mutex_lock(philo->right_fork);
	}
	print_taken_fork(philo->nr, philo->info->start_time);
	if (starvation_check(philo) == -1)
		return (-1);
	return (0);
}

static int	setup_forks(t_philo *philo)
{
	if (philo->info->nr_philo % 2 == 0)
	{
		if (even_forks(philo) == -1)
			return (-1);
	}
	else
		if (odd_forks(philo) == -1)
			return (-1);
	return (0);
}

static int	thread_exit(t_philo *philo)
{
	pthread_mutex_destroy(philo->right_fork);
	if (philo->left_fork)
		pthread_mutex_destroy(philo->left_fork);
	pthread_mutex_destroy(philo->info->is_dead_mutex);
	if (philo->meals_counter
		== philo->info->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		if (setup_forks(philo) == -1)
			break ;
		philo->last_meal_time = get_time();
		print_is_eating(philo->nr, philo->info->start_time);
		usleep(philo->info->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->meals_counter++;
		if (philo->meals_counter
			== philo->info->number_of_times_each_philosopher_must_eat)
			break ;
		print_is_sleeping(philo->nr, philo->info->start_time);
		usleep(philo->info->time_to_sleep * 1000);
		if (starvation_check(philo) == -1)
			 break ;
		print_is_thinking(philo->nr, philo->info->start_time);
	}
	if (thread_exit(philo) == 0)
		exit (0);
	return (0);
}
