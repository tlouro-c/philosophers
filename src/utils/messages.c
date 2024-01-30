/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:39:36 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/30 15:45:52 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *msg, int *death)
{
	pthread_mutex_lock(philo->info->status_mutex);
	if (philo->info->death)
	{
		pthread_mutex_unlock(philo->info->status_mutex);
		*death = 1;
		return ;
	}
	pthread_mutex_unlock(philo->info->status_mutex);
	printf("%-5li %3li %s\n", (get_time() - philo->info->start),
		philo->nr, msg);
	*death = 0;
}

void	print_death(t_philo *philo)
{
	printf("%-5li %3li died\n", (get_time() - philo->info->start), philo->nr);
}

void	not_enough_arguments(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 121);
	return ;
}

void	error_exiting(t_philo *table)
{
	free_table(table);
	write(2, "Error, exiting...\n", 19);
	return ;
}

void	clean_exit(t_garcon *garcon)
{
	free_table(garcon->table);
	free(garcon->info);
	free(garcon);
	return ;
}
