/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:02:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/20 01:38:44 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	even_forks(t_philo *philo)
{
	if (philo->nr % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, FORK);
		if (!alive(philo))
			return (-1);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		usleep(2 * 1000);
		pthread_mutex_lock(philo->right_fork);
		print(philo, FORK);
		if (!alive(philo))
			return (-1);
		pthread_mutex_lock(philo->left_fork);
	}
	print(philo, FORK);
	if (!alive(philo))
		return (-1);
	return (0);
}

static int	odd_forks(t_philo *philo)
{
	if (philo->nr % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, FORK);
		if (!alive(philo))
			return (-1);
		usleep(2 * 1000);
		if (!philo->left_fork)
			return (-1);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		usleep(2 * 1000);
		if (philo->left_fork)
			pthread_mutex_lock(philo->left_fork);
		if (!alive(philo))
			return (-1);
		print(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
	}
	print(philo, FORK);
	if (!alive(philo))
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

void	*routine(t_philo *philo)
{
	while (1)
	{
		print(philo, THINK);
		if (setup_forks(philo) == -1)
			break ;
		philo->last_meal = get_time();
		print(philo, EAT);
		usleep(philo->info->eat_time * 1000);
		philo->meals_counter++;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (philo->meals_counter == philo->info->nr_meals)
			break ;
		print(philo, SLEEP);
		usleep(philo->info->sleep_time * 1000);
		if (!alive(philo))
			break ;
	}
	return (0);
}

void	*garcon_routine(t_garcon *garcon)
{
	t_philo			*current_philo;
	static int		full;

	current_philo = garcon->table;
	while (1)
	{
		if ((get_time() - current_philo->last_meal) > garcon->info->life_time)
		{
			pthread_mutex_lock(garcon->info->status_mutex);
			garcon->info->death = 1;
			print_death(current_philo);
			pthread_mutex_unlock(garcon->info->status_mutex);
			break ;
		}
		if (current_philo->meals_counter == garcon->info->nr_meals
			&& current_philo->full == 0)
		{
			current_philo->full = 1;
			full++;
			if (full == garcon->info->nr_philo)
				break ;
		}
		current_philo = current_philo->next;
	}
	return (0);
}
