/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:12:50 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/22 23:29:28 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_last_meal(t_philo *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(philo->info->status_mutex);
	if (!philo->info->death)
		philo->last_meal = now;
	pthread_mutex_unlock(philo->info->status_mutex);
}

int	update_meal_counter(t_philo *philo)
{
	pthread_mutex_lock(philo->info->status_mutex);
	philo->meals_counter++;
	if (philo->meals_counter == philo->info->nr_meals)
	{
		philo->full = 1;
		pthread_mutex_unlock(philo->info->status_mutex);
		return (-1);
	}
	pthread_mutex_unlock(philo->info->status_mutex);
	return (0);
}

void	*wait_for_philosophers(t_garcon *garcon)
{
	t_philo	*tmp;

	tmp = garcon->table->next;
	while (tmp != garcon->table)
	{
		if (pthread_join(tmp->thread, NULL) != 0)
			return ((void *)tmp);
		tmp = tmp->next;
	}
	pthread_join(garcon->table->thread, NULL);
	return (0);
}

int	unlock_both_forks_ret(t_mutex *first_fork, t_mutex *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (-1);
}

void	assign_death_info(t_garcon *garcon)
{
	garcon->anyone_died = 1;
	garcon->info->death = 1;
}
