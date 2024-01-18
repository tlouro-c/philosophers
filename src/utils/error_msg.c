/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:47:47 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/18 09:52:50 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	not_enough_arguments(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 121);
	exit(255);
}

void	error_exiting(int error_code)
{
	write(2, "Error, exiting...\n", 19);
	exit(error_code);
}

void	free_table_exit(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = philo;
	pthread_mutex_destroy(tmp->info->is_dead_mutex);
	while (tmp)
	{
		next = tmp->next;
		pthread_mutex_destroy(tmp->right_fork);
		free(tmp->right_fork);
		free(tmp);
		tmp = next;
	}
	error_exiting(254);
}
