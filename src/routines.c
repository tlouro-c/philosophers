/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:02:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 22:39:15 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	even_forks(t_philo *philo,
	t_mutex **first_fork, t_mutex **second_fork)
{
	if (philo->nr % 2 == 1)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

static int	odd_forks(t_philo *philo,
	t_mutex **first_fork, t_mutex **second_fork)
{
	if (philo->nr % 2 == 1)
	{
		*first_fork = philo->right_fork;
		if (!philo->left_fork)
			return (-1);
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	return (0);
}

static int	setup_forks(t_philo *philo, int *death)
{
	t_mutex	*first_fork;
	t_mutex	*second_fork;

	if (philo->info->nr_philo % 2 == 0)
		even_forks(philo, &first_fork, &second_fork);
	else
		if (odd_forks(philo, &first_fork, &second_fork) == -1)
			return (-1);
	if (philo->info->nr_philo % 2 == 1 && philo->nr % 2 == 0)
		usleep(3000);
	pthread_mutex_lock(first_fork);
	print(philo, FORK, death);
	if (philo->info->nr_philo % 2 == 1 && philo->nr % 2 == 1)
		usleep(3000);
	pthread_mutex_lock(second_fork);
	print(philo, FORK, death);
	return (0);
}

void	*routine(t_philo *philo)
{
	int	death;

	death = 0;
	while (!death)
	{
		print(philo, THINK, &death);
		if (death || setup_forks(philo, &death) == -1)
			break ;
		usleep(500);
		print(philo, EAT, &death);
		if (death)
		{
			unlock_both_forks_ret(philo->left_fork, philo->right_fork);
			break ;
		}
		update_last_meal(philo);
		usleep(philo->info->eat_time * 1000);
		unlock_both_forks_ret(philo->left_fork, philo->right_fork);
		if (death || (philo->info->nr_meals != LONG_MAX
				&& update_meal_counter(philo) == -1))
			break ;
		print(philo, SLEEP, &death);
		usleep(philo->info->sleep_time * 1000);
	}
	return (0);
}

void	*garcon_routine(t_garcon *garcon)
{
	t_philo		*current_philo;

	current_philo = garcon->table;
	while (1)
	{
		pthread_mutex_lock(garcon->info->status_mutex);
		if ((get_time() - current_philo->last_meal) > garcon->info->life_time)
			assign_death_info(garcon);
		if (current_philo->full)
			garcon->client_full++;
		pthread_mutex_unlock(garcon->info->status_mutex);
		if (garcon->client_full == garcon->info->nr_philo)
			break ;
		if (garcon->anyone_died)
		{
			print_death(current_philo);
			break ;
		}
		current_philo = current_philo->next;
		if (current_philo == garcon->table)
			usleep(1000);
	}
	return (wait_for_philosophers(garcon));
}
