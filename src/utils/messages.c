/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:39:36 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 00:15:06 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *msg, int *death)
{
	pthread_mutex_lock(philo->info->status_mutex);
	if (philo->info->death)
		*death = 1;
	else
	{
		printf("%-5li %3li %s\n", (get_time() - philo->info->start),
			philo->nr, msg);
		*death = 0;
	}
	pthread_mutex_unlock(philo->info->status_mutex);
}

void	print_death(t_philo *philo)
{
	printf("%-5li %3li died\n", (get_time() - philo->info->start), philo->nr);
}

void	not_enough_arguments(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 121);
	exit(255);
}

void	error_exiting(t_philo *table, int error_code)
{
	free_table(table);
	write(2, "Error, exiting...\n", 19);
	exit(error_code);
}
